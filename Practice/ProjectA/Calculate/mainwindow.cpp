#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_0_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "0");
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "1");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "2");
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "3");
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "4");
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "5");
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "6");
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "7");
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "8");
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "9");
}


void MainWindow::on_pushButton_AC_clicked()
{
    ui->lineEdit->setText("");
}

void MainWindow::on_pushButton_Drop_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text() + ".");
}

void MainWindow::on_pushButton_Add_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "+");
}

void MainWindow::on_pushButton_Substract_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "-");
}

void MainWindow::on_pushButton_Multi_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text() + "*");
}

void MainWindow::on_pushButton_Div_clicked()
{
     ui->lineEdit->setText(ui->lineEdit->text() + "÷");
}

void MainWindow::on_pushButton_Left_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "(");
}

void MainWindow::on_pushButton_Right_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + ")");
}

void MainWindow::on_pushButton_Mod_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "%");
}

void MainWindow::on_pushButton_Power_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "^");
}

void MainWindow::on_pushButton_Del_clicked()
{
    QString temp_1 =  ui->lineEdit->text();
    string temp_2 = temp_1.toStdString();
    if(temp_2.size()>0){
        temp_2 = temp_2.substr(0,temp_2.size()-1);
    }
    temp_1 = QString::fromStdString(temp_2);
    ui->lineEdit->setText(temp_1);
}

void MainWindow::on_pushButton_Equal_clicked()
{
    QString temp = ui->lineEdit->text();
    temp.replace("÷","/");
    string str = temp.toStdString();
    str = calc(str);
    temp = QString::fromStdString(str);
    ui->lineEdit->setText(temp);
    ui->lineEdit->text().clear();
}





