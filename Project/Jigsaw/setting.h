#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>

namespace Ui {
class setting;
}

class setting : public QDialog
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = 0);
    ~setting();

private slots:
    void on_picButton6_clicked();

    void on_picButton1_clicked();

    void on_picButton2_clicked();

    void on_picButton3_clicked();

    void on_picButton4_clicked();

    void on_picButton5_clicked();

signals:

    void sendPicPath(QString);

private:
    Ui::setting *ui;

    QFileDialog* fileDialog;
};

#endif // SETTING_H
