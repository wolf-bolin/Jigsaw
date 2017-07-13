#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*successDialog.setModal(true);
    successDialog.show();*/

    setMouseTracking(true);//窗口移动功能的前提声明

    QPixmap pix;
    pix.load(":/picture/mainBackground.png");
    resize(pix.size());
    setMask(pix.mask());

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
    ui->saveStatusButton->setStyleSheet(ButtonStyle);
    ui->autoSolveButton->setStyleSheet(ButtonStyle);
    ui->rankBrowse->setStyleSheet(ButtonStyle);
    ui->gameSettingButton->setStyleSheet(ButtonStyle);
    ui->newGameButton->setStyleSheet(ButtonStyle_newGame);
    ui->undoStepButton->setStyleSheet(ButtonStyle);
    ui->exitGameButton->setStyleSheet(ButtonStyle);

    int loadedFontID = QFontDatabase::addApplicationFont(":/font/miaowu.ttf");
    QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
    QString mwfont = loadedFontFamilies.at(0);
    ui->saveStatusButton->setFont(QFont(mwfont,20));
    ui->autoSolveButton->setFont(QFont(mwfont,20));
    ui->rankBrowse->setFont(QFont(mwfont,20));
    ui->gameSettingButton->setFont(QFont(mwfont,20));
    ui->newGameButton->setFont(QFont(mwfont,20));
    ui->undoStepButton->setFont(QFont(mwfont,20));
    ui->exitGameButton->setFont(QFont(mwfont,20));
    ui->gameScoreLCD->setFont(QFont(mwfont,26));
    ui->gameStepLCD->setFont(QFont(mwfont,26));
    ui->gameTimeLCD->setFont(QFont(mwfont,26));

    //数据初始化
    readStatus(numData,gameStep,gameTime);//读取本地文件或者初始化
    readMoveLog(logs);
    std::string picPath;
    readSetting(picPath);
    picFilePath = QString::fromStdString(picPath);
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

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/picture/mainBackground.png"));
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button()== Qt::LeftButton)
    {
        offset=event->globalPos()-pos();
    }else if(event->button()== Qt::RightButton){
        MainWindow::showMinimized();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons()&Qt::LeftButton)
    {
        QPoint temp;
        QCursor cursor;
        cursor.setShape(Qt::OpenHandCursor);
        setCursor(cursor);

        temp=event->globalPos()-offset;
        move(temp);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(!event->buttons())
    {
        QCursor cursor;
        cursor.setShape(Qt::ArrowCursor);
        setCursor(cursor);
    }
}

// ////////////////////////////////////////////////////////////////////////////
//槽函数
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
    logs.clear();
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
    updateLCD();
}

void MainWindow::on_exitGameButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_saveStatusButton_clicked()
{
    saveMoveLog(logs);
    saveStatus(numData,gameStep,gameTime);
    QMessageBox::information(this,tr("提示"),tr("数据保存成功"));
}

void MainWindow::on_autoSolveButton_clicked()
{
    if(playing==0){
        return;
    }
    logs.clear();
    playing=0;
    astar(numData,answer);
    CGTimer = new QTimer;
    connect(CGTimer,SIGNAL(timeout()),this,SLOT(AStarSolveStep()));
    CGTimer->start(500);
    gameTimer->stop();
    gameTime=0;
    gameStep=0;
}

void MainWindow::on_rankBrowse_clicked()
{
    rankBrowserWidget.loadData();
    rankBrowserWidget.show();
}

void MainWindow::on_gameSettingButton_clicked()
{
    connect(&settingDialog,SIGNAL(sendPicPath(QString)),this,SLOT(setNewPicture(QString)));
    settingDialog.setModal(true);
    settingDialog.show();
}

void MainWindow::addTime(){
    //更新UI中时间的显示
    gameTime++;
    updateLCD();
}

void MainWindow::AStarSolveStep(){
    //解题过程中的每一步操作
    SwapBtn(answer.back().m,answer.back().n);
    answer.pop_back();
    if(answer.size()==0){
        CGTimer->stop();
    }
}

void MainWindow::setNewPicture(QString filePath){
    //图像的重新载入
    QImage picture;
    if(!(picture.load(filePath)) ) //加载图像
    {
        QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
        picFilePath = ":/picture/00.jpg";
        saveSetting(picFilePath.toStdString());
        return;
    }
    picFilePath = filePath;
    saveSetting(picFilePath.toStdString());
    QImage pictureScaled = picture.scaled(405,405);//设定大小
    QPixmap pictureCut;
    QIcon buttonIcon;
    int picPos;
    for(int i=0;i<8;i++){
        pictureCut= QPixmap::fromImage(pictureScaled).copy((i%3)*135,(i/3)*135,135,135);
        buttonIcon= QIcon(pictureCut);
        picPos=findNumPos(i+1);
        numButton[picPos]->setIcon(buttonIcon);
        numButton[picPos]->setIconSize(QSize(135,135));
    }
    buttonIcon= QIcon();
    numButton[findNumPos(0)]->setIcon(buttonIcon);
    numButton[findNumPos(0)]->setIconSize(QSize(135,135));

    pictureScaled = picture.scaled(160,160);
    pictureCut = QPixmap::fromImage(pictureScaled);
    ui->picturePreview->setPixmap(pictureCut);
}

// ////////////////////////////
//逻辑函数
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
    updateLCD();
    if(checkAnswer(numData)){
        gameTimer->stop();
        playing=0;

        successDialog.setModal(true);
        successDialog.show();
        connect(this,SIGNAL(gameComplete(int,int,int)),&successDialog,SLOT(setParameter(int,int,int)));
        emit gameComplete(gameTime,gameStep,answer.size());
        return;
    }
}

int MainWindow::findNumPos(int n){
    //用于查询每个数码的位置
    for(unsigned int i=0;i!=numData.size();i++){
        if(numData[i]==n){
            return i;
        }
    }
    return -1;
}

void MainWindow::doNext(int m,int n){
    SwapBtn(m,n);
    //计步
    gameStep++;
    //后台数据处理
    logs.push_back(moveinfo(gameStep,m,n));
}

void MainWindow::doRvoke(int m,int n){
    SwapBtn(m,n);
    //计步
    gameStep++;
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

// /////////////////////////////////////////////////////
//UI函数
void MainWindow::updateLCD(){
    //更新UI中LCD
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
    ui->gameTimeLCD->setText(timeRecord->toString("mm:ss"));
    ui->gameStepLCD->setText(QString::number(gameStep,10));
    int scoreNow=gameTime*(gameStep-answer.size()+1);
    ui->gameScoreLCD->setText(QString::number(scoreNow,10));
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
