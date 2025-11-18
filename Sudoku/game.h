#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <array>

namespace sudoku {

using Grid = std::array<std::array<int, 9>, 9>;

enum class Difficulty
{
    Easy,
    Medium,
    Hard
};

class AbstractGame
{
public:
    virtual ~AbstractGame() = default;

    virtual void reset() = 0;
    virtual void newGame(Difficulty difficulty) = 0;

    virtual Board& board() = 0;
    virtual const Board& board() const = 0;

    virtual Difficulty difficulty() const = 0;

    virtual bool isFinished() const = 0;
    virtual bool isValid() const = 0;

    virtual bool setCell(int row, int col, int value) = 0;

    virtual void solve() = 0;
};

class Game : public AbstractGame
{
public:
    explicit Game(Difficulty difficulty = Difficulty::Easy);

    void reset() override;
    void newGame(Difficulty difficulty) override;

    Board& board() override;
    const Board& board() const override;

    Difficulty difficulty() const override;

    bool isFinished() const override;
    bool isValid() const override;

    bool setCell(int row, int col, int value) override;

    void solve() override; // vul de oplossing in

private:
    Board      m_board;
    Difficulty m_difficulty;
    Grid       m_solution;

    void setupInitialBoard();
};

} // namespace sudoku

#endif // GAME_H
