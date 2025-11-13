#ifndef CELL_H
#define CELL_H

namespace sudoku {

class Cell
{
public:
    Cell();

    int  value() const;
    void setValue(int v);

private:
    int m_value;
};

} // namespace sudoku

#endif // CELL_H
