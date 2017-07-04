/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton_Right;
    QPushButton *pushButton_Left;
    QPushButton *pushButton_Mod;
    QPushButton *pushButton_Power;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_Div;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_Substract;
    QPushButton *pushButton_0;
    QPushButton *pushButton_AC;
    QPushButton *pushButton_Equal;
    QPushButton *pushButton_Add;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;
    QPushButton *pushButton_8;
    QPushButton *pushButton_Multi;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(408, 497);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 10, 391, 81));
        lineEdit->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Avenir Next"));
        font.setPointSize(40);
        lineEdit->setFont(font);
        lineEdit->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit->setMaxLength(327);
        lineEdit->setReadOnly(true);
        pushButton_Right = new QPushButton(centralWidget);
        pushButton_Right->setObjectName(QStringLiteral("pushButton_Right"));
        pushButton_Right->setGeometry(QRect(110, 100, 93, 71));
        QFont font1;
        font1.setFamily(QStringLiteral("Avenir Next"));
        font1.setPointSize(28);
        pushButton_Right->setFont(font1);
        pushButton_Left = new QPushButton(centralWidget);
        pushButton_Left->setObjectName(QStringLiteral("pushButton_Left"));
        pushButton_Left->setGeometry(QRect(10, 100, 93, 71));
        pushButton_Left->setFont(font1);
        pushButton_Mod = new QPushButton(centralWidget);
        pushButton_Mod->setObjectName(QStringLiteral("pushButton_Mod"));
        pushButton_Mod->setGeometry(QRect(210, 100, 93, 71));
        pushButton_Mod->setFont(font1);
        pushButton_Power = new QPushButton(centralWidget);
        pushButton_Power->setObjectName(QStringLiteral("pushButton_Power"));
        pushButton_Power->setGeometry(QRect(310, 100, 93, 71));
        pushButton_Power->setFont(font1);
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(10, 260, 93, 71));
        pushButton_4->setFont(font1);
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(110, 260, 93, 71));
        pushButton_5->setFont(font1);
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(210, 260, 93, 71));
        pushButton_6->setFont(font1);
        pushButton_Div = new QPushButton(centralWidget);
        pushButton_Div->setObjectName(QStringLiteral("pushButton_Div"));
        pushButton_Div->setGeometry(QRect(310, 260, 93, 71));
        pushButton_Div->setFont(font1);
        pushButton_1 = new QPushButton(centralWidget);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(10, 340, 93, 71));
        pushButton_1->setFont(font1);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(110, 340, 93, 71));
        pushButton_2->setFont(font1);
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(210, 340, 93, 71));
        pushButton_3->setFont(font1);
        pushButton_Substract = new QPushButton(centralWidget);
        pushButton_Substract->setObjectName(QStringLiteral("pushButton_Substract"));
        pushButton_Substract->setGeometry(QRect(310, 340, 93, 71));
        pushButton_Substract->setFont(font1);
        pushButton_0 = new QPushButton(centralWidget);
        pushButton_0->setObjectName(QStringLiteral("pushButton_0"));
        pushButton_0->setGeometry(QRect(10, 420, 93, 71));
        pushButton_0->setFont(font1);
        pushButton_AC = new QPushButton(centralWidget);
        pushButton_AC->setObjectName(QStringLiteral("pushButton_AC"));
        pushButton_AC->setGeometry(QRect(110, 420, 93, 71));
        pushButton_AC->setFont(font1);
        pushButton_Equal = new QPushButton(centralWidget);
        pushButton_Equal->setObjectName(QStringLiteral("pushButton_Equal"));
        pushButton_Equal->setGeometry(QRect(210, 420, 93, 71));
        pushButton_Equal->setFont(font1);
        pushButton_Add = new QPushButton(centralWidget);
        pushButton_Add->setObjectName(QStringLiteral("pushButton_Add"));
        pushButton_Add->setGeometry(QRect(310, 420, 93, 71));
        pushButton_Add->setFont(font1);
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(10, 180, 93, 71));
        pushButton_7->setFont(font1);
        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(210, 180, 93, 71));
        pushButton_9->setFont(font1);
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(110, 180, 93, 71));
        pushButton_8->setFont(font1);
        pushButton_Multi = new QPushButton(centralWidget);
        pushButton_Multi->setObjectName(QStringLiteral("pushButton_Multi"));
        pushButton_Multi->setGeometry(QRect(310, 180, 93, 71));
        pushButton_Multi->setFont(font1);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\350\256\241\347\256\227\345\231\250", Q_NULLPTR));
        lineEdit->setText(QString());
        pushButton_Right->setText(QApplication::translate("MainWindow", ")", Q_NULLPTR));
        pushButton_Left->setText(QApplication::translate("MainWindow", "(", Q_NULLPTR));
        pushButton_Mod->setText(QApplication::translate("MainWindow", "%", Q_NULLPTR));
        pushButton_Power->setText(QApplication::translate("MainWindow", "^", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "4", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "5", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "6", Q_NULLPTR));
        pushButton_Div->setText(QApplication::translate("MainWindow", "/", Q_NULLPTR));
        pushButton_1->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "3", Q_NULLPTR));
        pushButton_Substract->setText(QApplication::translate("MainWindow", "-", Q_NULLPTR));
        pushButton_0->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        pushButton_AC->setText(QApplication::translate("MainWindow", "AC", Q_NULLPTR));
        pushButton_Equal->setText(QApplication::translate("MainWindow", "=", Q_NULLPTR));
        pushButton_Add->setText(QApplication::translate("MainWindow", "+", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "7", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("MainWindow", "9", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("MainWindow", "8", Q_NULLPTR));
        pushButton_Multi->setText(QApplication::translate("MainWindow", "*", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
