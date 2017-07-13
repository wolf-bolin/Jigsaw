#ifndef SUCCESS_H
#define SUCCESS_H

#include <QDialog>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QMouseEvent>
#include <QFontDatabase>
#include <QMessageBox>
#include <QPoint>
#include <QCursor>
#include <QMouseEvent>

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
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_sureButton_clicked();
    
    void setParameter(int gameTime,int gameStep,int answerStep);

    void newRecordFinishedSlot(QNetworkReply *reply);

private:
    Ui::success *ui;
    gameinfo* personal;
    
    //逻辑数据
    QNetworkAccessManager *manager;
    std::vector<gameinfo> gameRecord;//历史游戏记录

    //UI样式
    QPoint offset;//鼠标位置记录值
    QString ButtonStyle = "QPushButton{background-color:#907B63;"

                            "color: white;   border-radius: 10px;  border: 2px groove gray;"

                            "border-style: outset;}"

                            "QPushButton:hover{background-color:white; color: black;}"

                            "QPushButton:pressed{background-color:rgb(85, 170, 255);"

                            "border-style: inset; }";
};

#endif // SUCCESS_H
