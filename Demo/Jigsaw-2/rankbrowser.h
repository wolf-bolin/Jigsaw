#ifndef RANKBROWSER_H
#define RANKBROWSER_H

#include <QWidget>

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

private slots:
    void on_pushButton_clicked();

private:
    Ui::rankBrowser *ui;

    std::vector<gameinfo> gameRecord;//历史游戏记录
};

#endif // RANKBROWSER_H
