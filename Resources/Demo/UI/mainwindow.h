#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
#include <QLCDNumber>
#include <QTimer>
#include <QTime>

#include "setting_dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SwapBtn(int m,int n) ;
    void MySwap(int k);


private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    void on_exit_Button_clicked();          //“退出”按钮对应的槽

    void on_Set_Button_clicked();           //“游戏设置”按钮对应的槽

    void on_pushButton_0_clicked();         //ui_main中9个按钮的点击事件槽
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();

    void on_New_game_Button_clicked();
    void updateTime();

private:
    Ui::MainWindow *ui_main;

    int step = 0;

    bool isStart = false;
    QTimer *timer;      //定时器 每秒更新时间
    QTime *TimeRecord;  //记录时间
    int game_time = 0;     //记录游戏时间

    QPushButton *Btn_array[9];
    int data_btn[9];

    QPoint move_point;
    bool mouse_press;

    Setting_Dialog set_dlg;             //自定义的一个设置对话框

    //第一种按钮的样式字符串
    QString ButtonStyle_1 = "QPushButton{background-color:#907B63;"

                    "color: white;   border-radius: 10px;  border: 2px groove gray;"

                    "border-style: outset;}"

                    "QPushButton:hover{background-color:white; color: black;}"

                    "QPushButton:pressed{background-color:rgb(85, 170, 255);"

                    "border-style: inset; }";

};

#endif // MAINWINDOW_H
