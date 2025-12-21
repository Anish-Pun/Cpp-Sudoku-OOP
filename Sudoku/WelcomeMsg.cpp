#include "WelcomeMsg.h"
#include "./ui_WelcomeMsg.h"
#include "game.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDialogButtonBox>

WelcomeMsg::WelcomeMsg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WelcomeMsg)
{
    ui->setupUi(this);
    setWindowTitle("Sudoku - Welcome");
    setModal(true);
}

WelcomeMsg::~WelcomeMsg()
{
    delete ui;
}

void WelcomeMsg::on_btnNewGame_clicked()
{
    QString playerName = getPlayerNameInput();
    if (playerName.isEmpty()) {
        return; // User cancelled
    }
    
    m_selectedPlayerName = playerName;
    m_isNewGame = true;
    accept();
}

void WelcomeMsg::on_btnLoadGame_clicked()
{
    QString playerName = selectPlayerFromList();
    if (playerName.isEmpty()) {
        return; // User cancelled or no players available
    }
    
    m_selectedPlayerName = playerName;
    m_isNewGame = false;
    accept();
}

void WelcomeMsg::on_btnExit_clicked()
{
    reject();
}

QString WelcomeMsg::getPlayerNameInput()
{
    bool ok;
    QString playerName = QInputDialog::getText(
        this,
        "New Player",
        "Enter your name:\n\n"
        "Notice: Only player statistics (games played, games won, best time, etc.) will be saved.\n"
        "Your current game board will NOT be saved.\n\n"
        "If you choose the same name, the previous statistics will be overwritten.",
        QLineEdit::Normal,
        "",
        &ok
    );
    
    if (!ok || playerName.trimmed().isEmpty()) {
        return QString();
    }
    
    // Check if player already exists and warn user
    if (sudoku::Game::playerExists(playerName.toStdString())) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Player Already Exists",
            "A player with this name already exists.\n\n"
            "Only statistics (games played, games won, best time, etc.) will be overwritten.\n"
            "The current game board will NOT be saved.\n\n"
            "Do you want to continue?",
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No
        );
        
        if (reply != QMessageBox::Yes) {
            return QString(); // User cancelled
        }
    }
    
    return playerName.trimmed();
}

QString WelcomeMsg::selectPlayerFromList()
{
    std::vector<std::string> players = sudoku::Game::listAvailablePlayers();
    
    if (players.empty()) {
        QMessageBox::information(
            this,
            "Load Game",
            "No saved players found. Please create a new game first.\n\n"
            "Note: Only player statistics are saved, not game boards."
        );
        return QString();
    }
    
    // Create a dialog with a list of players
    QDialog dialog(this);
    dialog.setWindowTitle("Load Game - Select Player");
    dialog.setModal(true);
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    
    QLabel *label = new QLabel("Select a player:", &dialog);
    layout->addWidget(label);
    
    QLabel *infoLabel = new QLabel("Note: Only player statistics will be loaded.\nThe game board will start fresh.", &dialog);
    infoLabel->setStyleSheet("color: gray; font-style: italic;");
    infoLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(infoLabel);
    
    QListWidget *listWidget = new QListWidget(&dialog);
    for (const auto& player : players) {
        listWidget->addItem(QString::fromStdString(player));
    }
    listWidget->setCurrentRow(0);
    layout->addWidget(listWidget);
    
    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        &dialog
    );
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    layout->addWidget(buttonBox);
    
    if (dialog.exec() == QDialog::Accepted) {
        QListWidgetItem *item = listWidget->currentItem();
        if (item) {
            return item->text();
        }
    }
    
    return QString();
}

