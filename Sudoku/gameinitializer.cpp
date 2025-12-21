#include "gameinitializer.h"
#include <iostream>


bool GameInitializer::createGameFromDialog(sudoku::Game& game)
{
    WelcomeMsg startupDialog;
    if (startupDialog.exec() != QDialog::Accepted) {
        return false;
    }

    return initializeGame(game, startupDialog.selectedPlayerName(), startupDialog.isNewGame());
}
bool GameInitializer::initializeGame(sudoku::Game& game, const QString& playerName, bool isNewGame)
{
    // Exception handling: wrap game initialization in try-catch
    try {
        if (isNewGame) {
            game.setPlayerName(playerName.toStdString());
            if (!game.savePlayerData()) {
                std::cerr << "Warning: Failed to save initial player data" << std::endl;
            }
        } else {
            if (!game.loadPlayerData(playerName.toStdString())) {
                std::cerr << "Failed to load player data for: " << playerName.toStdString() << std::endl;
                return false;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error initializing game: " << e.what() << std::endl;
        return false;
    }
    
    return true;
}

