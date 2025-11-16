#ifndef GAME_H
#define GAME_H

#include "board.h"

namespace sudoku {

// Difficulty for later puzzles
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

    void reset();                          // reset current game
    void newGame(Difficulty difficulty);   // change difficulty + reset

    Board&       board();
    const Board& board() const;

    Difficulty difficulty() const;

    bool setCell(int row, int col, int value);

    // Board state helpers
    bool isFinished() const;
    bool isValid() const;

private:
    Board      m_board;
    Difficulty m_difficulty;

    // Gotta implement real puzzel
    void setupInitialBoard();
};

} // namespace sudoku

#endif // GAME_H
