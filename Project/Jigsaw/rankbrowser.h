#ifndef RANKBROWSER_H
#define RANKBROWSER_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QFontDatabase>
#include <QString>
#include <QFont>
#include <QPoint>
#include <QCursor>
#include <QMouseEvent>

#include "gamelogic.h"

namespace Ui {
class rankBrowser;
}

class rankBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit rankBrowser(QWidget *parent = 0);
    void loadData();
    ~rankBrowser();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_sureButton_clicked();
    void getRankFinishedSlot(QNetworkReply *reply);

private:
    Ui::rankBrowser *ui;

    void getGlobalRank(int maxScore);
    void showLocalMessage();

    //逻辑数据
    std::vector<gameinfo> gameRecord;//历史游戏记录
    std::vector<gameinfo> globalRecord;
    QNetworkAccessManager *manager;
    int globalRank;

    //UI样式
    QPoint offset;//鼠标位置记录值
    QString ButtonStyle = "QPushButton{background-color:#907B63;"

                          "color: white;   border-radius: 10px;  border: 2px groove gray;"

                          "border-style: outset;}"

                          "QPushButton:hover{background-color:white; color: black;}"

                          "QPushButton:pressed{background-color:rgb(85, 170, 255);"

                          "border-style: inset; }";
};

#endif // RANKBROWSER_H
