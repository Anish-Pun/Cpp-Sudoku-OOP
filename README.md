```
███████╗██╗   ██╗██████╗  ██████╗ ██╗  ██╗██╗   ██╗
██╔════╝██║   ██║██╔══██╗██╔═══██╗██║ ██╔╝██║   ██║
███████╗██║   ██║██║  ██║██║   ██║█████╔╝ ██║   ██║
╚════██║██║   ██║██║  ██║██║   ██║██╔═██╗ ██║   ██║
███████║╚██████╔╝██████╔╝╚██████╔╝██║  ██╗╚██████╔╝
╚══════╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ 
 ```                                                                  
---

## Overview
A fully object-oriented Sudoku game built with C++ and Qt. Features a user-friendly GUI, multiple difficulty levels, player statistics, and persistent player profiles.

---

## Features
- ✔️ Playable Sudoku game with Qt GUI
- ✔️ Difficulty modes (Easy / Medium / Hard)
- ✔️ Tracks best and average completion times
- ✔️ Automatic validation and error checking
- ✔️ Automatic solve function
- ✔️ Player statistics tracking (games played, wins, best time)
- ✔️ Save/load player progress and profiles
- ✔️ Welcome message and player selection
- ✔️ Clean, responsive interface

---

# How to Run
- See [detailed instructions](Documentation/HowToRun.md) for the project.
---

# Project Structure
```
Cpp-Sudoku-OOP/
├── HowToRun.md                    # Detailed run instructions
├── Document.ipynb                 # Documentation notebook
├── README.md                      # This file
├── Resources/
│   └── SudokuGui.png              # Screenshot of the GUI
└── Sudoku/                        # Main Sudoku project
    ├── CMakeLists.txt             # Build configuration
    │
    ├── Forms/                     # Qt Designer UI files
    │   └── mainwindow.ui
    │
    ├── Header Files/              # Header (.h) files
    │   └── mainwindow.h
    │   ├── ...
    │
    └── Source Files/              # C++ source (.cpp) files
        └── mainwindow.cpp
        ├── ...

```
---
# GUI
![Current GUI](Resources/SudokuGui.png)

---
## Author
- [Anish](https://github.com/Anish-Pun)

---
*This project was created as a college assignment to demonstrate C++ and OOP principles with Qt.*
