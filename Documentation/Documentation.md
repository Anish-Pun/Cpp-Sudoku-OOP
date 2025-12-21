# Inhoudsopgave

- [Basis](#basis)
- [Aanvullend](#aanvullend)
- [OOP](#oop)
- [C++](#c)
- [Uitbreiding](#uitbreiding)

---

## Basis

### 1. useful and correct class (explain why)
- `Cell` stelt één Sudoku-vakje voor. Deze klasse bewaart alleen de waardes en de status van de cell.
- Ik bewaar de waardes via `std::uint8_t m_value;` voor geheugenefficiëntie (waarde 0-9 past in 1 byte), lees de waarde met `int value() const;` en wijzig de waarde met `void setValue(int v);`
- `bool m_fixed;` geeft aan of een cel vast is (True = fixed cell, False = speler kan invullen).
- Methoden zoals `isFixed()` en `setFixed()` regelen de status van de cel.
```cpp
namespace sudoku {
class Cell {
public:
    Cell();
    Cell(int value, bool fixed = false);
    Cell(const Cell& other);
    int value() const;
    void setValue(int v);
    bool isFixed() const;
    void setFixed(bool fixed);
private:
    std::uint8_t m_value;  // Memory-efficient: values 0-9 fit in 1 byte
    bool m_fixed;
};
} // namespace sudoku
```

### 2. useful and correct abstraction (explain why)
- Ik gebruik abstractie door een abstracte basisclass `AbstractGame` te definiëren.
- Deze class bepaalt welke functies het spel moet hebben.
- De UI werkt alleen met de abstracte interface en kent de implementatie van het spel niet.
```cpp
class AbstractGame {
public:
    virtual ~AbstractGame() = default;
    virtual void reset() = 0;
    virtual void newGame(Difficulty difficulty) = 0;
    virtual Board& board() = 0;
    // ...
};
```

### 3. useful and correct encapsulation (explain why)
- Ik gebruik encapsulation door data van mijn class in `private` te zetten.
- Data is alleen toegankelijk via public methods.
```cpp
private:
    int m_value;
    bool m_fixed;
```

### 4. useful and correct inheritance (explain why)
- Ik gebruik inheritance bij de spel-logica: `Game` erft van de abstracte basisclass `AbstractGame`.
```cpp
class Game : public AbstractGame {
public:
    explicit Game(Difficulty difficulty = Difficulty::Easy);
    void reset() override;
    // ...
};
```

### 5. useful and correct polymorphism (explain why)
- De UI werkt met de abstracte basisklasse `AbstractGame`, terwijl er in werkelijkheid een `Game`-object achter zit.
- Via de virtual functies in `AbstractGame` worden de overrides in `Game` uitgevoerd.
```cpp
private:
    sudoku::AbstractGame& m_game;
```

### 6. useful and correct object composition (explain why)
- Ik gebruik composition doordat `Board` een 2D-array van `Cell` bevat.
```cpp
private:
    Cell m_cells[Size][Size];
```

### 7. useful and correct base class
- `AbstractGame` is de base class voor de spel-logica en definieert welke functies elke game-implementatie moet hebben.
```cpp
class AbstractGame {
public:
    virtual ~AbstractGame() = default;
    virtual void reset() = 0;
    virtual void newGame(Difficulty difficulty) = 0;
    virtual Board& board() = 0;
    // ...
};
```

### 8. useful and correct abstract base class
- `AbstractGame` is een abstract base class met meerdere pure virtuele functies.
```cpp
class AbstractGame {
public:
    virtual ~AbstractGame() = default;
    virtual void reset() = 0;
    virtual void newGame(Difficulty difficulty) = 0;
    virtual Board& board() = 0;
    // ...
};
```

### 9. useful and correct virtual function
- `AbstractGame` bevat virtuele functies, bijvoorbeeld:
```cpp
virtual ~AbstractGame() = default;
```

### 10. no mistake in object-oriented programming
- In mijn huidige ontwerp volg ik de basisprincipes van OOP.
- Tot nu toe werkt de applicatie stabiel.
---

## Aanvullend
#### Algemeen
1. clean main (i.e. nothing in the main that should be in a class)
    - Mijn main is clean en bevat alleen de basis flow zonder business logic.
```cpp
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

```
2. no globals, but statics if needed
    - Ik gebruik geen globale variabelen.

3. correct protections
    - Ik gebruik correcte access modifiers (private, public, protected).
    - Member variabelen zijn private, alleen publieke interface is exposed.
    - Friend class `PlayerDataSerializer` (in PlayerStorage) heeft toegang tot private members van `Game` voor serialization en file I/O.

4. maintainability by clean uniform code style and good function naming and/or comments everywhere
    - Ik houd mijn code consistent en overzichtelijk.
    - Ik gebruik duidelijke functienamen zoals `getPlayerNameInput()`, `savePlayerData()`, `updateStatsWindow()`, en geef overal relevante comments.
  
5. separate header files
    - Ik geef elke class een aparte header (.h) en implementatie (.cpp) file, zoals `cell.h/cpp`, `board.h/cpp`, `game.h/cpp`, `mainwindow.h/cpp`, `PlayerStorage.h/cpp`, enzovoort.

6. one complete project that compiles and does not crash
    - Mijn project compileert zonder fouten en draait stabiel zonder te crashen.

7. fully working project
    - Volledig werkende Sudoku game met alle features geïmplementeerd.

8. sufficient git commits (+/- weekly)
    - Ik commit regelmatig (minimaal wekelijks) en beschrijf duidelijk de wijzigingen.

9. correct files on git
    - Ik zorg ervoor dat alleen relevante bronbestanden in git staan.
    - Build-bestanden en tijdelijke bestanden worden genegeerd via `.gitignore`.

10. working build manual as readme on GitHub (project must be possible to build from scratch on a clean PC)
    - In HowToRun.md geef ik duidelijke instructies zodat het project altijd vanaf een schone PC te bouwen is.
---

### OOP
1. at least 2 default constructors
    - Ik gebruik default constructors voor `Cell` en `Board` om objecten zonder parameters te initialiseren.
    - Deze gebruiken constructor forwarding om code duplicatie te voorkomen.
```cpp
// In cell.h, regel 12 en cell.cpp, regel 6-9
Cell();
Cell::Cell() : Cell(0, false) {}  // Forward naar parameterized constructor

// In board.h, regel 16 en board.cpp, regel 29-32
Board();
Board::Board() : Board(0) {}  // Forward naar parameterized constructor
```
2. at least 2 parameterized constructors
    - Ik maak objecten direct met waarden aan via parameterized constructors.
    - Ik heb minimaal 3 parameterized constructors: `Cell(int value, bool fixed)`, `Board(int fillValue)`, en `Board(const std::array<...>& values)`.
```cpp
// In cell.h, regel 14 en cell.cpp, regel 12-16
Cell(int value, bool fixed = false);
Cell::Cell(int value, bool fixed)
    : m_value(static_cast<std::uint8_t>(value)), m_fixed(fixed) {}

// In board.h, regel 18 en board.cpp, regel 35-43
explicit Board(int fillValue);
Board::Board(int fillValue) {
    for (int r = 0; r < Size; ++r) {
        for (int c = 0; c < Size; ++c) {
            m_cells[r][c].setValue(fillValue);
            m_cells[r][c].setFixed(false);
        }
    }
}

// Extra: Board heeft ook een constructor met std::array (board.h, regel 20 en board.cpp, regel 46-54)
Board(const std::array<std::array<int, Size>, Size>& values);
Board::Board(const std::array<std::array<int, Size>, Size>& values) {
    for (int r = 0; r < Size; ++r) {
        for (int c = 0; c < Size; ++c) {
            m_cells[r][c].setValue(values[r][c]);
            m_cells[r][c].setFixed(false);
        }
    }
}
```
3. at least 2 copy constructors
    - Ik kopieer objecten correct met copy constructors voor toewijzingen.
    - De copy constructors zorgen ervoor dat alle member variabelen correct worden gekopieerd.
```cpp
// In cell.h, regel 16 en cell.cpp, regel 19-23
Cell(const Cell& other);
Cell::Cell(const Cell& other)
    : m_value(other.m_value), m_fixed(other.m_fixed) {}

// In board.h, regel 22 en board.cpp, regel 65-73
Board(const Board& other);
Board::Board(const Board& other) {
    for (int r = 0; r < Size; ++r) {
        for (int c = 0; c < Size; ++c) {
            m_cells[r][c].setValue(other.m_cells[r][c].value());
            m_cells[r][c].setFixed(other.m_cells[r][c].isFixed());
        }
    }
}
```
4. at least 2 destructors
    - Ik ruim resources op met destructors bij verwijderen van objecten.
    - Ik heb destructors voor `Board`, `Game`, `MainWindow`, `WelcomeMsg`, en `PlayerStats`.
```cpp
// In board.h, regel 24 en board.cpp, regel 76-79
~Board();
Board::~Board() {
    clear();  // Ruim bord cellen op
}

// In game.h, regel 57 en game.cpp, regel 167-171
~Game() override;
Game::~Game() {
    m_board.clear();
    m_solution = {};  // Reset solution grid
}

// In mainwindow.h, regel 21 en mainwindow.cpp, regel 40-43
~MainWindow();
MainWindow::~MainWindow() {
    delete ui;  // Ruim UI pointer op
}

// In WelcomeMsg.h, regel 17 en WelcomeMsg.cpp, regel 22-25
~WelcomeMsg();
WelcomeMsg::~WelcomeMsg() {
    delete ui;  // Ruim UI pointer op
}

// In playerstats.h, regel 16 en playerstats.cpp, regel 11-14
~PlayerStats();
PlayerStats::~PlayerStats() {
    delete ui;  // Ruim UI pointer op
}
```
5. member initialization in constructors (the stuff behind a colon)
    - Ik initialiseer members efficiënt direct bij constructie met initializer lists.
    - Dit voorkomt onnodige default constructie en is efficiënter dan assignment in de constructor body.
```cpp
// In cell.cpp, regel 12-15
Cell::Cell(int value, bool fixed)
    : m_value(static_cast<std::uint8_t>(value)), m_fixed(fixed) {}

// In game.cpp, regel 158-163
Game::Game(Difficulty difficulty)
    : m_board(), m_difficulty(difficulty), m_solution{} {}

// In mainwindow.cpp, regel 18-24
MainWindow::MainWindow(sudoku::AbstractGame& game, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_game(game)
    , m_timer(new QTimer(this))
    , m_elapsedSeconds(0) {}
```
6. constructor forwarding
    - Ik voorkom dubbele code door default constructors te laten doorverwijzen naar parameterized constructors.
    - Dit vermindert code duplicatie en zorgt voor consistente initialisatie.
```cpp
// In cell.cpp, regel 6-9
Cell::Cell() : Cell(0, false) {}   // Forward naar Cell(int value, bool fixed)

// In board.cpp, regel 29-32
Board::Board() : Board(0) {}      // Forward naar Board(int fillValue)
```
7. useful proven (dynamic) polymorphism
    - Ik gebruik polymorfisme via abstracte interface `AbstractGame` met concrete implementatie `Game`.
    - De UI werkt met `AbstractGame&` maar krijgt een `Game` object, waardoor runtime polymorfisme wordt gebruikt.
    - Ik gebruik `dynamic_cast` om te controleren of het object een `Game` is voordat ik specifieke methoden aanroep.
```cpp
// In game.h, regel 52-59
class Game : public AbstractGame {
public:
    void reset() override;
    void newGame(Difficulty difficulty) override;
    // ... meer override methoden
};

// In mainwindow.cpp, regel 195-197 - dynamic_cast voor polymorfisme
if (auto* game = dynamic_cast<sudoku::Game*>(&m_game)) {
    game->registerFinishedGame(m_elapsedSeconds);
}
```
8. useful usage of "this" (if the code does not work without it)
    - Ik gebruik `this` als parent voor Qt-dialogen en widgets zodat ze correct werken en automatisch worden opgeruimd.
    - Zonder `this` zouden widgets niet correct worden opgeruimd en zouden dialogen niet modal werken.
```cpp
// In mainwindow.cpp, regel 200 - QMessageBox heeft this nodig als parent
QMessageBox::information(this, "Sudoku", "Gefeliciteerd! Het bord is volledig en correct.");

// In mainwindow.cpp, regel 22 - QTimer krijgt this als parent voor automatic cleanup
m_timer(new QTimer(this))

// In mainwindow.cpp, regel 334 - PlayerStats krijgt this als parent
m_statsWindow = new PlayerStats(this);

// In WelcomeMsg.cpp, regel 59 - QInputDialog heeft this nodig als parent
QString playerName = QInputDialog::getText(this, "New Player", ...);
```
9. useful member function
    - Ik controleer objecttoestand met member functies zoals `isValid()`, `isComplete()`, `isFixed()`, etc.
    - Deze functies encapsuleren de logica voor het controleren van de toestand van het object.
```cpp
// In board.h, regel 48-49
bool isComplete() const;
bool isValid() const;

// In board.cpp, regel 193-203 - implementatie van isComplete
bool Board::isComplete() const {
    for (int r = 0; r < Size; ++r) {
        for (int c = 0; c < Size; ++c) {
            if (valueAt(r, c) == 0) {
                return false;
            }
        }
    }
    return true;
}

// In cell.h, regel 21
bool isFixed() const;
```
10. default values in function definition
    - Ik maak functies flexibeler met standaardwaarden voor parameters.
    - Dit maakt functies makkelijker te gebruiken zonder alle parameters te hoeven specificeren.
```cpp
// In cell.h, regel 14 - default waarde voor fixed parameter
Cell(int value, bool fixed = false);

// In game.h, regel 55 - default waarde voor difficulty parameter
explicit Game(Difficulty difficulty = Difficulty::Easy);

// In game.h, regel 63 - default waarde voor onComplete callback
std::future<void> newGameAsync(Difficulty difficulty, std::function<void()> onComplete = nullptr);
```
11. useful member variable
    - Ik bewaar objecttoestand in member variabelen zoals het bord, difficulty, solution grid, en statistieken.
    - Deze variabelen zijn private en worden alleen via publieke methoden benaderd (encapsulation).
```cpp
// In board.h, regel 55 - Board bevat een 2D array van Cell objecten
Cell m_cells[Size][Size];

// In game.h, regel 97-105 - Game bevat board, difficulty, solution, en statistieken
Board m_board;
Difficulty m_difficulty;
Grid m_solution;
int m_gamesPlayed = 0;
int m_gamesWon = 0;
int m_bestTimeSeconds = -1;
long m_totalTimeSeconds = 0;
std::string m_playerName;
```
12. useful getters and setters for member variables
    - Ik geef gecontroleerde toegang tot private data via getters en setters.
    - Dit zorgt voor encapsulation en controle over hoe data wordt gelezen en geschreven.
```cpp
// In cell.h, regel 18-19 en cell.cpp, regel 25-36
int value() const;
void setValue(int v);
int Cell::value() const { return m_value; }
void Cell::setValue(int v) {
    if (v < 0) v = 0;
    if (v > 9) v = 9;
    m_value = static_cast<std::uint8_t>(v);
}

// In cell.h, regel 21-22 en cell.cpp, regel 38-46
bool isFixed() const;
void setFixed(bool fixed);

// In game.h, regel 79-87 - getters voor statistieken
int gamesPlayed() const { return m_gamesPlayed; }
int gamesWon() const { return m_gamesWon; }
const std::string& playerName() const { return m_playerName; }
void setPlayerName(const std::string& name) { m_playerName = name; }
```
13. correct usage of inline function
    - Ik gebruik inline functies voor snelle checks zonder function call overhead.
    - De functie `isInside()` is inline gedefinieerd in de header omdat het een kleine, veelgebruikte functie is.
```cpp
// In board.h, regel 38-41 - inline functie in header
bool isInside(int row, int col) const {
    return row >= 0 && row < Size && col >= 0 && col < Size;
}

// Deze functie wordt gebruikt in board.cpp, regel 59, 123 voor bounds checking
```
14. useful template function or class
    - Ik gebruik templates voor herbruikbare generieke code voor duplicate checks.
    - De template functie `hasDuplicateValue` werkt met elke functie die een waarde kan leveren (via lambda's).
```cpp
// In board.cpp, regel 8-25 - template functie voor duplicate detection
template<typename ValueProvider>
bool hasDuplicateValue(ValueProvider&& provider, int count) {
    bool seen[10] = { false };
    for (int idx = 0; idx < count; ++idx) {
        int v = provider(idx);
        if (v == 0) continue;
        if (seen[v]) return true;
        seen[v] = true;
    }
    return false;
}

// Gebruikt in board.cpp, regel 166-170 voor row conflict check
bool Board::rowHasConflict(int row) const {
    return hasDuplicateValue([this, row](int idx) {
        return valueAt(row, idx);
    }, Size);
}
```
15. useful friend function or class
    - Ik gebruik een friend class `PlayerDataSerializer` voor file I/O zonder private members publiek te maken.
    - De friend class heeft toegang tot private members zoals `m_playerName`, `m_gamesPlayed`, `m_gamesWon`, etc. voor serialisatie.
```cpp
// In game.h, regel 111 - friend class declaratie
friend class PlayerDataSerializer;

// In PlayerStorage.h, regel 12-37 - friend class definitie
class PlayerDataSerializer {
public:
    class FileIOException : public std::runtime_error {
        explicit FileIOException(const std::string& message)
            : std::runtime_error("File I/O Error: " + message) {}
    };
    static void save(const Game& game);
    static void load(Game& game, const std::string& playerName);
};

// In PlayerStorage.cpp, regel 48-52 - directe toegang tot private members
void PlayerDataSerializer::save(const Game& game) {
    file << game.m_playerName << "\n";      // Private member access
    file << game.m_gamesPlayed << "\n";    // Private member access
    file << game.m_gamesWon << "\n";       // Private member access
    file << game.m_bestTimeSeconds << "\n";
    file << game.m_totalTimeSeconds << "\n";
}
```
---

### C++
1. everything in one or more self-made namespace(s)
    - Ik plaats alle Sudoku-gerelateerde klassen en functies in de namespace `sudoku` voor overzicht en naamconflictpreventie.
    - Alle core game klassen (`Cell`, `Board`, `Game`, `AbstractGame`, `PlayerDataSerializer`) staan in deze namespace.
```cpp
// In cell.h, regel 6-29
namespace sudoku {
    class Cell { /* ... */ };
}

// In board.h, regel 8-64
namespace sudoku {
    class Board { /* ... */ };
}

// In game.h, regel 13-114
namespace sudoku {
    class AbstractGame { /* ... */ };
    class Game : public AbstractGame { /* ... */ };
}

// In PlayerStorage.h, regel 9-39
namespace sudoku {
    class PlayerDataSerializer { /* ... */ };
}
```
2. 2 useful unsigned chars or other better usage of memory efficient type
    - Ik gebruik `std::uint8_t` op twee verschillende plaatsen voor geheugenefficiënte opslag:
      1. Voor individuele cell-waarden in de `Cell` klasse (waarden 0-9 passen perfect in 1 byte in plaats van 4 bytes met int)
      2. Voor het complete solution grid via een type alias `Grid` (81 cellen × 1 byte = 81 bytes in plaats van 81 × 4 bytes = 324 bytes met int)
    - Dit bespaart significant geheugen, vooral bij het solution grid.
```cpp
// Eerste gebruik: member variable in Cell klasse (cell.h, regel 25)
std::uint8_t m_value;  // Opslag van individuele cell waarde (0-9) - 1 byte in plaats van 4 bytes

// Tweede gebruik: type alias voor 2D grid (game.h, regel 15)
using Grid = std::array<std::array<std::uint8_t, 9>, 9>;

// Grid wordt gebruikt als member variable (game.h, regel 99)
Grid m_solution;  // Complete solution grid met uint8_t voor memory efficiency
// 81 cellen × 1 byte = 81 bytes vs 81 × 4 bytes = 324 bytes met int
```
3. at least 4 useful const references for variables
    - Ik gebruik const-referenties als lokale variabelen om onnodige kopieën te voorkomen en data te beschermen.
    - Dit voorkomt onnodige kopieën van grote objecten zoals Board en QString.
```cpp
// Local const reference variable (mainwindow.cpp, regel 104)
const sudoku::Board& board = m_game.board();

// Local const reference variable (mainwindow.cpp, regel 161)
const QString& text = item->text().trimmed();

// Local const reference variable (mainwindow.cpp, regel 156-158)
const QColor& baseBg = lightBlock
    ? QColor(250, 250, 250)
    : QColor(230, 230, 230);

// Local const reference variable (mainwindow.cpp, regel 224)
const QColor& baseBg = lightBlock
    ? QColor(250, 250, 250)
    : QColor(230, 230, 230);

// Local const reference variable (mainwindow.cpp, regel 281)
const QString& text = ui->comboDifficulty->currentText();

// Local const reference variable (game.cpp, regel 277)
const Grid& full = generateSolvedGrid();
```
4. at least 4 useful const references for functions
    - Ik gebruik const-referenties in functie parameters en return types om kopieën te voorkomen.
    - Const-referenties in parameters beschermen tegen onbedoelde wijzigingen.
```cpp
// Const reference return type (game.h, regel 37 en game.cpp, regel 230-233)
virtual const Board& board() const = 0;
const Board& Game::board() const { return m_board; }

// Const reference return type (board.h, regel 29 en board.cpp, regel 96-99)
const Cell& cellAt(int row, int col) const;
const Cell& Board::cellAt(int row, int col) const { return m_cells[row][col]; }

// Const reference parameter (board.h, regel 35 en board.cpp, regel 57-62)
void updateCell(int row, int col, const Cell& cell);
void Board::updateCell(int row, int col, const Cell& cell) { /* ... */ }

// Const reference parameter (PlayerStorage.h, regel 24)
static void save(const Game& game);

// Const reference parameter (PlayerStorage.h, regel 27)
static void load(Game& game, const std::string& playerName);

// Const reference return type (game.h, regel 86)
const std::string& playerName() const { return m_playerName; }
```
5. at least 4 useful bool
    - Ik gebruik bools voor statuswaarden zoals fixed cells, validiteit checks, en game state.
    - Bools zijn efficiënt en duidelijk voor true/false waarden.
```cpp
// Member variable (cell.h, regel 26)
bool m_fixed;  // Geeft aan of cel vast is (niet editable)

// Member function return type (cell.h, regel 21)
bool isFixed() const;  // Controleert of cel fixed is

// Member function return type (board.h, regel 48-49)
bool isComplete() const;  // Controleert of bord volledig is
bool isValid() const;     // Controleert of bord geldig is

// Member function return type (game.h, regel 41-42)
virtual bool isFinished() const = 0;  // Controleert of spel klaar is
virtual bool isValid() const = 0;     // Controleert of bord geldig is

// Member variable (WelcomeMsg.h, regel 30)
bool m_isNewGame = false;  // Geeft aan of nieuwe game of load game
```
6. dynamic memory allocation (new)
    - Ik alloceer dynamisch geheugen voor Qt-widgets en UI-elementen.
    - Qt gebruikt new/delete voor object ownership management.
```cpp
// In mainwindow.cpp, regel 20 - UI object allocation
ui = new Ui::MainWindow;

// In mainwindow.cpp, regel 22 - QTimer allocation met parent
m_timer = new QTimer(this);

// In mainwindow.cpp, regel 87 - QTableWidgetItem allocation
auto *item = new QTableWidgetItem;

// In mainwindow.cpp, regel 115 - QTableWidgetItem allocation
item = new QTableWidgetItem;

// In mainwindow.cpp, regel 334 - PlayerStats window allocation
m_statsWindow = new PlayerStats(this);

// In WelcomeMsg.cpp, regel 15 - UI object allocation
ui(new Ui::WelcomeMsg)

// In playerstats.cpp, regel 6 - UI object allocation
ui(new Ui::PlayerStats)
```
7. dynamic memory removing (delete)
    - Ik ruim dynamisch geheugen op om memory leaks te voorkomen.
    - Alle destructors zorgen voor correcte cleanup van dynamisch gealloceerd geheugen.
```cpp
// In mainwindow.cpp, regel 42 - UI cleanup
delete ui;

// In WelcomeMsg.cpp, regel 24 - UI cleanup
delete ui;

// In playerstats.cpp, regel 13 - UI cleanup
delete ui;

// Qt widgets met parent worden automatisch opgeruimd wanneer parent wordt verwijderd
// (m_timer, m_statsWindow worden automatisch opgeruimd door Qt parent-child systeem)
```
8. 2 useful (modern) call-by-references
    - Ik geef parameters efficiënt door via non-const referenties zonder kopieën.
    - Non-const referenties worden gebruikt wanneer het object moet worden gewijzigd.
```cpp
// Non-const reference parameter (PlayerStorage.h, regel 27 en PlayerStorage.cpp, regel 66)
static void load(Game& game, const std::string& playerName);
void PlayerDataSerializer::load(Game& game, const std::string& playerName) {
    game.m_playerName = line;  // Wijzigt game object
}

// Non-const reference parameter (gameinitializer.h, regel 13 en gameinitializer.cpp, regel 5)
static bool createGameFromDialog(sudoku::Game& game);
bool GameInitializer::createGameFromDialog(sudoku::Game& game) {
    // Wijzigt game object
}

// Non-const reference parameter (gameinitializer.h, regel 17)
static bool initializeGame(sudoku::Game& game, const QString& playerName, bool isNewGame);

// Non-const reference return type (game.h, regel 65 en game.cpp, regel 225-228)
Board& board() override;
Board& Game::board() { return m_board; }

// Non-const reference return type (board.h, regel 28 en board.cpp, regel 91-94)
Cell& cellAt(int row, int col);
Cell& Board::cellAt(int row, int col) { return m_cells[row][col]; }
```
9. useful string class usage
    - Ik gebruik string classes (`std::string` en `QString`) voor tekstopslag en gebruikersinvoer.
    - `std::string` voor C++ core logica, `QString` voor Qt UI operaties.
```cpp
// std::string voor player name opslag (game.h, regel 105)
std::string m_playerName;

// std::string in functie parameters (PlayerStorage.h, regel 27, 30, 36)
static void load(Game& game, const std::string& playerName);
static bool playerFileExists(const std::string& playerName);
static std::string getPlayerDataPath(const std::string& playerName);

// QString voor UI tekst (mainwindow.cpp, regel 120, 161, 281)
item->setText(v == 0 ? QString() : QString::number(v));
const QString& text = item->text().trimmed();
const QString& text = ui->comboDifficulty->currentText();

// QString voor player input (WelcomeMsg.h, regel 19, 29)
QString selectedPlayerName() const { return m_selectedPlayerName; }
QString m_selectedPlayerName;
```
10. useful container class
    - Ik gebruik containers zoals `std::array` voor efficiënte bord-opslag en `std::vector` voor dynamische lijsten.
    - C-style arrays voor fixed-size data, std::array voor type-safe fixed-size containers, std::vector voor dynamische groei.
```cpp
// C-style array voor Board cellen (board.h, regel 55)
Cell m_cells[Size][Size];  // Fixed-size 9x9 array

// std::array voor Grid type alias (game.h, regel 15)
using Grid = std::array<std::array<std::uint8_t, 9>, 9>;

// std::array in functie (game.cpp, regel 67)
std::array<int, 9> nums = {1,2,3,4,5,6,7,8,9};

// std::array parameter (board.h, regel 20)
Board(const std::array<std::array<int, Size>, Size>& values);

// std::vector voor player lijsten (game.h, regel 94 en game.cpp, regel 359-367)
static std::vector<std::string> listAvailablePlayers();
std::vector<std::string> Game::listAvailablePlayers() {
    return PlayerDataSerializer::listPlayers();
}

// std::vector voor indices (game.cpp, regel 104)
std::vector<int> indices(totalCells);
```
11. useful usage of nullptr
    - Ik initialiseer pointers met `nullptr` voor veiligheid en duidelijkheid.
    - `nullptr` is moderner en veiliger dan NULL of 0 voor pointers.
```cpp
// Pointer initialisatie (mainwindow.h, regel 29)
PlayerStats* m_statsWindow = nullptr;

// Pointer reset na cleanup (mainwindow.cpp, regel 338)
connect(m_statsWindow, &QObject::destroyed, this, [this]() {
    m_statsWindow = nullptr;  // Reset pointer na widget destruction
});

// nullptr als default parameter (game.h, regel 63)
std::future<void> newGameAsync(Difficulty difficulty, std::function<void()> onComplete = nullptr);
```
12. useful usage of (modern) file-I/O
    - Ik gebruik moderne C++ file I/O met `std::ofstream` en `std::ifstream` samen met `std::filesystem`.
    - File I/O is netjes gescheiden in een aparte friend class `PlayerDataSerializer` voor encapsulation.
```cpp
// In PlayerStorage.cpp
// Writing player data (regel 40-54)
std::ofstream file(filePath, std::ios::out | std::ios::trunc);
if (!file.is_open()) {
    throw FileIOException("Cannot open file for writing: " + filePath);
}
file << game.m_playerName << "\n";
file << game.m_gamesPlayed << "\n";
file << game.m_gamesWon << "\n";
file << game.m_bestTimeSeconds << "\n";
file << game.m_totalTimeSeconds << "\n";
file.close();

// Reading player data (regel 76-130)
std::ifstream file(filePath, std::ios::in);
if (!file.is_open()) {
    throw FileIOException("Cannot open file for reading: " + filePath);
}
std::string line;
std::getline(file, line);
game.m_playerName = line;
// ... meer data lezen ...

// Directory operations met std::filesystem (regel 11-18, 156-174)
std::filesystem::path savesDir = "saves";
if (!std::filesystem::exists(savesDir)) {
    std::filesystem::create_directories(savesDir);
}
for (const auto& entry : std::filesystem::directory_iterator(savesDir)) {
    if (entry.is_regular_file() && entry.path().extension() == ".dat") {
        // Process player files...
    }
}
```
13. useful exception handling
    - Ik gebruik try-catch blocks voor robuuste error handling bij file I/O en thread operaties.
    - Custom exception class `FileIOException` voor specifieke fouten die duidelijk zijn voor de gebruiker.
    - Exception handling wordt gebruikt in `PlayerStorage.cpp` voor file I/O operaties, in `game.cpp` voor thread operaties, en in `gameinitializer.cpp` voor game initialisatie.
```cpp
// Custom exception class in PlayerStorage.h, regel 16-21
class FileIOException : public std::runtime_error {
public:
    explicit FileIOException(const std::string& message)
        : std::runtime_error("File I/O Error: " + message) {}
};

// Exception handling in PlayerStorage.cpp, regel 34-63
void PlayerDataSerializer::save(const Game& game) {
    try {
        if (game.m_playerName.empty()) {
            throw FileIOException("Player name is empty");
        }
        std::string filePath = getPlayerDataPath(game.m_playerName);
        std::ofstream file(filePath, std::ios::out | std::ios::trunc);
        if (!file.is_open()) {
            throw FileIOException("Cannot open file for writing: " + filePath);
        }
        // ... file operations ...
    } catch (const std::filesystem::filesystem_error& e) {
        throw FileIOException("Filesystem error: " + std::string(e.what()));
    } catch (const std::exception& e) {
        throw FileIOException("Unexpected error: " + std::string(e.what()));
    }
}

// Exception handling in game.cpp, regel 193-221 (thread operations)
std::future<void> Game::newGameAsync(Difficulty difficulty, std::function<void()> onComplete) {
    return std::async(std::launch::async, [this, difficulty, onComplete]() {
        try {
            auto [full, puzzle] = generatePuzzle(difficulty);
            // ... thread work ...
        } catch (const std::exception& e) {
            std::cerr << "Error generating puzzle in thread: " << e.what() << std::endl;
            setupInitialBoard(); // Fallback
        }
    });
}

// Exception handling in gameinitializer.cpp, regel 16-32
bool GameInitializer::initializeGame(sudoku::Game& game, const QString& playerName, bool isNewGame) {
    try {
        if (isNewGame) {
            game.setPlayerName(playerName.toStdString());
            if (!game.savePlayerData()) {
                std::cerr << "Warning: Failed to save initial player data" << std::endl;
            }
        } else {
            if (!game.loadPlayerData(playerName.toStdString())) {
                std::cerr << "Failed to load player data" << std::endl;
                return false;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error initializing game: " << e.what() << std::endl;
        return false;
    }
    return true;
}
```
14. useful usage of lambda function
    - Ik gebruik lambdas voor compacte inline functies in template code, Qt connect statements, en thread callbacks.
    - Lambdas maken code korter en duidelijker zonder aparte functies te hoeven definiëren.
```cpp
// Lambda in template function call voor row conflict (board.cpp, regel 166-170)
bool Board::rowHasConflict(int row) const {
    return hasDuplicateValue([this, row](int idx) {
        return valueAt(row, idx);
    }, Size);
}

// Lambda in template function call voor column conflict (board.cpp, regel 175-179)
bool Board::columnHasConflict(int col) const {
    return hasDuplicateValue([this, col](int idx) {
        return valueAt(idx, col);
    }, Size);
}

// Lambda in template function call voor block conflict (board.cpp, regel 184-190)
bool Board::blockHasConflict(int startRow, int startCol) const {
    return hasDuplicateValue([this, startRow, startCol](int idx) {
        int r = startRow + idx / 3;
        int c = startCol + idx % 3;
        return valueAt(r, c);
    }, 9);
}

// Lambda in Qt connect voor cleanup (mainwindow.cpp, regel 337-339)
connect(m_statsWindow, &QObject::destroyed, this, [this]() {
    m_statsWindow = nullptr;
});

// Lambda in std::async voor thread work (game.cpp, regel 193-222)
return std::async(std::launch::async, [this, difficulty, onComplete]() {
    try {
        auto [full, puzzle] = generatePuzzle(difficulty);
        // ... thread work ...
    } catch (const std::exception& e) {
        std::cerr << "Error generating puzzle in thread: " << e.what() << std::endl;
        setupInitialBoard();
    }
});

// Lambda in playerstats.cpp voor time formatting (regel 24-33)
auto formatTime = [](int seconds) -> QString {
    if (seconds < 0) return "-";
    int minutes = seconds / 60;
    int secs = seconds % 60;
    return QString("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(secs, 2, 10, QLatin1Char('0'));
};
```
15. useful usage of threads
    - Ik gebruik `std::async` voor background puzzle generation zodat de UI responsief blijft tijdens CPU-intensive operaties.
    - `std::async` gebruikt intern `std::thread` voor asynchrone uitvoering van puzzle generatie.
    - Thread operaties zijn wrapped in exception handling voor robuustheid.
```cpp
// In game.h, regel 63 - async functie declaratie
std::future<void> newGameAsync(Difficulty difficulty, std::function<void()> onComplete = nullptr);

// In game.cpp, regel 186-223 - async implementatie met thread
std::future<void> Game::newGameAsync(Difficulty difficulty, std::function<void()> onComplete) {
    m_difficulty = difficulty;
    ++m_gamesPlayed;
    
    // Launch puzzle generation in a separate thread using std::async
    // std::async gebruikt intern std::thread voor asynchrone uitvoering
    return std::async(std::launch::async, [this, difficulty, onComplete]() {
        try {
            // Generate puzzle in background thread (CPU-intensive operation)
            // Dit voorkomt dat de UI bevriest tijdens puzzle generatie
            auto [full, puzzle] = generatePuzzle(difficulty);
            
            // Store results (thread-safe voor deze use case)
            m_solution = full;
            
            // Apply puzzle to board
            m_board.clear();
            for (int r = 0; r < Board::Size; ++r) {
                for (int c = 0; c < Board::Size; ++c) {
                    int v = puzzle[r][c];
                    m_board.setValue(r, c, v);
                    m_board.setFixed(r, c, v != 0);
                }
            }
            
            // Call completion callback if provided
            if (onComplete) {
                onComplete();
            }
        } catch (const std::exception& e) {
            std::cerr << "Error generating puzzle in thread: " << e.what() << std::endl;
            // Fallback to synchronous generation on error
            setupInitialBoard();
        }
    });
}
```

---

## Uitbreiding
1. useful Qt class
    - Ik gebruik verschillende Qt klassen zoals `QMainWindow`, `QTableWidget`, `QTimer`, `QMessageBox`, `QDialog`, `QApplication`, etc.
    - `MainWindow` erft van `QMainWindow` (mainwindow.h, regel 14)
    - `QTimer` wordt gebruikt voor de game timer (mainwindow.cpp, regel 22, 34-35)
    - `QTableWidget` wordt gebruikt voor het Sudoku bord (mainwindow.cpp, regel 47-97)
    - `QMessageBox` wordt gebruikt voor gebruikersmeldingen (mainwindow.cpp, regel 200, 248, etc.)

2. useful usage of signals/slots
    - Ik gebruik Qt's signal/slot mechanisme voor event-driven programming.
    - Connecties tussen signals en slots worden gemaakt met `connect()`.
```cpp
// In mainwindow.cpp, regel 31-35
connect(ui->tableSudoku, &QTableWidget::cellChanged,
        this, &MainWindow::onCellChanged);
connect(m_timer, &QTimer::timeout,
        this, &MainWindow::updateTimer);
connect(m_statsWindow, &QObject::destroyed, this, [this]() {
    m_statsWindow = nullptr;
});

// In WelcomeMsg.cpp, regel 136-137
connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
```

3. test-driven development (= written test plan or unit tests)
4. solve bug ticket (with pull request or commit message issue link and issue branch)
5. report a bug ticket on another project
6. usage of a GUI
    - Volledige GUI applicatie met Qt framework.
    - `MainWindow` bevat een interactief Sudoku bord met `QTableWidget`.
    - Dialogen voor player selectie (`WelcomeMsg`) en statistieken (`PlayerStats`).
7. usage of OpenGL or other 3D engine
8. useful usage of an external library (not Qt)
9. project that communicates (e.g. UART, BT) with hardware
10. a nice extra that you think that should deserve grading (stuff you put time in and is not rewarded by an item above)