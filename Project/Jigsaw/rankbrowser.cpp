#include "rankbrowser.h"
#include "ui_rankbrowser.h"

rankBrowser::rankBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rankBrowser)
{
    ui->setupUi(this);

    QStringList header;
    header<<tr("用户名")<<tr("时间")<<tr("步数")<<tr("分数");
    ui->gameRecordTable->setColumnCount(4);
    ui->gameRecordTable->setHorizontalHeaderLabels(header);
    ui->gameRecordTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QFont font = ui->gameRecordTable->horizontalHeader()->font();
    font.setBold(true);
    ui->gameRecordTable->horizontalHeader()->setFont(font);
    ui->gameRecordTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
    ////////////////////////////////////////////////////
    ui->globalRankTable->setColumnCount(4);
    ui->globalRankTable->setHorizontalHeaderLabels(header);
    ui->globalRankTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->globalRankTable->horizontalHeader()->setFont(font);
    ui->globalRankTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

    manager = new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply * )), this, SLOT(getRankFinishedSlot(QNetworkReply * )));

    QPixmap pix;
    pix.load(":/picture/rankBackground.png");
    resize(pix.size());
    setMask(pix.mask());

    int loadedFontID = QFontDatabase::addApplicationFont(":/font/miaowu.ttf");
    QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
    QString mwfont = loadedFontFamilies.at(0);
    ui->personalInfo->setFont(QFont(mwfont,20));

    ui->sureButton->setStyleSheet(ButtonStyle);
    ui->sureButton->setFont(QFont(mwfont,16));
}

rankBrowser::~rankBrowser()
{
    delete ui;
}

void rankBrowser::loadData(){
    //可从外部调用的数据加载函数
    readGameLog(gameRecord);
    showLocalMessage();
    int maxRecord=(1<<30),index=-1;
    for(unsigned int i=0;i!=gameRecord.size();i++){
        if(gameRecord[i].score<maxRecord){
            maxRecord=gameRecord[i].score;
            index=i;
        }
    }
    if(index!=-1){
        ui->personalInfo->setText("您的最好成绩为"+QString::number(gameRecord[index].score)+"分");
        getGlobalRank(maxRecord);
    }else{
        ui->personalInfo->setText("");
        getGlobalRank(-1);
    }

}

void rankBrowser::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/picture/rankBackground.png"));
}

void rankBrowser::mousePressEvent(QMouseEvent *event){
    if(event->button()== Qt::LeftButton)
    {
        offset=event->globalPos()-pos();
    }
}

void rankBrowser::mouseMoveEvent(QMouseEvent *event){
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

void rankBrowser::mouseReleaseEvent(QMouseEvent *event){
    if(!event->buttons())
    {
        QCursor cursor;
        cursor.setShape(Qt::ArrowCursor);
        setCursor(cursor);
    }
}

// ////////////////////////////////////////////////////////////////////
//槽函数
void rankBrowser::on_sureButton_clicked()
{
    rankBrowser::close();
}

void rankBrowser::getRankFinishedSlot(QNetworkReply *reply) {
    //HTTP响应槽 获取全球排名
    qDebug() << "Slot finished.";
    qDebug() << reply->error();

    globalRecord.clear();
    while(ui->globalRankTable->rowCount()>0){
        ui->globalRankTable->removeRow(0);
    }

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
                    if (rank_value.isDouble()&&rank_value.toInt()!=-1) {
                        globalRank=rank_value.toInt();
                        qDebug() << "My rank:" << rank_value.toInt();
                        ui->personalInfo->setText(ui->personalInfo->text()+" 全球排名："+QString::number(rank_value.toInt(),10));
                    }
                }
                if (obj.contains("ranking_list")) {
                    QJsonArray ranking_array = obj.take("ranking_list").toArray();
                    for (int i = 0; i < ranking_array.size(); i++) {
                        globalRecord.push_back(gameinfo(ranking_array.at(i).toArray().at(1).toString().toStdString(),
                                                        ranking_array.at(i).toArray().at(4).toInt(),
                                                        ranking_array.at(i).toArray().at(3).toInt(),
                                                        ranking_array.at(i).toArray().at(2).toInt()
                                                   ));
                        qDebug() << ranking_array.at(i).toArray().at(1).toString() << " "//username
                        << ranking_array.at(i).toArray().at(2).toInt() << " "//score
                        << ranking_array.at(i).toArray().at(3).toInt() << " "//difficulty
                        << ranking_array.at(i).toArray().at(4).toInt();//time-used
                    }
                }
            }

            std::sort(globalRecord.begin(),globalRecord.end());
            for(unsigned int i=0;i!=globalRecord.size();i++){
                std::cout<<globalRecord[i].userName<<"  "
                        <<globalRecord[i].gameTime<<"  "
                       <<globalRecord[i].gameStep<<"  "
                      <<globalRecord[i].score<<std::endl;
                int row_count = ui->globalRankTable->rowCount(); //获取表单行数
                ui->globalRankTable->insertRow(row_count);      //插入新行
                QTableWidgetItem *item1,*item2,*item3,*item4;   //新建一个item
                item1 = new QTableWidgetItem();
                item2 = new QTableWidgetItem();
                item3 = new QTableWidgetItem();
                item4 = new QTableWidgetItem();
                item1->setText(QString::fromStdString(globalRecord[i].userName));            //给这个item设置文本
                ui->globalRankTable->setItem(row_count,0,item1); //将这个item加入到表单的第row_count行，第0列当中去
                item2->setText(QString::number(globalRecord[i].gameTime,10));
                ui->globalRankTable->setItem(row_count,1,item2);
                item3->setText(QString::number(globalRecord[i].gameStep,10));
                ui->globalRankTable->setItem(row_count,2,item3);
                item4->setText(QString::number(globalRecord[i].score,10));
                ui->globalRankTable->setItem(row_count,3,item4);
            }

        }else{
            ui->globalRankTable->insertRow(0);
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("数据获取失败");
            ui->globalRankTable->setItem(0,0,item);
        }
    }else{
        ui->globalRankTable->insertRow(0);
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText("数据获取失败");
        ui->globalRankTable->setItem(0,0,item);
    }
}

// ///////////////////////////////////////////////////////////////////
//逻辑代码
void rankBrowser::getGlobalRank(int maxScore){
    //发起HTTP请求 获取全球排名
    QUrl url("http://jigsaw.api.admirable.one/getRank?my_highest_score="+QString::number(maxScore,10));
    QNetworkRequest request(url);
    manager->get(request);
    qDebug() << "GetRank network request sent."+url.toString();
}

void rankBrowser::showLocalMessage(){
    while(ui->gameRecordTable->rowCount()>0){
        ui->gameRecordTable->removeRow(0);
    }
    for(unsigned int i=0;i!=gameRecord.size();i++){
        std::cout<<gameRecord[i].userName<<"  "
                <<gameRecord[i].gameTime<<"  "
               <<gameRecord[i].gameStep<<"  "
              <<gameRecord[i].score<<std::endl;
        int row_count = ui->gameRecordTable->rowCount(); //获取表单行数
        ui->gameRecordTable->insertRow(row_count);      //插入新行
        QTableWidgetItem *item1,*item2,*item3,*item4;   //新建一个item
        item1 = new QTableWidgetItem();
        item2 = new QTableWidgetItem();
        item3 = new QTableWidgetItem();
        item4 = new QTableWidgetItem();
        item1->setText(QString::fromStdString(gameRecord[i].userName));            //给这个item设置文本
        ui->gameRecordTable->setItem(row_count,0,item1); //将这个item加入到表单的第row_count行，第0列当中去
        item2->setText(QString::number(gameRecord[i].gameTime,10));
        ui->gameRecordTable->setItem(row_count,1,item2);
        item3->setText(QString::number(gameRecord[i].gameStep,10));
        ui->gameRecordTable->setItem(row_count,2,item3);
        item4->setText(QString::number(gameRecord[i].score,10));
        ui->gameRecordTable->setItem(row_count,3,item4);
    }
}
