#include "gaming.h"
#include "ui_gaming.h"

Gaming::Gaming(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gaming)
{
    ui->setupUi(this);
}

Gaming::~Gaming()
{
    delete ui;
}
