#include "board.h"
#include <iostream>

namespace sudoku {

Board::Board()
{
    clear();
}

// OOP: parameterized constructor
Board::Board(int fillValue)
{
    for (int r = 0; r < Size; ++r) {
        for (int c = 0; c < Size; ++c) {
            m_cells[r][c].setValue(fillValue);
            m_cells[r][c].setFixed(false);
        }
    }
}

// OOP: parameterized constructor
Board::Board(const std::array<std::array<int, Size>, Size>& values)
{
    for (int r = 0; r < Size; ++r) {
        for (int c = 0; c < Size; ++c) {
            m_cells[r][c].setValue(values[r][c]);
            m_cells[r][c].setFixed(false);
        }
    }
}

void Board::clear()
{
    for (int r = 0; r < Size; ++r) {
        for (int c = 0; c < Size; ++c) {
            m_cells[r][c].setValue(0);
            m_cells[r][c].setFixed(false);
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

bool Board::isFixed(int row, int col) const
{
    return m_cells[row][col].isFixed();
}

void Board::setFixed(int row, int col, bool fixed)
{
    m_cells[row][col].setFixed(fixed);
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

    // rij
    for (int c = 0; c < Size; ++c) {
        if (c == col) continue; // eigen cel overslaan
        if (m_cells[row][c].value() == value) {
            return false;
        }
    }

    // kolom
    for (int r = 0; r < Size; ++r) {
        if (r == row) continue; // eigen cel overslaan
        if (m_cells[r][col].value() == value) {
            return false;
        }
    }

    // 3x3 blok
    int br = (row / 3) * 3;
    int bc = (col / 3) * 3;
    for (int r = br; r < br + 3; ++r) {
        for (int c = bc; c < bc + 3; ++c) {
            if (r == row && c == col) continue; // eigen cel overslaan
            if (m_cells[r][c].value() == value) {
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
            int v = valueAt(r, c);
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
