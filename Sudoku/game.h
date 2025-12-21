#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <array>
#include <cstdint>
#include <string>
#include <vector>
#include <thread>
#include <future>
#include <functional>

namespace sudoku {

using Grid = std::array<std::array<std::uint8_t, 9>, 9>;

// Forward declaration for friend class
class PlayerDataSerializer;

enum class Difficulty
{
    Easy,
    Medium,
    Hard
};

// OOP: Abstraction
class AbstractGame
{
public:
    virtual ~AbstractGame() = default;

    virtual void reset() = 0; // OOP: Polymorphism
    virtual void newGame(Difficulty difficulty) = 0;

    virtual Board& board() = 0;
    virtual const Board& board() const = 0;

    virtual Difficulty difficulty() const = 0;

    virtual bool isFinished() const = 0;
    virtual bool isValid() const = 0;

    virtual bool setCell(int row, int col, int value) = 0;

    virtual void solve() = 0;

    virtual int solutionAt(int row, int col) const = 0;
};

// OOP: Inheritance
class Game : public AbstractGame
{
public:
    explicit Game(Difficulty difficulty = Difficulty::Easy);
    // OOP: destructor
    ~Game() override;

    void reset() override;
    void newGame(Difficulty difficulty) override;
    
    // Thread support: generate puzzle in background
    std::future<void> newGameAsync(Difficulty difficulty, std::function<void()> onComplete = nullptr);

    Board& board() override;
    const Board& board() const override;

    Difficulty difficulty() const override;

    bool isFinished() const override;
    bool isValid() const override;

    bool setCell(int row, int col, int value) override;

    void solve() override; // OOP: Polymorphism
    int solutionAt(int row, int col) const override;

    // stats getters
    int gamesPlayed() const { return m_gamesPlayed; }
    int gamesWon() const { return m_gamesWon; }
    int bestTimeSeconds() const { return m_bestTimeSeconds; }
    double averageTimeSeconds() const;
    void registerFinishedGame(int elapsedSeconds);
    
    // player name
    const std::string& playerName() const { return m_playerName; }
    void setPlayerName(const std::string& name) { m_playerName = name; }
    
    // file I/O for player data
    bool savePlayerData() const;
    bool loadPlayerData(const std::string& playerName);
    
    // static methods to list and check players
    static std::vector<std::string> listAvailablePlayers();
    static bool playerExists(const std::string& playerName);
private:
    Board      m_board;      // OOP: Composition
    Difficulty m_difficulty; // OOP: Encapsulation
    Grid       m_solution;   // OOP: Encapsulation

    int  m_gamesPlayed      = 0;
    int  m_gamesWon         = 0;
    int  m_bestTimeSeconds  = -1;
    long m_totalTimeSeconds = 0;
    std::string m_playerName;

    void setupInitialBoard();
    static std::string getPlayerDataPath(const std::string& playerName);
    
    // OOP: Friend class for serialization (useful friend class)
    friend class PlayerDataSerializer;
};

} // namespace sudoku

#endif // GAME_H
