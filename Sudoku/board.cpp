#include "board.h"
#include <iostream>

namespace sudoku {

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

bool Board::isInside(int row, int col) const
{
    return row >= 0 && row < Size && col >= 0 && col < Size;
}

bool Board::isValidMove(int row, int col, int value) const
{
    if (!isInside(row, col)) {
        return false;
    }

    if (value == 0) {
        return true;
    }

    if (value < 1 || value > 9) {
        return false;
    }

    for (int c = 0; c < Size; ++c) {
        if (c != col && valueAt(row, c) == value) {
            return false;
        }
    }

    for (int r = 0; r < Size; ++r) {
        if (r != row && valueAt(r, col) == value) {
            return false;
        }
    }

    int blockRow = (row / 3) * 3;
    int blockCol = (col / 3) * 3;

    for (int r = blockRow; r < blockRow + 3; ++r) {
        for (int c = blockCol; c < blockCol + 3; ++c) {
            if ((r != row || c != col) && valueAt(r, c) == value) {
                return false;
            }
        }
    }

    return true;
}

bool Board::rowHasConflict(int row) const
{
    bool seen[10] = { false };

    for (int c = 0; c < Size; ++c) {
        int v = valueAt(row, c);
        if (v == 0) {
            continue;
        }
        if (seen[v]) {
            return true;
        }
        seen[v] = true;
    }

    return false;
}

bool Board::columnHasConflict(int col) const
{
    bool seen[10] = { false };

    for (int r = 0; r < Size; ++r) {
        int v = valueAt(r, col);
        if (v == 0) {
            continue;
        }
        if (seen[v]) {
            return true;
        }
        seen[v] = true;
    }

    return false;
}

bool Board::blockHasConflict(int startRow, int startCol) const
{
    bool seen[10] = { false };

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            int v = valueAt(startRow + r, startCol + c);
            if (v == 0) {
                continue;
            }
            if (seen[v]) {
                return true;
            }
            seen[v] = true;
        }
    }

    return false;
}

bool Board::isComplete() const
{
    for (int r = 0; r < Size; ++r) {
        for (int c = 0; c < Size; ++c) {
            if (valueAt(r, c) == 0) {
                return false;
            }
        }
    }
    return true;
}

bool Board::isValid() const
{
    for (int r = 0; r < Size; ++r) {
        if (rowHasConflict(r)) {
            return false;
        }
    }

    for (int c = 0; c < Size; ++c) {
        if (columnHasConflict(c)) {
            return false;
        }
    }

    for (int r = 0; r < Size; r += 3) {
        for (int c = 0; c < Size; c += 3) {
            if (blockHasConflict(r, c)) {
                return false;
            }
        }
    }

    return true;
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

} // namespace sudoku
