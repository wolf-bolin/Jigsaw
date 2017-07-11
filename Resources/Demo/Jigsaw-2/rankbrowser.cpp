#include "rankbrowser.h"
#include "ui_rankbrowser.h"

#include <QPainter>
#include <QBitmap>

rankBrowser::rankBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rankBrowser)
{

    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),10,10);
    setMask(bmp);

    ui->gameRecordTable->setColumnCount(4);
    ui->gameRecordTable->horizontalHeader()->setDefaultSectionSize(80);
    QStringList header;
    header<<tr("用户名")<<tr("时间")<<tr("步数")<<tr("分数");
    ui->gameRecordTable->setHorizontalHeaderLabels(header);
    QFont font = ui->gameRecordTable->horizontalHeader()->font();
    font.setBold(true);
    ui->gameRecordTable->horizontalHeader()->setFont(font);
    ui->gameRecordTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
}
rankBrowser::~rankBrowser()
{
    delete ui;
}

void rankBrowser::loadData(){
    readGameLog(gameRecord);
    while(ui->gameRecordTable->rowCount()>0){
        ui->gameRecordTable->removeRow(0);
    }
    for(unsigned int i=0;i!=gameRecord.size();i++){
        std::cout<<gameRecord[i].userName<<"  "
                <<gameRecord[i].gameTime<<"  "
               <<gameRecord[i].gameStep<<"  "
              <<gameRecord[i].score<<std::endl;
        int row_count = ui->gameRecordTable->rowCount(); //获取表单行数
        ui->gameRecordTable->insertRow(row_count);      //插入新行
        QTableWidgetItem *item1,*item2,*item3,*item4;   //新建一个item
        item1 = new QTableWidgetItem();
        item2 = new QTableWidgetItem();
        item3 = new QTableWidgetItem();
        item4 = new QTableWidgetItem();
        item1->setText(QString::fromStdString(gameRecord[i].userName));            //给这个item设置文本
        ui->gameRecordTable->setItem(row_count,0,item1); //将这个item加入到表单的第row_count行，第0列当中去
        item2->setText(QString::number(gameRecord[i].gameTime,10));
        ui->gameRecordTable->setItem(row_count,1,item2);
        item3->setText(QString::number(gameRecord[i].gameStep,10));
        ui->gameRecordTable->setItem(row_count,2,item3);
        item4->setText(QString::number(gameRecord[i].score,10));
        ui->gameRecordTable->setItem(row_count,3,item4);
    }
}

void rankBrowser::on_pushButton_clicked()
{
    rankBrowser::close();
}
