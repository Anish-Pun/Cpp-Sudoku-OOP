#ifndef CELL_H
#define CELL_H

class Cell
{
public:
    Cell();

    int  value() const;
    void setValue(int v);

private:
    int m_value;
};

#endif // CELL_H
