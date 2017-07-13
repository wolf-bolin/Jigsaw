#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>
#include <QFontDatabase>
#include <QPoint>
#include <QCursor>
#include <QMouseEvent>

namespace Ui {
class setting;
}

class setting : public QDialog
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = 0);
    ~setting();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_picButton6_clicked();

    void on_picButton1_clicked();

    void on_picButton2_clicked();

    void on_picButton3_clicked();

    void on_picButton4_clicked();

    void on_picButton5_clicked();

    void on_sureButton_clicked();

signals:

    void sendPicPath(QString);

private:
    Ui::setting *ui;

    //逻辑数据
    QFileDialog* fileDialog;

    //UI样式
    QPoint offset;//鼠标位置记录值
    QString ButtonStyle = "QPushButton{background-color:#907B63;"

                            "color: white;   border-radius: 10px;  border: 2px groove gray;"

                            "border-style: outset;}"

                            "QPushButton:hover{background-color:white; color: black;}"

                            "QPushButton:pressed{background-color:rgb(85, 170, 255);"

                            "border-style: inset; }";
};

#endif // SETTING_H
