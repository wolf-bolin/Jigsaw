#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_Add_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_AC_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_Substract_clicked();

    void on_pushButton_Multi_clicked();

    void on_pushButton_Div_clicked();

    void on_pushButton_Equal_clicked();

    void on_pushButton_Left_clicked();

    void on_pushButton_Right_clicked();

    void on_pushButton_Mod_clicked();

    void on_pushButton_Power_clicked();

    void on_pushButton_Drop_clicked();

    void on_pushButton_Del_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
