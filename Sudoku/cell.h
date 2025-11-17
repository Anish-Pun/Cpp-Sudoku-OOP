#ifndef CELL_H
#define CELL_H

namespace sudoku {

class Cell
{
public:
    Cell();

    int  value() const;
    void setValue(int v);

    bool isFixed() const;
    void setFixed(bool fixed);

private:
    int m_value;
    bool m_fixed;
};

} // namespace sudoku

#endif // CELL_H
