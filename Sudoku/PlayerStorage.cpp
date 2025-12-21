#include "PlayerStorage.h"
#include <filesystem>
#include <cctype>

namespace sudoku {

std::string PlayerDataSerializer::getPlayerDataPath(const std::string& playerName)
{
    // Create saves directory if it doesn't exist
    std::filesystem::path savesDir = "saves";
    try {
        if (!std::filesystem::exists(savesDir)) {
            std::filesystem::create_directories(savesDir);
        }
    } catch (const std::filesystem::filesystem_error& e) {
        throw FileIOException("Cannot create saves directory: " + std::string(e.what()));
    }
    
    // Sanitize player name for filename (remove invalid characters)
    std::string safeName = playerName;
    for (char& c : safeName) {
        if (!std::isalnum(c) && c != '_' && c != '-') {
            c = '_';
        }
    }
    
    return (savesDir / (safeName + ".dat")).string();
}

void PlayerDataSerializer::save(const Game& game)
{
    // Exception handling: wrap file operations in try-catch
    try {
        if (game.m_playerName.empty()) {
            throw FileIOException("Player name is empty");
        }
        
        std::string filePath = getPlayerDataPath(game.m_playerName);
        std::ofstream file(filePath, std::ios::out | std::ios::trunc);
        
        if (!file.is_open()) {
            throw FileIOException("Cannot open file for writing: " + filePath);
        }
        
        // Write player data in a simple format
        // Friend class can access private members: m_playerName, m_gamesPlayed, etc.
        file << game.m_playerName << "\n";
        file << game.m_gamesPlayed << "\n";
        file << game.m_gamesWon << "\n";
        file << game.m_bestTimeSeconds << "\n";
        file << game.m_totalTimeSeconds << "\n";
        
        file.close();
        
        if (!file.good()) {
            throw FileIOException("Error writing to file: " + filePath);
        }
    } catch (const std::filesystem::filesystem_error& e) {
        throw FileIOException("Filesystem error: " + std::string(e.what()));
    } catch (const std::exception& e) {
        throw FileIOException("Unexpected error: " + std::string(e.what()));
    }
}

void PlayerDataSerializer::load(Game& game, const std::string& playerName)
{
    // Exception handling: wrap file operations in try-catch
    try {
        std::string filePath = getPlayerDataPath(playerName);
        
        if (!std::filesystem::exists(filePath)) {
            throw FileIOException("Player file does not exist: " + filePath);
        }
        
        std::ifstream file(filePath, std::ios::in);
        
        if (!file.is_open()) {
            throw FileIOException("Cannot open file for reading: " + filePath);
        }
        
        std::string line;
        
        // Read player name
        if (!std::getline(file, line)) {
            throw FileIOException("Cannot read player name from file");
        }
        game.m_playerName = line;
        
        // Read games played
        if (!std::getline(file, line)) {
            throw FileIOException("Cannot read games played from file");
        }
        try {
            game.m_gamesPlayed = std::stoi(line);
        } catch (const std::exception&) {
            throw FileIOException("Invalid games played value: " + line);
        }
        
        // Read games won
        if (!std::getline(file, line)) {
            throw FileIOException("Cannot read games won from file");
        }
        try {
            game.m_gamesWon = std::stoi(line);
        } catch (const std::exception&) {
            throw FileIOException("Invalid games won value: " + line);
        }
        
        // Read best time
        if (!std::getline(file, line)) {
            throw FileIOException("Cannot read best time from file");
        }
        try {
            game.m_bestTimeSeconds = std::stoi(line);
        } catch (const std::exception&) {
            throw FileIOException("Invalid best time value: " + line);
        }
        
        // Read total time
        if (!std::getline(file, line)) {
            throw FileIOException("Cannot read total time from file");
        }
        try {
            game.m_totalTimeSeconds = std::stol(line);
        } catch (const std::exception&) {
            throw FileIOException("Invalid total time value: " + line);
        }
        
        file.close();
    } catch (const FileIOException&) {
        // Re-throw our custom exceptions
        throw;
    } catch (const std::filesystem::filesystem_error& e) {
        throw FileIOException("Filesystem error: " + std::string(e.what()));
    } catch (const std::exception& e) {
        throw FileIOException("Unexpected error: " + std::string(e.what()));
    }
}

bool PlayerDataSerializer::playerFileExists(const std::string& playerName)
{
    try {
        std::string filePath = getPlayerDataPath(playerName);
        return std::filesystem::exists(filePath);
    } catch (const std::exception&) {
        return false;
    }
}

std::vector<std::string> PlayerDataSerializer::listPlayers()
{
    std::vector<std::string> players;
    
    try {
        std::filesystem::path savesDir = "saves";
        
        if (!std::filesystem::exists(savesDir)) {
            return players; // Empty vector if directory doesn't exist
        }
        
        for (const auto& entry : std::filesystem::directory_iterator(savesDir)) {
            if (entry.is_regular_file() && entry.path().extension() == ".dat") {
                // Try to read the player name from the file
                std::ifstream file(entry.path(), std::ios::in);
                if (file.is_open()) {
                    std::string playerName;
                    if (std::getline(file, playerName)) {
                        players.push_back(playerName);
                    }
                    file.close();
                }
            }
        }
    } catch (const std::filesystem::filesystem_error&) {
        // Return empty list on filesystem errors
        return players;
    } catch (const std::exception&) {
        // Return empty list on any other errors
        return players;
    }
    
    return players;
}

} // namespace sudoku

