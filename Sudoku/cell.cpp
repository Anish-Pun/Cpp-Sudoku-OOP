#include "cell.h"

namespace sudoku {

    Cell::Cell()
        : m_value(0),
        m_fixed(false)
    {
    }

    // OOP: parameterized constructor
    Cell::Cell(int value, bool fixed)
        : m_value(value),
        m_fixed(fixed)
    {
    }

    int Cell::value() const
    {
        return m_value;
    }

    void Cell::setValue(int v)
    {
        m_value = v;
    }

    bool Cell::isFixed() const
    {
        return m_fixed;
    }

    void Cell::setFixed(bool fixed)
    {
        m_fixed = fixed;
    }

}
