#ifndef SUCCESS_H
#define SUCCESS_H

#include <QDialog>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

#include "gamelogic.h"

namespace Ui {
class success;
}

class success : public QDialog
{
    Q_OBJECT

public:
    explicit success(QWidget *parent = 0);
    ~success();

private slots:
    void on_sureButton_clicked();
    
    void setParameter(int gameTime,int gameStep,int answerStep);

    void newRecordFinishedSlot(QNetworkReply *reply);

private:
    Ui::success *ui;
    gameinfo* personal;
    
    QNetworkAccessManager *manager;
    
    std::vector<gameinfo> gameRecord;//历史游戏记录
};

#endif // SUCCESS_H
