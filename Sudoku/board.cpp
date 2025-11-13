#include "board.h"
#include <iostream>

Board::Board()
{
    clear();
}

void Board::clear()
{
    for (int r = 0; r < Size; ++r) {
        for (int c = 0; c < Size; ++c) {
            m_cells[r][c].setValue(0);
        }
    }
}

Cell& Board::cellAt(int row, int col)
{
    return m_cells[row][col];
}

const Cell& Board::cellAt(int row, int col) const
{
    return m_cells[row][col];
}

void Board::setValue(int row, int col, int value)
{
    m_cells[row][col].setValue(value);
}

int Board::valueAt(int row, int col) const
{
    return m_cells[row][col].value();
}

void Board::print(std::ostream& out) const
{
    for (int r = 0; r < Size; ++r) {
        for (int c = 0; c < Size; ++c) {
            int v = m_cells[r][c].value();
            if (v == 0)
                out << ". ";
            else
                out << v << ' ';
        }
        out << '\n';
    }
}

std::ostream& operator<<(std::ostream& out, const Board& board)
{
    board.print(out);
    return out;
}
