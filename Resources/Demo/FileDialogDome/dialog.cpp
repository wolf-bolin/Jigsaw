#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QString>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{

    QString str = QFileDialog::getOpenFileName(this,"导入图片","./picture","Image Files(*.jpg)");
    ui->label->setText(str);
}
