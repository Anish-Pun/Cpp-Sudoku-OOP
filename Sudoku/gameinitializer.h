#ifndef GAMEINITIALIZER_H
#define GAMEINITIALIZER_H

#include "game.h"
#include "WelcomeMsg.h"
#include <QString>

class GameInitializer
{
public:
    // Show startup dialog and initialize game
    // Game is initialized via reference parameter
    static bool createGameFromDialog(sudoku::Game& game);
    
private:
    GameInitializer() = default;
    static bool initializeGame(sudoku::Game& game, const QString& playerName, bool isNewGame);
};

#endif // GAMEINITIALIZER_H

