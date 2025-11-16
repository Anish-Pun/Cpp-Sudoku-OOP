#include "game.h"

namespace sudoku {

Game::Game(Difficulty difficulty)
    : m_board()
    , m_difficulty(difficulty)
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
    // 0 = clear cell, allowed anywhere inside board
    if (!m_board.isInside(row, col)) {
        return false;
    }

    if (!m_board.isValidMove(row, col, value)) {
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

void Game::setupInitialBoard()
{
    // For now: empty board.
    // Later we'll load a puzzle based on m_difficulty.
    m_board.clear();
}

} // namespace sudoku
