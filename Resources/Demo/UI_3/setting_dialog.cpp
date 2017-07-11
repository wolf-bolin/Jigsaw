#include "setting_dialog.h"
#include "ui_setting_dialog.h"
#include "mainwindow.h"

Setting_Dialog::Setting_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting_Dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->pushButton->setStyleSheet(ButtonStyle_1);
    ui->pushButton_2->setStyleSheet(ButtonStyle_1);
    ui->pushButton_3->setStyleSheet(ButtonStyle_1);
    ui->pushButton_4->setStyleSheet(ButtonStyle_1);

}

Setting_Dialog::~Setting_Dialog()
{
    delete ui;
}

void Setting_Dialog::on_pushButton_clicked()
{
    Setting_Dialog::close();
}


void Setting_Dialog::on_pushButton_3_clicked()
{
    Setting_Dialog::close();
    fileDlg.show();
}

void Setting_Dialog::on_pushButton_4_clicked()
{
    //filename = ":/picture/picture2" ;
}
