#include "success.h"
#include "ui_success.h"

success::success(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::success)
{
    ui->setupUi(this);

    QPixmap pix;
    pix.load(":/picture/successBackground.png");
    resize(pix.size());
    setMask(pix.mask());

    int loadedFontID = QFontDatabase::addApplicationFont(":/font/miaowu.ttf");
    QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
    QString font = loadedFontFamilies.at(0);
    ui->scoreLabel->setFont(QFont(font,36));
    ui->stepLabel->setFont(QFont(font,36));
    ui->timeLabel->setFont(QFont(font,36));
    ui->userNameEdit->setFont(QFont(font,20));
    ui->sureButton->setFont(QFont(font,20));
    ui->sureButton->setStyleSheet(ButtonStyle);

    ui->userNameEdit->setText("newUser");
}

void success::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/picture/successBackground.png"));
}

success::~success()
{
    delete ui;
}

void success::mousePressEvent(QMouseEvent *event){
    if(event->button()== Qt::LeftButton)
    {
        offset=event->globalPos()-pos();
    }
}

void success::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons()&Qt::LeftButton)
    {
        QPoint temp;
        QCursor cursor;
        cursor.setShape(Qt::OpenHandCursor);
        setCursor(cursor);

        temp=event->globalPos()-offset;
        move(temp);
    }
}

void success::mouseReleaseEvent(QMouseEvent *event){
    if(!event->buttons())
    {
        QCursor cursor;
        cursor.setShape(Qt::ArrowCursor);
        setCursor(cursor);
    }
}

void success::on_sureButton_clicked()
{
    if(ui->userNameEdit->text()==""){
        QMessageBox::information(this,tr("提示"),tr("给自己起个名字吧~"));
        ui->userNameEdit->setText("newUser");
    }
    QString username = ui->userNameEdit->text();
    qDebug()<<username;
    personal->userName=username.toStdString();

    readGameLog(gameRecord);
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
    ui->scoreLabel->setText(QString::number(personal->score,10));
    ui->stepLabel->setText(QString::number(personal->gameStep,10));
    ui->timeLabel->setText(QString::number(personal->gameTime,10));
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
