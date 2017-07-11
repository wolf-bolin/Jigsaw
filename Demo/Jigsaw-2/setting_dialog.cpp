#include "setting_dialog.h"
#include "ui_setting_dialog.h"
#include "mainwindow.h"

#include <QImage>
#include <QPainter>
#include <QBitmap>



Setting_dialog::Setting_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting_dialog)
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

    QImage picture1 (":/picture/picture1");
    QImage newpicture1 = picture1.scaled(161,151);
    QPixmap pix1 = QPixmap::fromImage(newpicture1);
    QIcon icon1 = QIcon(pix1);
    ui->pushButton_picture1->setIcon(icon1);

    QImage picture2 (":/picture/picture2");
    QImage newpicture2 = picture2.scaled(161,151);
    QPixmap pix2 = QPixmap::fromImage(newpicture2);
    QIcon icon2= QIcon(pix2);
    ui->pushButton_picture2->setIcon(icon2);
    ui->pushButton_picture2->setIconSize(QSize(100,100));

}

Setting_dialog::~Setting_dialog()
{
    delete ui;
}

void Setting_dialog::on_pushButton_picSelf_2_clicked()
{
    Setting_dialog::close();
}

void Setting_dialog::on_pushButton_picSelf_clicked()
{

    fileDlg.show();
}
