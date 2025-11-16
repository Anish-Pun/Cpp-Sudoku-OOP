#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QHeaderView>
#include <QFont>
#include <QBrush>
#include <QColor>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupBoard()
{
    auto table = ui->tableSudoku;

    // bais 9x9
    table->clear();
    table->setRowCount(9);
    table->setColumnCount(9);

    table->horizontalHeader()->setVisible(false);
    table->verticalHeader()->setVisible(false);

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectItems);
    table->setEditTriggers(QAbstractItemView::AllEditTriggers); // making cells editable

    table->setShowGrid(true);
    table->setGridStyle(Qt::SolidLine);

    // make cells square
    const int cellSize = 48;
    table->horizontalHeader()->setDefaultSectionSize(cellSize);
    table->verticalHeader()->setDefaultSectionSize(cellSize);

    const int size = cellSize * 9 + 2 * table->frameWidth();
    table->setMinimumSize(size, size);
    table->setMaximumSize(size, size);

    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // fonts for the numbers
    QFont f = table->font();
    f.setPointSize(16);
    f.setBold(true);
    table->setFont(f);

    // darker grid lines
    table->setStyleSheet("QTableWidget { gridline-color: #404040; }");

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            auto *item = new QTableWidgetItem;
            item->setText(QString());                // start empty
            item->setTextAlignment(Qt::AlignCenter);

            bool lightBlock = ((row / 3) + (col / 3)) % 2 == 0;
            QColor bg = lightBlock ? QColor(250, 250, 250)
                                   : QColor(230, 230, 230);
            item->setBackground(QBrush(bg));

            table->setItem(row, col, item);
        }
    }
}
