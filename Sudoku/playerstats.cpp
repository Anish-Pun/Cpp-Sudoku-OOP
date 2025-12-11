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
