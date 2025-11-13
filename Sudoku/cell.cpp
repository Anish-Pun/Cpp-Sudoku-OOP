#include "cell.h"

Cell::Cell()
    : m_value(0)
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
