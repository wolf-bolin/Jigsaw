#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QJsonArray>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QJsonParseError json_error;
    QByteArray byte_array = "{\"name\": \"Qt\",\"version\": 5,\"windows\": true}";
    QJsonDocument parseDocument = QJsonDocument::fromJson(byte_array, &json_error);
    if (json_error.error == QJsonParseError::NoError) {
        if (parseDocument.isObject()) {
            QJsonObject obj = parseDocument.object();
            if (obj.contains("name")) {
                QJsonValue name_value = obj.take("name");
                if (name_value.isString()) {
                    QString name = name_value.toString();
                    qDebug() << name << endl;
                }
            }
            if (obj.contains("version")) {
                QJsonValue version_value = obj.take("version");
                if (version_value.isDouble()) {
                    int version = version_value.toVariant().toInt();
                    qDebug() << version << endl;

                }
            }
            if (obj.contains("windows")) {
                QJsonValue version_value = obj.take("windows");
                if (version_value.isBool()) {
                    bool flag = version_value.toBool();
                    qDebug() << flag << endl;

                }
            }
        }
    }
    return a.exec();
}
