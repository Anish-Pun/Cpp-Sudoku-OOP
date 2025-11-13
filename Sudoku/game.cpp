#include "game.h"

namespace sudoku {

Game::Game()
    : m_board()
{
}

void Game::reset()
{
    m_board.clear();
}

Board& Game::board()
{
    return m_board;
}

const Board& Game::board() const
{
    return m_board;
}

}
