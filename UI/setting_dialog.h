#ifndef SETTING_DIALOG_H
#define SETTING_DIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class Setting_Dialog;
}

class Setting_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Setting_Dialog(QWidget *parent = 0);
    ~Setting_Dialog();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_3_clicked();

private:
    Ui::Setting_Dialog *ui;
    QFileDialog fileDlg;


    QString ButtonStyle_1 = "QPushButton{background-color:#907B63;"

                    "color: white;   border-radius: 10px;  border: 2px groove gray;"

                    "border-style: outset;}"

                    "QPushButton:hover{background-color:white; color: black;}"

                    "QPushButton:pressed{background-color:rgb(85, 170, 255);"

                    "border-style: inset; }";
};

#endif // SETTING_DIALOG_H
