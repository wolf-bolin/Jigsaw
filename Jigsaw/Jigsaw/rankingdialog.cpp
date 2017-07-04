#include "rankingdialog.h"
#include "ui_rankingdialog.h"

RankingDialog::RankingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RankingDialog)
{
    ui->setupUi(this);
}

RankingDialog::~RankingDialog()
{
    delete ui;
}
