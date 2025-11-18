#include "game.h"
#include <iostream>
#include <array>
#include <vector>
#include <random>

namespace sudoku {

struct Puzzle {
    Grid puzzle;
    Grid solution;
};

// Een paar voorbeeld-puzzels (0 = leeg)
// Een paar voorbeeld-puzzels (0 = leeg)
static const std::vector<Puzzle> EASY_PUZZLES = {
    Puzzle{
        // puzzle
        Grid{{
            {{5,3,0, 0,7,0, 0,0,0}},
            {{6,0,0, 1,9,5, 0,0,0}},
            {{0,9,8, 0,0,0, 0,6,0}},

            {{8,0,0, 0,6,0, 0,0,3}},
            {{4,0,0, 8,0,3, 0,0,1}},
            {{7,0,0, 0,2,0, 0,0,6}},

            {{0,6,0, 0,0,0, 2,8,0}},
            {{0,0,0, 4,1,9, 0,0,5}},
            {{0,0,0, 0,8,0, 0,7,9}}
        }},
        // solution
        Grid{{
            {{5,3,4, 6,7,8, 9,1,2}},
            {{6,7,2, 1,9,5, 3,4,8}},
            {{1,9,8, 3,4,2, 5,6,7}},

            {{8,5,9, 7,6,1, 4,2,3}},
            {{4,2,6, 8,5,3, 7,9,1}},
            {{7,1,3, 9,2,4, 8,5,6}},

            {{9,6,1, 5,3,7, 2,8,4}},
            {{2,8,7, 4,1,9, 6,3,5}},
            {{3,4,5, 2,8,6, 1,7,9}}
        }}
    },
    Puzzle{
        // puzzle (de tweede die je al had)
        Grid{{
            {{0,0,0, 2,6,0, 7,0,1}},
            {{6,8,0, 0,7,0, 0,9,0}},
            {{1,9,0, 0,0,4, 5,0,0}},

            {{8,2,0, 1,0,0, 0,4,0}},
            {{0,0,4, 6,0,2, 9,0,0}},
            {{0,5,0, 0,0,3, 0,2,8}},

            {{0,0,9, 3,0,0, 0,7,4}},
            {{0,4,0, 0,5,0, 0,3,6}},
            {{7,0,3, 0,1,8, 0,0,0}}
        }},
        // solution (de volledige die ik je net gaf)
        Grid{{
            {{4,3,5, 2,6,9, 7,8,1}},
            {{6,8,2, 5,7,1, 4,9,3}},
            {{1,9,7, 8,3,4, 5,6,2}},

            {{8,2,6, 1,9,5, 3,4,7}},
            {{3,7,4, 6,8,2, 9,1,5}},
            {{9,5,1, 7,4,3, 6,2,8}},

            {{5,1,9, 3,2,6, 8,7,4}},
            {{2,4,8, 9,5,7, 1,3,6}},
            {{7,6,3, 4,1,8, 2,5,9}}
        }}
    }
};

// eenvoudige RNG helper
static std::mt19937& rng()
{
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

static const Puzzle& randomFrom(const std::vector<Puzzle>& list)
{
    std::uniform_int_distribution<std::size_t> dist(0, list.size() - 1);
    return list[dist(rng())];
}

Game::Game(Difficulty difficulty)
    : m_board()
    , m_difficulty(difficulty)
    , m_solution{}
{
    setupInitialBoard();
}

void Game::reset()
{
    setupInitialBoard();
}

void Game::newGame(Difficulty difficulty)
{
    m_difficulty = difficulty;
    setupInitialBoard();
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

// hier gebeurt de random Sudoku selectie
void Game::setupInitialBoard()
{
    m_board.clear();

    const Puzzle* chosen = nullptr;

    switch (m_difficulty) {
    case Difficulty::Easy:
        chosen = &randomFrom(EASY_PUZZLES);
        break;
    case Difficulty::Medium:
        // voorlopig zelfde set
        chosen = &randomFrom(EASY_PUZZLES);
        break;
    case Difficulty::Hard:
        chosen = &randomFrom(EASY_PUZZLES);
        break;
    }

    if (!chosen) {
        return;
    }

    // oplossing opslaan
    m_solution = chosen->solution;

    // puzzel in board zetten + fixed markeren
    for (int r = 0; r < Board::Size; ++r) {
        for (int c = 0; c < Board::Size; ++c) {
            int v = chosen->puzzle[r][c];
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


} // namespace sudoku
