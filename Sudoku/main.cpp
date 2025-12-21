#include <QApplication>
#include "game.h"
#include "mainwindow.h"
#include "gameinitializer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    sudoku::Game game;
    if (!GameInitializer::createGameFromDialog(game)) {
        return 0;
    }

    MainWindow w(game);
    w.show();
    return app.exec();
}

