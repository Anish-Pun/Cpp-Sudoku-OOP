#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "game.h"

class PlayerStats;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// OOP: Inheritance
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // OOP: Polymorphism
    explicit MainWindow(sudoku::AbstractGame& game, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    sudoku::AbstractGame& m_game; // OOP: Composition
    QTimer *m_timer;
    int     m_elapsedSeconds;

    PlayerStats* m_statsWindow = nullptr;
    void setupBoardAppearance();  // alleen looks
    void loadFromGame();          // Board -> UI
    void updateStatsWindow();
    void savePlayerData();        // Save player stats to file

private slots:
    void onCellChanged(int row, int column); // UI -> Game
    void on_btnCheck_clicked(); // Checking if btns of the ui works
    void on_btnNewGame_clicked();
    void on_btnSolve_clicked();
    void on_btnStats_clicked();
    void updateTimer();
    void showHelpDialog();
};

#endif // MAINWINDOW_H
