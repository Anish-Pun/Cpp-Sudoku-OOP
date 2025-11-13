#include <QApplication>
#include <iostream>
#include "board.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Board board;
    std::cout << board << std::endl;

    return 0;
}
