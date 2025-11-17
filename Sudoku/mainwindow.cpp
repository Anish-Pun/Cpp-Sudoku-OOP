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

MainWindow::MainWindow(sudoku::Game& game, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_game(game)
{
    ui->setupUi(this);

    setupBoardAppearance();
    loadFromGame();

    // if cell changes then sync with the game ui aswel
    connect(ui->tableSudoku, &QTableWidget::cellChanged,
            this, &MainWindow::onCellChanged);
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
            int v = board.valueAt(row, col);
            QTableWidgetItem* item = table->item(row, col);
            if (!item) {
                item = new QTableWidgetItem;
                item->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, col, item);
            }
            item->setText(v == 0 ? QString() : QString::number(v));
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

    const QString text = item->text().trimmed();
    int newValue = 0;

    if (!text.isEmpty()) {
        bool ok = false;
        int parsed = text.toInt(&ok);
        if (!ok || parsed < 1 || parsed > 9) {
            QSignalBlocker blocker(table);
            loadFromGame();
            return;
        }
        newValue = parsed;
    }

    // Probeer move in Game
    if (!m_game.setCell(row, column, newValue)) {
        // Ongeldige zet volgens Sudoku-regels -> revert
        QSignalBlocker blocker(table);
        loadFromGame();
    }
}

// Checking if ui btns works
void MainWindow::on_btnCheck_clicked()
{
    const sudoku::Board& board = m_game.board();

    bool complete = board.isComplete(); // check if every cell is completed
    bool valid    = board.isValid();     // check for valid cell

    if (valid && complete) {
        QMessageBox::information(this, "Sudoku",
                                 "Gefeliciteerd! Het bord is volledig en correct.");
    } else if (valid && !complete) {
        QMessageBox::information(this, "Sudoku",
                                 "Alle ingevulde cijfers zijn geldig,\nmaar het bord is nog niet compleet.");
    } else {
        QMessageBox::warning(this, "Sudoku",
                             "Er zitten fouten in het bord.\nControleer rijen, kolommen en 3x3 blokken.");
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

    qDebug() << "New game started with difficulty" << ui->comboDifficulty->currentText();
}
