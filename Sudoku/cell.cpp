#include "cell.h"

namespace sudoku {

    // OOP: constructor forwarding naar de parameterized versie
    Cell::Cell()
        : Cell(0, false)
    {
    }

    // OOP: parameterized constructor
    Cell::Cell(int value, bool fixed)
        : m_value(static_cast<std::uint8_t>(value)),
        m_fixed(fixed)
    {
    }

    // OOP: copy constructor
    Cell::Cell(const Cell& other)
        : m_value(other.m_value),
        m_fixed(other.m_fixed)
    {
    }

    int Cell::value() const
    {
        return m_value;
    }

    void Cell::setValue(int v)
    {
        // keep API accepting int but store as uint8_t internally
        if (v < 0) v = 0;
        if (v > 9) v = 9;
        m_value = static_cast<std::uint8_t>(v);
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
