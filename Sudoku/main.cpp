#include <QApplication>
#include <iostream>
#include "game.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    sudoku::Game game;
    std::cout << game.board() << std::endl;

    MainWindow w(game);
    w.show();
    return app.exec();

}

