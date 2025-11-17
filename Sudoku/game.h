#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <string>

namespace sudoku {

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

private:
    Board      m_board;
    Difficulty m_difficulty;

     // implementing real puzzel
    void setupInitialBoard();
};

} // namespace sudoku

#endif // GAME_H
