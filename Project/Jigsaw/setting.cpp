#include "setting.h"
#include "ui_setting.h"

setting::setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);

    /*QImage picture1 (":/picture/picture1");
    QImage newpicture1 = picture1.scaled(161,151);//参数需要修改
    QPixmap pix1 = QPixmap::fromImage(newpicture1);
    QIcon icon1 = QIcon(pix1);
    ui->picButton1->setIcon(icon1);
    ui->picButton1->setIconSize(QSize(161,151));//参数需要修改

    QImage picture2 (":/picture/picture2");
    QImage newpicture2 = picture2.scaled(161,151);//参数需要修改
    QPixmap pix2 = QPixmap::fromImage(newpicture2);
    QIcon icon2 = QIcon(pix2);
    ui->picButton2->setIcon(icon2);
    ui->picButton2->setIconSize(QSize(161,151));//参数需要修改

    QImage picture3 (":/picture/picture3");
    QImage newpicture3 = picture3.scaled(161,151);//参数需要修改
    QPixmap pix3 = QPixmap::fromImage(newpicture3);
    QIcon icon3 = QIcon(pix3);
    ui->picButton3->setIcon(icon3);
    ui->picButton3->setIconSize(QSize(161,151));//参数需要修改

    QImage picture4 (":/picture/picture4");
    QImage newpicture4 = picture4.scaled(161,151);//参数需要修改
    QPixmap pix4 = QPixmap::fromImage(newpicture4);
    QIcon icon4 = QIcon(pix4);
    ui->picButton4->setIcon(icon4);
    ui->picButton4->setIconSize(QSize(161,151));//参数需要修改

    QImage picture5 (":/picture/picture5");
    QImage newpicture5 = picture5.scaled(161,151);//参数需要修改
    QPixmap pix5 = QPixmap::fromImage(newpicture5);
    QIcon icon5 = QIcon(pix5);
    ui->picButton5->setIcon(icon5);
    ui->picButton5->setIconSize(QSize(161,151));//参数需要修改*/
}

setting::~setting()
{
    delete ui;
}

void setting::on_picButton1_clicked()
{
    emit sendPicPath(":/picture/yzk.jpg");
}

void setting::on_picButton2_clicked()
{
    emit sendPicPath(":/picture/09.jpg");
}

void setting::on_picButton3_clicked()
{

}

void setting::on_picButton4_clicked()
{

}

void setting::on_picButton5_clicked()
{

}

void setting::on_picButton6_clicked()
{
    setting::close();
    QString str = "Image Files(*.jpg)";
    fileDialog->setNameFilter(str);
    fileDialog->show();
}
