#ifndef CELL_H
#define CELL_H

namespace sudoku {

// OOP: Encapsulation
class Cell
{
public:
    Cell();
    // OOP: parameterized constructor
    Cell(int value, bool fixed = false);
    // OOP: copy constructor
    Cell(const Cell& other);

    int  value() const;
    void setValue(int v);

    bool isFixed() const;
    void setFixed(bool fixed);

private: // OOP: Encapsulation
    int m_value;
    bool m_fixed;
};

} // namespace sudoku

#endif // CELL_H
