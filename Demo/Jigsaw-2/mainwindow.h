#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBitmap>
#include <QPainter>
#include <QString>
#include <QPushButton>
#include <QMessageBox>
#include <QImage>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <vector>
#include <QFileDialog>

#include "gamelogic.h"
#include "rankbrowser.h"
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

private slots:
    void on_picButton0_clicked();

    void on_picButton1_clicked();

    void on_picButton2_clicked();

    void on_picButton3_clicked();

    void on_picButton4_clicked();

    void on_picButton5_clicked();

    void on_picButton6_clicked();

    void on_picButton7_clicked();

    void on_picButton8_clicked();

    void addTime();

    void AStarSolveStep();

    void on_newGameButton_clicked();

    void on_undoStepButton_clicked();

    void on_exitGameButton_clicked();

    void on_saveStatusButton_clicked();

    void on_autoSolveButton_clicked();

    void on_rankBrowse_clicked();

    void on_gameSettingButton_clicked();

private:
    Ui::MainWindow *ui;

    std::vector<QPushButton*> numButton;
    std::vector<int> numData;

    QFileDialog filedialog;

    //UI函数
    void setNewPicture(QString filePath);
    void updateLCD();
    void SwapBtn(int m,int n);

    //逻辑函数
    int findNumPos(int n);
    void clickEvent(int n);
    void doNext(int m,int n);
    void doRvoke(int m,int n);
    bool checkAnswer(std::vector<int> &numData);

    //游戏组件
    bool isStart = false;
    QTimer* gameTimer;//定时器 每秒更新时间
    QTime* timeRecord;//记录时间
    bool playing;
    int gameTime = 0;//记录游戏时间
    int gameStep;//计步
    std::vector<moveinfo> logs;//记录步骤
    std::vector<gameinfo> gameRecord;//历史游戏记录

    //解题组建
    QTimer* CGTimer;
    std::vector<moveinfo> answer;

    //UI样式
    rankBrowser rankBrowserWidget;
    Setting_dialog settingdialog;

    QString picFilePath;
    QString ButtonStyle_1 = "QPushButton{background-color:#907B63;"

                            "color: white;   border-radius: 10px;  border: 2px groove gray;"

                            "border-style: outset;}"

                            "QPushButton:hover{background-color:white; color: black;}"

                            "QPushButton:pressed{background-color:rgb(85, 170, 255);"

                            "border-style: inset; }";

};

#endif // MAINWINDOW_H
