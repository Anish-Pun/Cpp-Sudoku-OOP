#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace sudoku {
class Game;
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(sudoku::Game& game, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    sudoku::Game& m_game;

    void setupBoardAppearance();  // alleen looks
    void loadFromGame();          // Board -> UI

private slots:
    void onCellChanged(int row, int column); // UI -> Game
    void on_btnCheck_clicked(); // Checking if btns of the ui works
};

#endif // MAINWINDOW_H
