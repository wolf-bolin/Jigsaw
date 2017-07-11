#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QUrl>
#include <QBitArray>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(finishedSlot(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QUrl url("http://jigsaw.api.admirable.one/getRank?my_highest_score=10100");
    //QByteArray array("");
    QNetworkRequest request(url);
    //QNetworkAccessManager = new QNetworkAccessManager(this);
    //request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    //request.setRawHeader("Authorization","Bearer 49152bfddae0c5b5d492d3d9871f8c11");//服务器要求的数据头部
    manager->get(request);
    qDebug()<<"send";
}
void MainWindow::finishedSlot(QNetworkReply *reply){
    qDebug()<<"finishedSlot";
    qDebug()<<reply->error();
    if (reply->error() == QNetworkReply::NoError){
        QByteArray bytes = reply->readAll();  // bytes
        //QString string(bytes); // string
        QString string = QString::fromUtf8(bytes);
        ui->textBrowser->setText(string);
    }
}
