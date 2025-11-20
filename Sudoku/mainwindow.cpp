#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "game.h"          // sudoku::Game
#include "board.h"         // sudoku::Board

#include <QHeaderView>
#include <QFont>
#include <QBrush>
#include <QColor>
#include <QTableWidgetItem>
#include <QSignalBlocker>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(sudoku::AbstractGame& game, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_game(game)
    , m_timer(new QTimer(this))
    , m_elapsedSeconds(0)
{
    ui->setupUi(this);

    setupBoardAppearance();
    loadFromGame();

    // if cell changes then sync with the game ui aswel
    connect(ui->tableSudoku, &QTableWidget::cellChanged,
            this, &MainWindow::onCellChanged);
    //Timer Update every seconds
    connect(m_timer, &QTimer::timeout,
            this, &MainWindow::updateTimer);

    on_btnNewGame_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupBoardAppearance()
{
    auto table = ui->tableSudoku;

    table->clear();
    table->setRowCount(9);
    table->setColumnCount(9);

    table->horizontalHeader()->setVisible(false);
    table->verticalHeader()->setVisible(false);

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectItems);
    table->setEditTriggers(QAbstractItemView::AllEditTriggers);

    table->setShowGrid(true);
    table->setGridStyle(Qt::SolidLine);

    const int cellSize = 48;
    table->horizontalHeader()->setDefaultSectionSize(cellSize);
    table->verticalHeader()->setDefaultSectionSize(cellSize);

    const int size = cellSize * 9 + 2 * table->frameWidth();
    table->setMinimumSize(size, size);
    table->setMaximumSize(size, size);

    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QFont f = table->font();
    f.setPointSize(16);
    f.setBold(true);
    table->setFont(f);

    table->setStyleSheet("QTableWidget { gridline-color: #404040; }");

    // Maak items met 3x3 blok achtergrond
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            auto *item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);

            bool lightBlock = ((row / 3) + (col / 3)) % 2 == 0;
            QColor bg = lightBlock ? QColor(250, 250, 250)
                                   : QColor(230, 230, 230);
            item->setBackground(QBrush(bg));

            table->setItem(row, col, item);
        }
    }
}

// Board -> UI
void MainWindow::loadFromGame()
{
    auto table = ui->tableSudoku;
    const sudoku::Board& board = m_game.board();

    QSignalBlocker blocker(table);

    for (int row = 0; row < sudoku::Board::Size; ++row) {
        for (int col = 0; col < sudoku::Board::Size; ++col) {
            int  v     = board.valueAt(row, col);
            bool fixed = board.isFixed(row, col);

            QTableWidgetItem* item = table->item(row, col);
            if (!item) {
                item = new QTableWidgetItem;
                item->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, col, item);
            }

            item->setText(v == 0 ? QString() : QString::number(v));

            // flags: fixed = niet editable, user = editable
            Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
            if (!fixed) {
                flags |= Qt::ItemIsEditable;
            }
            item->setFlags(flags);

            // stijl: fixed = bold + donkerder, user = normaal
            QFont f = item->font();
            if (fixed) {
                f.setBold(true);
                item->setFont(f);
                item->setForeground(QBrush(QColor(0, 0, 0)));
            } else {
                f.setBold(false);
                item->setFont(f);
                item->setForeground(QBrush(QColor(50, 50, 50)));
            }
        }
    }
}

// UI -> Game
void MainWindow::onCellChanged(int row, int column)
{
    auto table = ui->tableSudoku;

    QTableWidgetItem* item = table->item(row, column);
    if (!item) {
        return;
    }

    // achtergrond terugzetten naar het normale 3x3-blok patroon
    bool   lightBlock = ((row / 3) + (column / 3)) % 2 == 0;
    QColor baseBg     = lightBlock
                        ? QColor(250, 250, 250)
                        : QColor(230, 230, 230);
    item->setBackground(QBrush(baseBg));

    QString text = item->text().trimmed();
    int value = 0;

    // Leeg laten = 0 in het bord
    if (!text.isEmpty()) {
        bool ok = false;
        int v = text.toInt(&ok);
        if (!ok || v < 1 || v > 9) {
            // Ongeldige input: reset naar bord-state
            QSignalBlocker blocker(table);
            loadFromGame();
            return;
        }
        value = v;
    }

    //vraag aan Game of deze zet mag
    bool accepted = m_game.setCell(row, column, value);
    if (!accepted) {
        QSignalBlocker blocker(table);
        loadFromGame();
        return;
    }

    // zet is OK → bord opnieuw inladen
    {
        QSignalBlocker blocker(table);
        loadFromGame();
    }

    // check meteen of het spel gewonnen is
    if (m_game.isFinished()) {
        m_timer->stop();  // stop timer

        QMessageBox::information(this, "Sudoku",
                                 "Gefeliciteerd! Het bord is volledig en correct.");
    }
}


// Checking if ui btns works
void MainWindow::on_btnCheck_clicked()
{
    auto  table = ui->tableSudoku;
    const sudoku::Board& board = m_game.board();

    QSignalBlocker blocker(table);  // geen cellChanged-events tijdens kleur-update

    bool anyError = false;
    bool complete = board.isComplete();

    for (int row = 0; row < sudoku::Board::Size; ++row) {
        for (int col = 0; col < sudoku::Board::Size; ++col) {
            QTableWidgetItem* item = table->item(row, col);
            if (!item) continue;

            // 1) basis-achtergrond (3x3 blok patroon)
            bool lightBlock = ((row / 3) + (col / 3)) % 2 == 0;
            QColor baseBg = lightBlock
                                ? QColor(250, 250, 250)
                                : QColor(230, 230, 230);
            item->setBackground(QBrush(baseBg));

            // 2) fouten markeren in rood
            int  v     = board.valueAt(row, col);
            bool fixed = board.isFixed(row, col);

            // alleen door de speler ingevulde vakjes controleren
            if (!fixed && v != 0) {
                int correct = m_game.solutionAt(row, col);

                if (v != correct) {
                    anyError = true;
                    item->setBackground(QBrush(QColor(255, 200, 200))); // lichtrood
                }
            }
        }
    }

    // 3) Bericht tonen
    if (!complete) {
        if (anyError) {
            QMessageBox::warning(
                this,
                "Sudoku",
                "Er zitten fouten in het bord (rood gemarkeerd) en het is nog niet volledig."
                );
        } else {
            QMessageBox::information(
                this,
                "Sudoku",
                "Het bord is nog niet volledig. Ga gerust verder!"
                );
        }
    } else {
        if (anyError) {
            QMessageBox::warning(
                this,
                "Sudoku",
                "Het bord is volledig, maar bevat fouten (rood gemarkeerd)."
                );
        } else {
            // volledig én geen fouten → gewonnen
            m_timer->stop();
            QMessageBox::information(
                this,
                "Sudoku",
                "Gefeliciteerd! Het bord is volledig en correct."
                );
        }
    }
}

static sudoku::Difficulty difficultyFromCombo(Ui::MainWindow* ui)
{
    const QString text = ui->comboDifficulty->currentText();
    if (text == "Medium")
        return sudoku::Difficulty::Medium;
    if (text == "Hard")
        return sudoku::Difficulty::Hard;
    return sudoku::Difficulty::Easy;
}

void MainWindow::on_btnNewGame_clicked()
{
    auto diff = difficultyFromCombo(ui);

    m_game.newGame(diff);  // kiest random puzzle op basis van difficulty
    loadFromGame();        // Board -> UI

    m_elapsedSeconds = 0;
    ui->labelTimer->setText("Time: 00:00");
    m_timer->start(1000);  // elke 1000 ms -> updateTimer()

    qDebug() << "New game started with difficulty" << ui->comboDifficulty->currentText();
}

void MainWindow::on_btnSolve_clicked()
{
    m_game.solve();

    // Timer stoppen
    m_timer->stop();

    // UI updaten
    {
        QSignalBlocker blocker(ui->tableSudoku);
        loadFromGame();
    }

    QMessageBox::information(
        this,
        "Sudoku",
        "De oplossing is ingevuld."
        );
}

void MainWindow::updateTimer()
{
    ++m_elapsedSeconds;

    int minutes = m_elapsedSeconds / 60;
    int seconds = m_elapsedSeconds % 60;

    ui->labelTimer->setText(
        QString("Time: %1:%2")
            .arg(minutes, 2, 10, QLatin1Char('0'))
            .arg(seconds, 2, 10, QLatin1Char('0'))
        );
}
