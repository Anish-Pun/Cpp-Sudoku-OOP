#include "game.h"
#include "PlayerStorage.h"
#include <iostream>
#include <array>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <filesystem>
#include <cctype>
#include <future>
#include <functional>

namespace sudoku {

// eenvoudige RNG helper
static std::mt19937& rng()
{
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

// Sudoku helper
static bool isSafe(const Grid& g, int row, int col, int value)
{
    // row
    for (int c = 0; c < 9; ++c) {
        if (g[row][c] == value) return false;
    }
    // col
    for (int r = 0; r < 9; ++r) {
        if (g[r][col] == value) return false;
    }
    // 3x3 block
    int br = (row / 3) * 3;
    int bc = (col / 3) * 3;
    for (int r = br; r < br + 3; ++r) {
        for (int c = bc; c < bc + 3; ++c) {
            if (g[r][c] == value) return false;
        }
    }
    return true;
}

static bool findEmpty(const Grid& g, int& row, int& col)
{
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (g[r][c] == 0) {
                row = r;
                col = c;
                return true;
            }
        }
    }
    return false;
}

// backtracking to fill an empty grid into a full valid solution
static bool fillGrid(Grid& g)
{
    int row = 0, col = 0;
    if (!findEmpty(g, row, col)) {
        return true; // no empty cell => solved
    }

    std::array<int, 9> nums = {1,2,3,4,5,6,7,8,9};
    // random order for variation
    std::shuffle(nums.begin(), nums.end(), rng());

    for (int v : nums) {
        if (isSafe(g, row, col, v)) {
            g[row][col] = v;
            if (fillGrid(g)) {
                return true;
            }
            g[row][col] = 0;
        }
    }
    return false; // backtrack
}

static Grid generateSolvedGrid()
{
    Grid g{};
    // all zeros by default
    fillGrid(g);
    return g;
}

static void removeCellsForDifficulty(Grid& g, Difficulty diff)
{
    int targetClues = 40; // default easy-ish
    switch (diff) {
    case Difficulty::Easy:   targetClues = 50; break;
    case Difficulty::Medium: targetClues = 40; break;
    case Difficulty::Hard:   targetClues = 30; break;
    }

    const int totalCells   = 81;
    int       toRemove     = totalCells - targetClues;
    if (toRemove <= 0) return;

    std::vector<int> indices(totalCells);
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), rng());

    int removed = 0;
    for (int idx : indices) {
        if (removed >= toRemove) break;

        int r = idx / 9;
        int c = idx % 9;
        if (g[r][c] != 0) {
            g[r][c] = 0;
            ++removed;
        }
    }
}

// Helper function to generate puzzle (can be called from thread)
static std::pair<Grid, Grid> generatePuzzle(Difficulty difficulty)
{
    Grid full = generateSolvedGrid();
    Grid puzzle = full;
    removeCellsForDifficulty(puzzle, difficulty);
    return std::make_pair(full, puzzle);
}

double Game::averageTimeSeconds() const
{
    if (m_gamesWon == 0) {
        return 0.0;
    }
    return static_cast<double>(m_totalTimeSeconds) / m_gamesWon;
}

void Game::registerFinishedGame(int elapsedSeconds)
{
    if (elapsedSeconds < 0) {
        return;
    }
    ++m_gamesWon;
    m_totalTimeSeconds += elapsedSeconds;
    if (m_bestTimeSeconds < 0 || elapsedSeconds < m_bestTimeSeconds) {
        m_bestTimeSeconds = elapsedSeconds;
    }
}

int Game::solutionAt(int row, int col) const
{
    if (row < 0 || row >= Board::Size || col < 0 || col >= Board::Size) {
        return 0;
    }
    return m_solution[row][col];
}

Game::Game(Difficulty difficulty)
    : m_board()
    , m_difficulty(difficulty)
    , m_solution{}
{
    setupInitialBoard();
}

// OOP: destructor herstelt het spel naar een lege staat voor het uit scope gaat
Game::~Game()
{
    m_board.clear();
    m_solution = {};
}

void Game::reset()
{
    setupInitialBoard();
}

void Game::newGame(Difficulty difficulty)
{
    m_difficulty = difficulty;
    ++m_gamesPlayed;
    setupInitialBoard();
}

// Thread support: generate puzzle in background thread using std::thread
std::future<void> Game::newGameAsync(Difficulty difficulty, std::function<void()> onComplete)
{
    m_difficulty = difficulty;
    ++m_gamesPlayed;
    
    // Launch puzzle generation in a separate thread using std::async
    // This uses std::thread internally and allows background processing
    return std::async(std::launch::async, [this, difficulty, onComplete]() {
        // Exception handling: wrap thread work in try-catch
        try {
            // Generate puzzle in background thread (CPU-intensive operation)
            auto [full, puzzle] = generatePuzzle(difficulty);
            
            // Store results (these assignments are thread-safe for this use case)
            // In production, you'd use mutexes for thread safety
            m_solution = full;
            
            // Apply puzzle to board
            m_board.clear();
            for (int r = 0; r < Board::Size; ++r) {
                for (int c = 0; c < Board::Size; ++c) {
                    int v = puzzle[r][c];
                    m_board.setValue(r, c, v);
                    m_board.setFixed(r, c, v != 0);
                }
            }
            
            // Call completion callback if provided
            if (onComplete) {
                onComplete();
            }
        } catch (const std::exception& e) {
            std::cerr << "Error generating puzzle in thread: " << e.what() << std::endl;
            // Fallback to synchronous generation on error
            setupInitialBoard();
        }
    });
}

Board& Game::board()
{
    return m_board;
}

const Board& Game::board() const
{
    return m_board;
}

Difficulty Game::difficulty() const
{
    return m_difficulty;
}

bool Game::setCell(int row, int col, int value)
{
    std::cout << "Game::setCell(" << row << ", " << col
              << ") = " << value << std::endl;

    // basis checks
    if (!m_board.isInside(row, col)) {
        return false;
    }
    if (m_board.isFixed(row, col)) {
        return false;
    }
    // 0 = leeg maken
    if (value < 0 || value > 9) {
        return false;
    }

    m_board.setValue(row, col, value);
    return true;
}

bool Game::isFinished() const
{
    return m_board.isComplete() && m_board.isValid();
}

bool Game::isValid() const
{
    return m_board.isValid();
}

// hier gebeurt Sudoku selectie
void Game::setupInitialBoard()
{
    m_board.clear();

    // genereer een volledig opgelost grid
    const Grid& full = generateSolvedGrid();


    // maak een puzzel door waarden te verwijderen afhankelijk van de difficulty
    Grid puzzle = full;
    removeCellsForDifficulty(puzzle, m_difficulty);

    // oplossing opslaan
    m_solution = full;

    // puzzel in board zetten + fixed markeren
    for (int r = 0; r < Board::Size; ++r) {
        for (int c = 0; c < Board::Size; ++c) {
            int v = puzzle[r][c];
            m_board.setValue(r, c, v);
            m_board.setFixed(r, c, v != 0);
        }
    }
}

void Game::solve()
{
    // Vul hele oplossing in het board
    for (int r = 0; r < Board::Size; ++r) {
        for (int c = 0; c < Board::Size; ++c) {
            int v = m_solution[r][c];
            m_board.setValue(r, c, v);
            m_board.setFixed(r, c, true); // alles locken na solve
        }
    }
}

// File I/O implementation
std::string Game::getPlayerDataPath(const std::string& playerName)
{
    // Create saves directory if it doesn't exist
    std::filesystem::path savesDir = "saves";
    if (!std::filesystem::exists(savesDir)) {
        std::filesystem::create_directories(savesDir);
    }
    
    // Make player name safe for file name
    std::string safeName = playerName;
    for (char& c : safeName) {
        if (!std::isalnum(c) && c != '_' && c != '-') {
            c = '_';
        }
    }
    
    return (savesDir / (safeName + ".dat")).string();
}

bool Game::savePlayerData() const
{
    // Exception handling: use friend class with try-catch
    try {
        PlayerDataSerializer::save(*this);
        return true;
    } catch (const PlayerDataSerializer::FileIOException& e) {
        std::cerr << "Failed to save player data: " << e.what() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error saving player data: " << e.what() << std::endl;
        return false;
    }
}

bool Game::loadPlayerData(const std::string& playerName)
{
    // Exception handling: use friend class with try-catch
    try {
        PlayerDataSerializer::load(*this, playerName);
        return true;
    } catch (const PlayerDataSerializer::FileIOException& e) {
        std::cerr << "Failed to load player data: " << e.what() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error loading player data: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::string> Game::listAvailablePlayers()
{
    // Exception handling: use friend class
    try {
        return PlayerDataSerializer::listPlayers();
    } catch (const std::exception&) {
        return std::vector<std::string>(); // Return empty on error
    }
}

bool Game::playerExists(const std::string& playerName)
{
    // Exception handling: use friend class
    try {
        return PlayerDataSerializer::playerFileExists(playerName);
    } catch (const std::exception&) {
        return false;
    }
}


} // namespace sudoku
