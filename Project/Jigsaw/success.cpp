#include "success.h"
#include "ui_success.h"

success::success(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::success)
{
    ui->setupUi(this);
    
    readGameLog(gameRecord);
}

success::~success()
{
    delete ui;
}

void success::on_sureButton_clicked()
{
    QString username = ui->userNameEdit->text();
    qDebug()<<username;
    personal->userName=username.toStdString();
    
    gameRecord.push_back(*personal);
    saveGameLog(gameRecord);
    
    
    manager = new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply * )), this, SLOT(newRecordFinishedSlot(QNetworkReply * )));
    QString HTTPurl="http://jigsaw.api.admirable.one/newRecord";
    HTTPurl+="?player_name="+QString::fromStdString(personal->userName);
    HTTPurl+="&score="+QString::number(personal->score,10);
    HTTPurl+="&difficulty="+QString::number(personal->gameStep,10);
    HTTPurl+="&time="+QString::number(personal->gameTime,10);
    QUrl url(HTTPurl);
    QNetworkRequest request(url);
    manager->get(request);
    qDebug() << "New record request sent.";
    success::close();
}

void success::setParameter(int gameTime,int gameStep,int answerStep){
    int score=gameTime*(gameStep-answerStep+1);
    personal = new gameinfo("admin",gameTime,gameStep,score);
}

void success::newRecordFinishedSlot(QNetworkReply *reply) {
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
                qDebug() << "success";
            }else{
                qDebug() << "Oops";
            }
            qDebug() << "info :" << info_value.toString() << endl;
        }
    }
}
