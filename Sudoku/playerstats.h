#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

#include <QDialog>

namespace Ui {
class PlayerStats;
}

class PlayerStats : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerStats(QWidget *parent = nullptr);
    ~PlayerStats();

    void setStats(int gamesPlayed,
                  int gamesWon,
                  int bestTimeSeconds,
                  double averageTimeSeconds);
                  
private slots:
    void on_btnClose_clicked();

private:
    Ui::PlayerStats *ui;
};

#endif // PLAYERSTATS_H
