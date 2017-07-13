#include "setting.h"
#include "ui_setting.h"

setting::setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);

    QPixmap pix;
    pix.load(":/picture/settingBackground.png");
    resize(pix.size());
    setMask(pix.mask());

    QImage picture1 (":/picture/00.jpg");
    QImage newpicture1 = picture1.scaled(115,115);
    QPixmap pix1 = QPixmap::fromImage(newpicture1);
    QIcon icon1 = QIcon(pix1);
    ui->picButton1->setIcon(icon1);
    ui->picButton1->setIconSize(QSize(115,115));

    QImage picture2 (":/picture/01.jpg");
    QImage newpicture2 = picture2.scaled(115,115);
    QPixmap pix2 = QPixmap::fromImage(newpicture2);
    QIcon icon2 = QIcon(pix2);
    ui->picButton2->setIcon(icon2);
    ui->picButton2->setIconSize(QSize(115,115));

    QImage picture3 (":/picture/02.jpg");
    QImage newpicture3 = picture3.scaled(115,115);
    QPixmap pix3 = QPixmap::fromImage(newpicture3);
    QIcon icon3 = QIcon(pix3);
    ui->picButton3->setIcon(icon3);
    ui->picButton3->setIconSize(QSize(115,115));

    QImage picture4 (":/picture/03.jpg");
    QImage newpicture4 = picture4.scaled(115,115);
    QPixmap pix4 = QPixmap::fromImage(newpicture4);
    QIcon icon4 = QIcon(pix4);
    ui->picButton4->setIcon(icon4);
    ui->picButton4->setIconSize(QSize(115,115));

    QImage picture5 (":/picture/04.jpg");
    QImage newpicture5 = picture5.scaled(115,115);
    QPixmap pix5 = QPixmap::fromImage(newpicture5);
    QIcon icon5 = QIcon(pix5);
    ui->picButton5->setIcon(icon5);
    ui->picButton5->setIconSize(QSize(115,115));

    QImage picture6 (":/picture/05.jpg");
    QImage newpicture6 = picture6.scaled(115,115);
    QPixmap pix6 = QPixmap::fromImage(newpicture6);
    QIcon icon6 = QIcon(pix6);
    ui->picButton6->setIcon(icon6);
    ui->picButton6->setIconSize(QSize(115,115));

    int loadedFontID = QFontDatabase::addApplicationFont(":/font/miaowu.ttf");
    QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
    QString font = loadedFontFamilies.at(0);
    ui->sureButton->setFont(QFont(font,15));
    ui->sureButton->setStyleSheet(ButtonStyle);

}

setting::~setting()
{
    delete ui;
}

void setting::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/picture/settingBackground.png"));
}

void setting::mousePressEvent(QMouseEvent *event){
    if(event->button()== Qt::LeftButton)
    {
        offset=event->globalPos()-pos();
    }
}

void setting::mouseMoveEvent(QMouseEvent *event){
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

void setting::mouseReleaseEvent(QMouseEvent *event){
    if(!event->buttons())
    {
        QCursor cursor;
        cursor.setShape(Qt::ArrowCursor);
        setCursor(cursor);
    }
}

void setting::on_picButton1_clicked()
{
    emit sendPicPath(":/picture/00.jpg");
}

void setting::on_picButton2_clicked()
{
    emit sendPicPath(":/picture/01.jpg");
}

void setting::on_picButton3_clicked()
{
    emit sendPicPath(":/picture/02.jpg");
}

void setting::on_picButton4_clicked()
{
    emit sendPicPath(":/picture/03.jpg");
}

void setting::on_picButton5_clicked()
{
    emit sendPicPath(":/picture/04.jpg");
}

void setting::on_picButton6_clicked()
{
    QString str = QFileDialog::getOpenFileName(this,"导入图片","./picture","Image Files(*.jpg)");
    emit sendPicPath(str);
}

void setting::on_sureButton_clicked()
{
    setting::close();
}
