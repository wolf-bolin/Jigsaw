#include "rankbrowser.h"
#include "ui_rankbrowser.h"

rankBrowser::rankBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rankBrowser)
{
    ui->setupUi(this);
    ui->gameRecordTable->setColumnCount(4);
    ui->gameRecordTable->horizontalHeader()->setDefaultSectionSize(80);
    QStringList header;
    header<<tr("用户名")<<tr("时间")<<tr("步数")<<tr("分数");
    ui->gameRecordTable->setHorizontalHeaderLabels(header);
    QFont font = ui->gameRecordTable->horizontalHeader()->font();
    font.setBold(true);
    ui->gameRecordTable->horizontalHeader()->setFont(font);
    ui->gameRecordTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
    ////////////////////////////////////////////////////
    ui->globalRankTable->setColumnCount(4);
    ui->globalRankTable->horizontalHeader()->setDefaultSectionSize(80);
    ui->globalRankTable->setHorizontalHeaderLabels(header);
    ui->globalRankTable->horizontalHeader()->setFont(font);
    ui->globalRankTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

    manager = new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply * )), this, SLOT(getRankFinishedSlot(QNetworkReply * )));

}
rankBrowser::~rankBrowser()
{
    delete ui;
}
void rankBrowser::getGlobalRank(int maxScore){
    QUrl url("http://jigsaw.api.admirable.one/getRank?my_highest_score="+QString::number(maxScore,10));
    QNetworkRequest request(url);
    manager->get(request);
    qDebug() << "GetRank network request sent."+url.toString();
}

void rankBrowser::loadData(){
    readGameLog(gameRecord);
    showLocalMessage();
    int maxRecord=(1<<30);
    for(int i=0;i!=gameRecord.size();i++){
        if(gameRecord[i].score<maxRecord){
            maxRecord=gameRecord[i].score;
        }
    }
    getGlobalRank(maxRecord);
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
void rankBrowser::getRankFinishedSlot(QNetworkReply *reply) {
    qDebug() << "Slot finished.";
    qDebug() << reply->error();

    globalRecord.clear();

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
                        globalRank=rank_value.toInt();
                        qDebug() << "My rank:" << rank_value.toInt();
                        QString rank = rank_value.toString();
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
            while(ui->globalRankTable->rowCount()>0){
                ui->globalRankTable->removeRow(0);
            }
            ui->globalRankTable->insertRow(0);
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setText("数据获取失败");
            ui->globalRankTable->setItem(0,0,item);
        }
    }else{
        while(ui->globalRankTable->rowCount()>0){
            ui->globalRankTable->removeRow(0);
        }
        ui->globalRankTable->insertRow(0);
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText("数据获取失败");
        ui->globalRankTable->setItem(0,0,item);
    }
}
