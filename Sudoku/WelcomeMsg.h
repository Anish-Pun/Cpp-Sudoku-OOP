#ifndef WELCOMEMSG_H
#define WELCOMEMSG_H

#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class WelcomeMsg; }
QT_END_NAMESPACE

class WelcomeMsg : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeMsg(QWidget *parent = nullptr);
    ~WelcomeMsg();

    QString selectedPlayerName() const { return m_selectedPlayerName; }
    bool isNewGame() const { return m_isNewGame; }

private slots:
    void on_btnNewGame_clicked();
    void on_btnLoadGame_clicked();
    void on_btnExit_clicked();

private:
    Ui::WelcomeMsg *ui;
    QString m_selectedPlayerName;
    bool m_isNewGame = false;

    QString getPlayerNameInput();
    QString selectPlayerFromList();
};

#endif // WELCOMEMSG_H

