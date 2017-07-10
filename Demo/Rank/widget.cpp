#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    //设置本地记录表格内容
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(80);
    QStringList header;
    header<<tr("用户名")<<tr("时间")<<tr("步数")<<tr("分数");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

    //设置表头内容
    ui->tableWidget_2->setColumnCount(4);
    ui->tableWidget_2->horizontalHeader()->setDefaultSectionSize(80);
    header<<tr("用户名")<<tr("时间")<<tr("步数")<<tr("分数");
    ui->tableWidget_2->setHorizontalHeaderLabels(header);
    font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget_2->horizontalHeader()->setFont(font);
    ui->tableWidget_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");




}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    Widget::close();
}

void Widget::on_pushButton_2_clicked()
{
    int row_count = ui->tableWidget->rowCount(); //获取表单行数
    ui->tableWidget->insertRow(row_count);      //插入新行
    QTableWidgetItem *item = new QTableWidgetItem();   //新建一个item
    item->setText("李华");            //给这个item设置文本
    ui->tableWidget->setItem(row_count,0,item); //将这个item加入到表单的第row_count行，第0列当中去

    QTableWidgetItem *item2 = new QTableWidgetItem();   //新建一个item
    item2->setText(QString::number( 7,10));            //给这个item2设置数据,QString::number是将10进制的int类型的数转换为Qstring类型
    ui->tableWidget->setItem(row_count,1,item2);

}
