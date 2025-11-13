#ifndef CELL_H
#define CELL_H

namespace sudoku { // C++ requirement: self-made namespace

class Cell           // Basis: useful class (represents one Sudoku cell)
{
public:
    Cell();          // OOP: default constructor

    int  value() const; // OOP: useful member function, const-correct
    void setValue(int v); // OOP: useful setter for member variable

private:
    int m_value;     // OOP: encapsulation (private member variable)
};

} // namespace sudoku

#endif // CELL_H
