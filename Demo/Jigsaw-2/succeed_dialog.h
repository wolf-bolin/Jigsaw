#ifndef SUCCEED_DIALOG_H
#define SUCCEED_DIALOG_H

#include <QDialog>


namespace Ui {
class Succeed_Dialog;
}

class Succeed_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Succeed_Dialog(QWidget *parent = 0);
    ~Succeed_Dialog();

private:
    Ui::Succeed_Dialog *ui;
};

#endif // SUCCEED_DIALOG_H
