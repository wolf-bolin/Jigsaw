#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);//窗口移动功能的前提声明

    setWindowFlags(Qt::FramelessWindowHint);//隐藏标题栏
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),20,20);
    setMask(bmp);//设置窗体背景

    //将ui中的数码按钮转载在数组中
    numButton.resize(9);
    numButton[0]=ui->picButton0;
    numButton[1]=ui->picButton1;
    numButton[2]=ui->picButton2;
    numButton[3]=ui->picButton3;
    numButton[4]=ui->picButton4;
    numButton[5]=ui->picButton5;
    numButton[6]=ui->picButton6;
    numButton[7]=ui->picButton7;
    numButton[8]=ui->picButton8;

    //最好先完成数据的读入再初始化界面
    ui->saveStatusButton->setStyleSheet(ButtonStyle_1);
    ui->autoSolveButton->setStyleSheet(ButtonStyle_1);
    ui->rankBrowse->setStyleSheet(ButtonStyle_1);
    ui->gameSettingButton->setStyleSheet(ButtonStyle_1);
    ui->newGameButton->setStyleSheet(ButtonStyle_1);
    ui->undoStepButton->setStyleSheet(ButtonStyle_1);
    ui->exitGameButton->setStyleSheet(ButtonStyle_1);

    //数据初始化
    readStatus(numData,gameStep,gameTime);//读取本地文件或者初始化
    readMoveLog(logs);
    readGameLog(gameRecord);

    picFilePath = ":/picture/yzk.jpg";
    //初始化游戏状态与计时器
    gameTimer = new QTimer;  //初始化定时器
    connect(gameTimer,SIGNAL(timeout()),this,SLOT(addTime()));
    if(gameTime!=0){
        gameTimer->start(1000);
        playing=1;
    }else{
        playing=0;
    }
    //图像二次呈现
    setNewPicture(picFilePath);//加载按钮图片
    updateLCD();//更新LCD
}
MainWindow::~MainWindow()
{
    delete ui;
}
//游戏功能相关
void MainWindow::on_rankBrowse_clicked()
{
    rankBrowserWidget.loadData();
    rankBrowserWidget.show();
}
void MainWindow::on_saveStatusButton_clicked()
{
    saveMoveLog(logs);
    saveStatus(numData,gameStep,gameTime);
    QMessageBox::information(this,tr("提示"),tr("数据保存成功"));
}
void MainWindow::on_exitGameButton_clicked()
{
    QApplication::quit();
}

//游戏内容相关
void MainWindow::on_picButton0_clicked()
{
    clickEvent(0);
}

void MainWindow::on_picButton1_clicked()
{
    clickEvent(1);
}

void MainWindow::on_picButton2_clicked()
{
    clickEvent(2);
}

void MainWindow::on_picButton3_clicked()
{
    clickEvent(3);
}

void MainWindow::on_picButton4_clicked()
{
    clickEvent(4);
}

void MainWindow::on_picButton5_clicked()
{
    clickEvent(5);
}

void MainWindow::on_picButton6_clicked()
{
    clickEvent(6);
}

void MainWindow::on_picButton7_clicked()
{
    clickEvent(7);
}

void MainWindow::on_picButton8_clicked()
{
    clickEvent(8);
}

void MainWindow::on_newGameButton_clicked()
{
    newGame(numData,gameStep,gameTime);//随机生成一个合理的游戏
    astar(numData,answer);//计算最优解，为计算分数做准备
    //UI更新
    setNewPicture(picFilePath);//加载按钮图片
    updateLCD();//更新LCD
    gameTimer->start(1000);
    playing=1;
}

void MainWindow::on_undoStepButton_clicked()
{
    if(logs.size()==0){//防止超出范围的撤销操作
        return;
    }
    doRvoke(logs.back().n,logs.back().m);//按照记录向后撤步
    logs.pop_back();
}

void MainWindow::on_autoSolveButton_clicked()
{
    astar(numData,answer);
    CGTimer = new QTimer;
    connect(CGTimer,SIGNAL(timeout()),this,SLOT(AStarSolveStep()));
    CGTimer->start(500);
    gameTimer->stop();
    gameTime=0;
    gameStep=0;
    playing=0;
}

//独立代码块
void MainWindow::clickEvent(int n){
    if(!playing){
        QMessageBox::information(this,tr("提示"),tr("请开始一局新游戏"));
        return;
    }

    if(numData[n]==0){
        return;
    }

    if(n!=2&&n!=5&&n!=8)
    {
        if(numData[n+1]==0)//向右看
        {
            doNext(n,n+1);
        }

    }
    if(n!=0&&n!=3&&n!=6)
    {
        if(numData[n-1]==0)//向左看
        {
            doNext(n,n-1);
        }
    }
    if(n!=0&&n!=1&&n!=2)
    {
        if(numData[n-3]==0)//向上看
        {
            doNext(n,n-3);
        }
    }
    if(n!=6&&n!=7&&n!=8)
    {
        if(numData[n+3]==0)//向下看
        {
            doNext(n,n+3);
        }
    }

    if(checkAnswer(numData)){
        QMessageBox::information(this,tr("提示"),tr("游戏完成"));
        gameTimer->stop();
        playing=0;
        gameRecord.push_back(gameinfo("admin",gameTime,gameStep,gameTime*(gameStep-answer.size()+1)));
        saveGameLog(gameRecord);
        return;
    }
}
void MainWindow::doNext(int m,int n){
    SwapBtn(m,n);
    //计步
    gameStep++;
    ui->gameStepLCD->display(gameStep);
    //后台数据处理
    logs.push_back(moveinfo(gameStep,m,n));
}
void MainWindow::doRvoke(int m,int n){
    SwapBtn(m,n);
    //计步
    gameStep++;
    ui->gameStepLCD->display(gameStep);
}
void MainWindow::SwapBtn(int m,int n){
    //交换图像
    QIcon tem_icon = numButton[m]->icon();
    numButton[m]->setIcon(numButton[n]->icon());
    numButton[n]->setIcon(tem_icon);
    //交换数字
    int temp = numData[m];
    numData[m] = numData[n];
    numData[n] = temp;
}
bool MainWindow::checkAnswer(std::vector<int> &numData){
    for(int i=0;i!=8;i++){
        if(numData[i]!=i+1){
            return false;
        }
    }
    if(numData[8]!=0){
        return false;
    }
    return true;
}

void MainWindow::setNewPicture(QString filePath){//图像的重新载入
    QImage picture;
    if(!(picture.load(filePath)) ) //加载图像
    {
        QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
        return;
    }
    QImage pictureScaled = picture.scaled(300,300);//设定大小
    QPixmap pictureCut;
    QIcon buttonIcon;
    int picPos;
    for(int i=0;i<8;i++){
        pictureCut= QPixmap::fromImage(pictureScaled).copy((i%3)*100,(i/3)*100,100,100);
        buttonIcon= QIcon(pictureCut);
        picPos=findNumPos(i+1);
        numButton[picPos]->setIcon(buttonIcon);
        numButton[picPos]->setIconSize(QSize(100,100));
    }
    buttonIcon= QIcon();
    numButton[findNumPos(0)]->setIcon(buttonIcon);
    numButton[findNumPos(0)]->setIconSize(QSize(100,100));
}
int MainWindow::findNumPos(int n){//用于查询每个数码的位置
    for(unsigned int i=0;i!=numData.size();i++){
        if(numData[i]==n){
            return i;
        }
    }
    return -1;
}
void MainWindow::addTime(){//更新UI中时间的显示
    *timeRecord = timeRecord->addSecs(1);
    gameTime++;
    ui->gameTimeLCD->display(timeRecord->toString("hh:mm:ss"));

}
void MainWindow::updateLCD(){//更新UI中LCD
    int hh,mm,ss;
    hh=mm=ss=0;
    if(gameTime>3600){
        hh=gameTime/3600;
    }
    if(gameTime>60){
        mm=gameTime%3600/60;
    }
    if(gameTime>0){
        ss=gameTime%60;
    }
    timeRecord = new QTime(hh,mm,ss);
    ui->gameTimeLCD->display(timeRecord->toString("hh:mm:ss"));
    //qDebug()<<gameTime<<hh<<" "<<mm<<" "<<ss<<" "<<" "<<timeRecord->toString("hh:mm:ss");
    ui->gameStepLCD->display(gameStep);
}
void MainWindow::AStarSolveStep(){
    SwapBtn(answer.back().m,answer.back().n);
    answer.pop_back();
    if(answer.size()==0){
        CGTimer->stop();
    }
}

void MainWindow::on_gameSettingButton_clicked()
{
    settingdialog.show();
}
