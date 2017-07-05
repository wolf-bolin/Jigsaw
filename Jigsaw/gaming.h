#ifndef GAMING_H
#define GAMING_H

#include <QWidget>

namespace Ui {
class Gaming;
}

class Gaming : public QWidget
{
    Q_OBJECT

public:
    explicit Gaming(QWidget *parent = 0);
    ~Gaming();

private:
    Ui::Gaming *ui;
};

#endif // GAMING_H
