#include <QApplication>
#include <iostream>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    sudoku::Game game;
    std::cout << game.board() << std::endl;

    return 0;
}
