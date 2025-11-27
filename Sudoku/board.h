#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include <array>
#include <iosfwd>

namespace sudoku {

// OOP: Abstraction
class Board
{
public:
    static const int Size = 9;

    Board();
    // OOP: parameterized constructor
    explicit Board(int fillValue);
    // OOP: parameterized constructor
    Board(const std::array<std::array<int, Size>, Size>& values);
    // OOP: copy constructor
    Board(const Board& other);
    // OOP: destructor
    ~Board();

    void clear();

    Cell&       cellAt(int row, int col);
    const Cell& cellAt(int row, int col) const;

    void setValue(int row, int col, int value);
    int  valueAt(int row, int col) const;

    bool isInside(int row, int col) const;

    bool isFixed(int row, int col) const;
    void setFixed(int row, int col, bool fixed);

    bool isValidMove(int row, int col, int value) const;

    bool isComplete() const;
    bool isValid() const;

    void print(std::ostream& out) const;

private:
    // OOP: Object composition
    Cell m_cells[Size][Size];

    bool rowHasConflict(int row) const;
    bool columnHasConflict(int col) const;
    bool blockHasConflict(int startRow, int startCol) const;
};

std::ostream& operator<<(std::ostream& out, const Board& board);

} // namespace sudoku

#endif // BOARD_H
