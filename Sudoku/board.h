#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include <iosfwd>

namespace sudoku {

    class Board
    {
    public:
        static const int Size = 9;

        Board();

        void clear();

        Cell&       cellAt(int row, int col);
        const Cell& cellAt(int row, int col) const;

        void setValue(int row, int col, int value);
        int  valueAt(int row, int col) const;

        void print(std::ostream& out) const;

    private:
        Cell m_cells[Size][Size];
    };

    std::ostream& operator<<(std::ostream& out, const Board& board);

}

#endif // BOARD_H
