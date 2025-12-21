# Experiments van dit Project
---

## Weekoverzicht

### Week 1 (13 Nov 2025) - Basis Setup
- Basis project structuur gemaakt
- Cell en Board klassen gemaakt
- 9x9 bord geïmplementeerd
- Getest of ik een bord kon maken met cellen

### Week 2 (16-17 Nov 2025) - Game Logica
- Game logica toegevoegd (difficulty, reset, new game)
- Game verbonden met UI
- Check button gemaakt
- Solve button gemaakt
- Timer toegevoegd
- Fixed cells geïmplementeerd
- Getest of alles werkt via de UI

### Week 3 (20 Nov 2025) - Puzzle Generatie
- Medium en Hard puzzles toegevoegd
- Puzzle generator gemaakt die random puzzles genereert
- Getest of gegenereerde puzzles geldig zijn

### Week 4 (27 Nov 2025) - OOP Verbeteringen
- Parameterized constructors toegevoegd
- Copy constructors gemaakt
- Destructors toegevoegd
- Constructor forwarding geïmplementeerd
- Inline functies gebruikt
- Getest of alles nog steeds werkt na refactoring

### Week 5 (4 Dec 2025) - Code Optimalisatie
- Template functie gemaakt voor conflict detection
- Memory optimalisatie met uint8_t
- Const references gebruikt waar mogelijk
- Code opgeschoond en verbeterd

### Week 6 (11 Dec 2025) - Statistics
- Game stats toegevoegd (games played, games won, best time)
- PlayerStats UI gemaakt
- Stats worden live geupdate
- Memory leak gefixt
- Getest of stats correct worden bijgehouden

### Week 7 (21 Dec 2025) - Player Storage & Welcome Screen
- Player data storage geïmplementeerd (save/load)
- Welcome message dialog gemaakt
- UI gepolished
- Getest of save/load werkt

---

## Hoe ik alles heb getest

### Stap 1: Basis Project Structuur (13 Nov 2025)

**Commit**: `basic project structure`, `Refactor board and cell classes`

**Doel**: Opzetten van de basis klassen structuur.

**Tests die ik uitvoerde:**

1. **Cell Klasse Basis Test**
   - Test: Kan ik een `Cell` object aanmaken en gebruiken?
   - Verificatie: Via handmatige tests in code
   - Commit bewijs: `Refactor board and cell classes to include namespace and improve structure`
   - Resultaat: ✅ Basis Cell klasse werkt

2. **Board Initialisatie Test**
   - Test: Kan ik een 9x9 bord aanmaken?
   - Verificatie: 
     ```cpp
     Board board;
     // Test: alle cellen moeten 0 zijn
     ```
   - Commit bewijs: `9x9 board - Implemented simple 9x9 board`
   - Resultaat: ✅ Board wordt correct geïnitialiseerd

**Conclusie Stap 1**: Basis structuur staat en kan getest worden.

---

### Stap 2: Game Logica Implementatie (16-17 Nov 2025)

**Commits**: `Add game logic`, `Connect Game Logic to UI`, `Update game.cpp - Added print so i can see if the game is connected to ui or not`

**Doel**: Implementeren van core game functionaliteit.

**Tests die ik uitvoerde:**

1. **Game Connectie Test**
   - Test: Is de game logica verbonden met de UI?
   - Verificatie: `std::cout` statements om te zien of `setCell()` wordt aangeroepen
   - Commit bewijs: `Update game.cpp - Added print so i can see if the game is connected to ui or not`
   - Resultaat: ✅ Game is verbonden met UI

2. **Difficulty Test**
   - Test: Werken verschillende difficulty levels?
   - Verificatie: Test Easy, Medium, Hard via UI
   - Commit bewijs: `Add game logic - Added Difficulty`
   - Resultaat: ✅ Difficulty werkt correct

3. **Reset/New Game Test**
   - Test: Werken `reset()` en `newGame()` correct?
   - Verificatie: Test via UI buttons
   - Commit bewijs: `Add game logic - Extended game with reset / new game`
   - Resultaat: ✅ Reset en new game werken

4. **IsFinished/IsValid Test**
   - Test: Detecteren `isFinished()` en `isValid()` correct de game state?
   - Verificatie: Test met verschillende board states
   - Commit bewijs: `Add game logic - Added Helper isFinished / isValid`
   - Resultaat: ✅ Helper functies werken correct

---

### Stap 3: UI Features en Validatie (17 Nov 2025)

**Commits**: `Add Check Btn`, `Implemented Check Btn`, `Fix: Ignore fixed cell when checking`, `Add fixed cells to Board and Game`, `Mark fixed cells as read-only in UI`

**Doel**: Implementeren van UI features en validatie.

**Tests die ik uitvoerde:**

1. **Check Button Test**
   - Test: Detecteert de Check button fouten correct?
   - Verificatie: Test met conflicten in het bord via UI
   - Commit bewijs: `Add Check Btn`, `Implemented Check Btn`
   - Resultaat: ✅ Check functionaliteit werkt

2. **Fixed Cells Test**
   - Test: Worden fixed cellen correct beschermd?
   - Verificatie: Test of fixed cellen niet gewijzigd kunnen worden
   - Commit bewijs: `Add fixed cells to Board and Game`, `Mark fixed cells as read-only in UI`
   - Resultaat: ✅ Fixed cellen worden beschermd

3. **Check Button Bug Fix**
   - Test: Negeert check fixed cellen?
   - Verificatie: Test dat alleen user-input cellen worden gecheckt
   - Commit bewijs: `Fix: Ignore fixed cell when checking`
   - Resultaat: ✅ Bug gefixt

4. **Solve Button Test**
   - Test: Werkt de Solve button correct?
   - Verificatie: Test of solve de volledige oplossing invult
   - Commit bewijs: `Implement Solve button using stored Sudoku solutions`
   - Resultaat: ✅ Solve werkt correct

5. **Timer Test**
   - Test: Werkt de game timer correct?
   - Verificatie: Test of timer correct telt en update
   - Commit bewijs: `Add game timer to Sudoku UI`
   - Resultaat: ✅ Timer werkt correct

---

### Stap 4: Puzzle Generatie (20 Nov 2025)

**Commits**: `Add medium and hard Sudoku puzzles`, `Implement Sudoku grid generation and difficulty-based puzzle creation`

**Doel**: Implementeren van dynamische puzzle generatie.

**Tests die ik uitvoerde:**

1. **Static Puzzles Test**
   - Test: Werken statische puzzles voor Medium en Hard?
   - Verificatie: Test verschillende difficulty levels
   - Commit bewijs: `Add medium and hard Sudoku puzzles`
   - Resultaat: ✅ Static puzzles werken

2. **Puzzle Generator Test**
   - Test: Genereert de generator geldige Sudoku puzzles?
   - Verificatie: Test of gegenereerde puzzles geldig zijn
   - Commit bewijs: `Implement Sudoku grid generation and difficulty-based puzzle creation`
   - Resultaat: ✅ Generator werkt correct

---

### Stap 5: OOP Verbeteringen (27 Nov 2025)

**Commits**: `Add parameterized constructors for Cell and Board`, `Add copy constructors for Cell and Board`, `Add 2 destructors`, `Add constructor forwarding`, `Inline isInside function`

**Doel**: Verbeteren van OOP structuur volgens requirements.

**Tests die ik uitvoerde:**

1. **Parameterized Constructors Test**
   - Test: Werken de nieuwe constructors correct?
   - Verificatie:
     ```cpp
     Cell cell(5, true);
     Board board(0);  // Fill with 0
     ```
   - Commit bewijs: `Add parameterized constructors for Cell and Board`
   - Resultaat: ✅ Constructors werken correct

2. **Copy Constructors Test**
   - Test: Werken copy constructors correct?
   - Verificatie: Test of kopieën onafhankelijk zijn
   - Commit bewijs: `Add copy constructors for Cell and Board`
   - Resultaat: ✅ Copy constructors werken

3. **Destructors Test**
   - Test: Ruimen destructors correct op?
   - Verificatie: Test memory cleanup
   - Commit bewijs: `Add 2 destructors`
   - Resultaat: ✅ Destructors werken correct

4. **Constructor Forwarding Test**
   - Test: Werkt constructor forwarding?
   - Verificatie: Test of default constructors correct forwarden
   - Commit bewijs: `Add constructor forwarding`
   - Resultaat: ✅ Forwarding werkt

5. **Inline Function Test**
   - Test: Werkt inline `isInside()` sneller?
   - Verificatie: Performance test
   - Commit bewijs: `Inline isInside function for faster bounds-checking`
   - Resultaat: ✅ Inline functie werkt

---

### Stap 6: Code Optimalisatie (4 Dec 2025)

**Commits**: `Refactor conflict detection methods to use a templated helper function`, `Optimize memory usage`, `Refactor variable declarations to use const references`, `Refactor difficultyFromCombo to use const reference`

**Doel**: Code optimaliseren en verbeteren.

**Tests die ik uitvoerde:**

1. **Template Function Test**
   - Test: Werkt de template functie voor conflict detection?
   - Verificatie: Test row/column/block conflict detection
   - Commit bewijs: `Refactor conflict detection methods to use a templated helper function`
   - Resultaat: ✅ Template werkt en code is cleaner

2. **Memory Optimization Test**
   - Test: Is memory gebruik verbeterd?
   - Verificatie: Check memory usage met `std::uint8_t`
   - Commit bewijs: `Optimize memory usage`
   - Resultaat: ✅ Memory gebruik is geoptimaliseerd

3. **Const References Test**
   - Test: Werken const references correct?
   - Verificatie: Test of kopieën worden voorkomen
   - Commit bewijs: `Refactor variable declarations to use const references`
   - Resultaat: ✅ Const references werken

---

### Stap 7: Statistics en Player Features (11 Dec 2025)

**Commits**: `Add basic game stats`, `Update Game to keep wins and timing stats`, `Show game stats in PlayerStats`, `Count Solve button as a win in stats`, `Made Stats value update live`, `Fix memory leak by resetting stats window pointer`

**Doel**: Implementeren van player statistics.

**Tests die ik uitvoerde:**

1. **Basic Stats Test**
   - Test: Worden statistieken correct bijgehouden?
   - Verificatie: Test gamesPlayed, gamesWon tracking
   - Commit bewijs: `Add basic game stats`
   - Resultaat: ✅ Stats worden bijgehouden

2. **Stats Display Test**
   - Test: Worden stats correct getoond in UI?
   - Verificatie: Test PlayerStats dialog
   - Commit bewijs: `Show game stats in PlayerStats`
   - Resultaat: ✅ Stats worden getoond

3. **Live Update Test**
   - Test: Updaten stats live tijdens gameplay?
   - Verificatie: Test of stats direct updaten
   - Commit bewijs: `Made Stats value update live`
   - Resultaat: ✅ Live updates werken

4. **Memory Leak Fix**
   - Test: Wordt memory leak voorkomen?
   - Verificatie: Test pointer cleanup
   - Commit bewijs: `Fix memory leak by resetting stats window pointer`
   - Resultaat: ✅ Memory leak gefixt

---

### Stap 8: Player Storage en Welcome Screen (21 Dec 2025)

**Commits**: `This week commit: Add player data storage and welcome message dialog`, `Polished Welcome UI`, `Update WelcomeMsg.ui`

**Doel**: Implementeren van player data persistence en welcome screen.

**Tests die ik uitvoerde:**

1. **Player Storage Test**
   - Test: Wordt player data correct opgeslagen en geladen?
   - Verificatie: Test save/load functionaliteit
   - Commit bewijs: `Add player data storage`
   - Resultaat: ✅ Storage werkt correct

2. **Welcome Dialog Test**
   - Test: Werkt de welcome dialog correct?
   - Verificatie: Test new game en load game flows
   - Commit bewijs: `Add welcome message dialog`
   - Resultaat: ✅ Welcome dialog werkt

3. **UI Polish Test**
   - Test: Ziet de UI er goed uit?
   - Verificatie: Visual testing via GUI
   - Commit bewijs: `Polished Welcome UI`, `Update WelcomeMsg.ui`
   - Resultaat: ✅ UI is gepolished

---

## Test Methode

### Aanpak

Ik gebruikte een **iteratieve test-gedreven aanpak** zoals blijkt uit mijn commits:

1. **Implementeer minimale feature** (bijv. "Add Check Btn")
2. **Test via UI of code** (bijv. "Added print so i can see if the game is connected")
3. **Fix bugs die gevonden worden** (bijv. "Fix: Ignore fixed cell when checking")
4. **Refactor en optimaliseer** (bijv. "Refactor conflict detection methods")
5. **Ga door naar volgende feature**

### Test Tools die ik gebruikte

- **std::cout debugging**: Ik gebruikte print statements om te verifiëren dat code werkt
  - Bewijs: `Update game.cpp - Added print so i can see if the game is connected to ui or not`
  
- **GUI testing**: Ik testte functionaliteit via de Qt GUI
  - Bewijs: Veel commits over UI features die getest werden via de interface
  
- **Incrementele ontwikkeling**: Elke feature werd getest voordat ik verderging
  - Bewijs: Commits tonen stap-voor-stap ontwikkeling ( behalve voor de laatste week)

- **Bug fixing**: Ik fixte bugs die tijdens testing werden gevonden
  - Bewijs: `Fix: Ignore fixed cell when checking`, `Fix memory leak by resetting stats window pointer`

### Voorbeelden uit mijn Commits

```cpp
// Test voorbeeld: Game connectie verifiëren
// Commit: "Update game.cpp - Added print so i can see if the game is connected to ui or not"
bool Game::setCell(int row, int col, int value) {
    std::cout << "Game::setCell(" << row << ", " << col << ") = " << value << std::endl;
    // ... implementatie
}

// Test voorbeeld: Fixed cells beschermen
// Commit: "Fix: Ignore fixed cell when checking"
// Test: Fixed cellen moeten niet worden gecheckt voor conflicts
```

---

## Resultaten

### Voordelen van deze Test-Driven Aanpak

1. **Betrouwbaarheid**: Elke feature werd getest voordat ik verderging, zoals blijkt uit de commit geschiedenis
2. **Bug Detection**: Bugs werden vroeg gevonden en gefixt (bijv. "Fix: Ignore fixed cell when checking")
3. **Code Kwaliteit**: Refactoring en optimalisaties werden gedaan na basis functionaliteit

### Ontwikkelingspatroon


1. **Basis implementatie** → Test → **Bug fixes** → Test → **Commit**
2. Bijvoorbeeld:
   - `Add Check Btn` → `Implemented Check Btn` → `Fix: Ignore fixed cell` → `Commited`

---