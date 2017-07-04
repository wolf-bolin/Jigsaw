#ifndef RANKINGDIALOG_H
#define RANKINGDIALOG_H

#include <QDialog>

namespace Ui {
class RankingDialog;
}

class RankingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RankingDialog(QWidget *parent = 0);
    ~RankingDialog();

private:
    Ui::RankingDialog *ui;
};

#endif // RANKINGDIALOG_H
