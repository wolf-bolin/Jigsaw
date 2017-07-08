#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QBitmap>
#include <QPainter>
#include <QIcon>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
            QMainWindow(parent),
    ui_main(new Ui::MainWindow)
{
    ui_main->setupUi(this);

    setMouseTracking(true);             //窗口移动功能的前提声明

    setWindowFlags(Qt::FramelessWindowHint);
    //设置关于窗体为圆角
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),20,20);
    setMask(bmp);

    //将ui_main
    Btn_array[0]=ui_main->pushButton_0;
    Btn_array[1]=ui_main->pushButton_1;
    Btn_array[2]=ui_main->pushButton_2;
    Btn_array[3]=ui_main->pushButton_3;
    Btn_array[4]=ui_main->pushButton_4;
    Btn_array[5]=ui_main->pushButton_5;
    Btn_array[6]=ui_main->pushButton_6;
    Btn_array[7]=ui_main->pushButton_7;
    Btn_array[8]=ui_main->pushButton_8;


    ui_main->Answer_Button->setStyleSheet(ButtonStyle_1);
    ui_main->exit_Button->setStyleSheet(ButtonStyle_1);
    ui_main->New_game_Button->setStyleSheet(ButtonStyle_1);
    ui_main->Record_Button->setStyleSheet(ButtonStyle_1);
    ui_main->Rev_Button->setStyleSheet(ButtonStyle_1);
    ui_main->Save_Button->setStyleSheet(ButtonStyle_1);
    ui_main->Set_Button->setStyleSheet(ButtonStyle_1);
    ui_main->Sort_Button->setStyleSheet(ButtonStyle_1);


    for(int i=0;i<9;i++)
    {
        data_btn[i]=i;
    }

    timer = new QTimer;  //初始化定时器
    TimeRecord = new QTime(0, 0, 0); //初始化时间
    ui_main->lcdNumber_Time->display(TimeRecord->toString("hh:mm:ss"));
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));

}

MainWindow::~MainWindow()
{
    delete ui_main;
}

void MainWindow::on_exit_Button_clicked()                //点击退出按钮的效果函数
{
    QApplication::quit();
}

void MainWindow::mousePressEvent(QMouseEvent *event)    //使得窗口能够被拖动的效果函数
{
 if(event->button() == Qt::LeftButton)
 {
      mouse_press = true;
      //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）

      move_point = event->pos();
 }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    if(mouse_press)                                     //若鼠标左键被按下
    {
       QPoint move_pos = event->globalPos();            //鼠标相对于屏幕的位置
       this->move(move_pos - move_point);               //移动主窗体位置
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{                                                        
    mouse_press = false;                                //设置鼠标为未被按下
}


void MainWindow::paintEvent(QPaintEvent *)              //画出一个圆边矩形
{
    QPainter painter(this);
    QRectF rectangle(170, 60, 550, 400);
    painter.setBrush(QBrush(Qt::color0,Qt::SolidPattern));
    painter.drawRoundedRect(rectangle, 15, 15);
}

void MainWindow::on_Set_Button_clicked()        //设置按钮的点击事件
{
    set_dlg.setModal(true);
    set_dlg.show();
}

void MainWindow::MySwap(int k)               //实现按钮交换的函数，其中k代表点击的按钮序号
{
    if(data_btn[k]==0){
        return;
    }

    if(k!=2&&k!=5&&k!=8)
    {
        if(data_btn[k+1]==0)            //向右看
        {
            SwapBtn(k,k+1);
        }

    }
    if(k!=0&&k!=3&&k!=6)
    {
        if(data_btn[k-1]==0)            //向左看
        {
            SwapBtn(k,k-1);
        }
    }
    if(k!=0&&k!=1&&k!=2)
    {
        if(data_btn[k-3]==0)            //向上看
        {
            SwapBtn(k,k-3);
        }
    }
    if(k!=6&&k!=7&&k!=8)
    {
        if(data_btn[k+3]==0)            //向下看
        {
            SwapBtn(k,k+3);
        }
    }
}

void MainWindow::SwapBtn(int m,int n)          //第m个按钮和第n个按钮进行交换
{
    QString str = Btn_array[m]->text();
    Btn_array[m]->setText(Btn_array[n]->text());
    Btn_array[n]->setText(str);
    int tem = data_btn[m];
    data_btn[m] = data_btn[n];
    data_btn[n] = tem;
    step++;
    ui_main->lcdNumber_Step->display(step);     //显示走的步数
}

void MainWindow::on_pushButton_0_clicked()
{
    MySwap(0);
}

void MainWindow::on_pushButton_1_clicked()
{
    MySwap(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    MySwap(2);
}

void MainWindow::on_pushButton_3_clicked()
{
    MySwap(3);
}

void MainWindow::on_pushButton_4_clicked()
{
    MySwap(4);
}

void MainWindow::on_pushButton_5_clicked()
{
    MySwap(5);
}

void MainWindow::on_pushButton_6_clicked()
{
    MySwap(6);
}

void MainWindow::on_pushButton_7_clicked()
{
    MySwap(7);
}

void MainWindow::on_pushButton_8_clicked()
{
    MySwap(8);
}

void MainWindow::on_New_game_Button_clicked()
{
    if(!isStart) //尚未开始 开始计时
        {

            timer->start(1000);

        }
        isStart = !isStart;
}
void MainWindow::updateTime()
{
    *TimeRecord = TimeRecord->addSecs(1);
    game_time++;
    ui_main->lcdNumber_Time->display(TimeRecord->toString("hh:mm:ss"));
}
