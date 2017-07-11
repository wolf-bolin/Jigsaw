#include "succeed_dialog.h"
#include "ui_succeed_dialog.h"

#include <QPixmap>
#include <QPainter>
#include <QBitmap>

Succeed_Dialog::Succeed_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Succeed_Dialog)
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

    QPixmap picture (":/picture/Succeed_picture");
    picture = picture.scaled(QSize(180,110));
    ui->label_picture->setPixmap(picture);
    ui->lineEdit_grade->setReadOnly(true);
    ui->lineEdit_name->setReadOnly(true);
    ui->lineEdit_step->setReadOnly(true);
    ui->lineEdit_time->setReadOnly(true);
}

Succeed_Dialog::~Succeed_Dialog()
{
    delete ui;
}
