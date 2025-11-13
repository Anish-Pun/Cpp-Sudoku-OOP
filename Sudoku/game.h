#ifndef GAME_H
#define GAME_H

#include "board.h"

namespace sudoku {

class Game
{
public:
    Game();

    void reset();

    Board&       board();
    const Board& board() const;

private:
    Board m_board;
};

}

#endif // GAME_H
