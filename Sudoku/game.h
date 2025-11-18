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

class Game
{
public:
    explicit Game(Difficulty difficulty = Difficulty::Easy);

    void reset();
    void newGame(Difficulty difficulty);

    Board&       board();
    const Board& board() const;

    bool setCell(int row, int col, int value);
    bool isFinished() const;
    bool isValid() const;

    Difficulty difficulty() const;

    void solve();  // vul de oplossing in

private:
    Board      m_board;
    Difficulty m_difficulty;

    Grid m_solution;

     // implementing real puzzel
    void setupInitialBoard();
};

} // namespace sudoku

#endif // GAME_H
