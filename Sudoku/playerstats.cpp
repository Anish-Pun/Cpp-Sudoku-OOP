#include "playerstats.h"
#include "ui_playerstats.h"

PlayerStats::PlayerStats(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlayerStats)
{
    ui->setupUi(this);
}

PlayerStats::~PlayerStats()
{
    delete ui;
}

void PlayerStats::setStats(int gamesPlayed,
                           int gamesWon,
                           int bestTimeSeconds,
                           double averageTimeSeconds)
{
    ui->valueGamesPlayed->setText(QString::number(gamesPlayed));
    ui->valueGamesWon->setText(QString::number(gamesWon));

    auto formatTime = [](int seconds) -> QString {
        if (seconds < 0) {
            return "-";
        }
        int minutes = seconds / 60;
        int secs    = seconds % 60;
        return QString("%1:%2")
            .arg(minutes, 2, 10, QLatin1Char('0'))
            .arg(secs,    2, 10, QLatin1Char('0'));
    };

    ui->valueBestTime->setText(formatTime(bestTimeSeconds));

    if (gamesWon == 0) {
        ui->valueAverageTime->setText("-");
    } else {
        int avgSecs = static_cast<int>(averageTimeSeconds + 0.5); // round to nearest
        ui->valueAverageTime->setText(formatTime(avgSecs));
    }
}
