#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    manager2 = new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply * )), this, SLOT(getRankFinishedSlot(QNetworkReply * )));
    QObject::connect(manager2, SIGNAL(finished(QNetworkReply * )), this, SLOT(newRecordFinishedSlot(QNetworkReply * )));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_sendButton_clicked() {
    QUrl url("http://jigsaw.api.admirable.one/getRank?my_highest_score=2000");
    QNetworkRequest request(url);
    manager->get(request);
    qDebug() << "GetRank network request sent.";
}

void MainWindow::on_pushButton_clicked() {
    QUrl url("http://jigsaw.api.admirable.one/newRecord?player_name=testNetwork&score=2000&difficulty=3&time=60");
    QNetworkRequest request(url);
    manager2->get(request);
    qDebug() << "New record request sent.";
}

void MainWindow::getRankFinishedSlot(QNetworkReply *reply) {
    qDebug() << "Slot finished.";
    qDebug() << reply->error();
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        // Parse data
        QJsonParseError json_error;
        QJsonDocument parseDocument = QJsonDocument::fromJson(bytes, &json_error);
        if (json_error.error == QJsonParseError::NoError) {
            if (parseDocument.isObject()) {
                QJsonObject obj = parseDocument.object();
                if (obj.contains("my_rank")) {
                    QJsonValue rank_value = obj.take("my_rank");
                    if (rank_value.isDouble()) {
                        qDebug() << "My rank:" << rank_value.toInt() << endl;
                        QString rank = rank_value.toString();
                    }
                }
                if (obj.contains("ranking_list")) {
                    QJsonArray ranking_array = obj.take("ranking_list").toArray();
                    for (int i = 0; i < ranking_array.size(); i++) {
                        qDebug() << ranking_array.at(i).toArray().at(1).toString() << " ";//username
                        qDebug() << ranking_array.at(i).toArray().at(2).toInt() << " ";//score
                        qDebug() << ranking_array.at(i).toArray().at(3).toInt() << " ";//difficulty
                        qDebug() << ranking_array.at(i).toArray().at(4).toInt() << endl;//time-used
                    }
                }
            }
        }



        //QString string(bytes); // string
        QString string = QString::fromUtf8(bytes);
        ui->textBrowser->setText(string);
    }
}

void MainWindow::newRecordFinishedSlot(QNetworkReply *reply) {
    qDebug() << "new record Slot finished.";
    qDebug() << reply->error();
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        // Parse data
        QJsonParseError json_error;
        QJsonDocument parseDocument = QJsonDocument::fromJson(bytes, &json_error);
        if (json_error.error == QJsonParseError::NoError) {
            QJsonObject obj = parseDocument.object();
            QJsonValue info_value = obj.take("info");
            if (info_value.toString()=="Success"){
                ui->textBrowser->setText("Success");
            }else{
                ui->textBrowser->setText("Oops");
            }
            qDebug() << "info :" << info_value.toString() << endl;
        }
    }
}