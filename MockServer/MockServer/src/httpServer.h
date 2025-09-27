#pragma once
#include <QObject>
#include <QHttpServer>
#include <QJsonDocument>
#include <QTcpServer>
#include <QHttpServerResponse>
#include <QJsonObject>
#include "mylog.h"

//////////////////////////////////////////////////////
/// \brief The HttpServer class
///
class HttpServer : public QObject
{
    Q_OBJECT
private:
    explicit HttpServer(QObject *parent = nullptr);
    QHttpServerResponse helloService(const QHttpServerRequest& request);

private:
    static HttpServer* instance;
    std::unique_ptr<QHttpServer> httpServer; // 服务
    std::unique_ptr<QTcpServer> tcpServer;

public:
    static HttpServer* getInstance(); // 单例模式
    bool init();

};
//////////////////////////////////////////////////////
