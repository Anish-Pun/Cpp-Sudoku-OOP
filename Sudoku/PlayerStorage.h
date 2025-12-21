#ifndef PLAYERSTORAGE_H
#define PLAYERSTORAGE_H

#include "game.h"
#include <string>
#include <fstream>
#include <stdexcept>

namespace sudoku {

// OOP: Friend class - can access private members of Game for serialization
class PlayerDataSerializer
{
public:
    // Exception class for file I/O errors
    class FileIOException : public std::runtime_error
    {
    public:
        explicit FileIOException(const std::string& message)
            : std::runtime_error("File I/O Error: " + message) {}
    };

    // Save player data
    static void save(const Game& game);
    
    // Load player data into game
    static void load(Game& game, const std::string& playerName);
    
    // Check if player file exists
    static bool playerFileExists(const std::string& playerName);
    
    // List all available players
    static std::vector<std::string> listPlayers();

private:
    static std::string getPlayerDataPath(const std::string& playerName);
};

} // namespace sudoku

#endif // PLAYERSTORAGE_H

