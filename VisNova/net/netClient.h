#pragma once
#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QUuid>
#include "common/myLog.h"

namespace net {
class netClient : public QObject
{
    Q_OBJECT
public:
    explicit netClient();
    void hello();
    QString makeRequestUuid();

private:
    const QString baseUrl = "http://127.0.0.1:8080";
    QNetworkAccessManager manage;

signals:
};
}




