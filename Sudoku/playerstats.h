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

private:
    Ui::PlayerStats *ui;
};

#endif // PLAYERSTATS_H
