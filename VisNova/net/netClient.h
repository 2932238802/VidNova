#pragma once
#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QUuid>
#include <QStandardPaths>
#include "common/myLog.h"
#include "common/ReadLocalFile.h"


// 前向声明 告诉编译器 别担心 这里会有一个类
namespace model {
class DataCenter;
}


namespace net
{
class NetClient : public QObject
{
    Q_OBJECT
public:
    explicit NetClient(model::DataCenter* dataCenter);
    void hello();

    QString makeRequestUuid();
    void loginTemplateAccess();
    void getAllVidelList();
    void getVideoByKind(int kindId);
    void getVideoByTag(int tagId);
    void getAllVideoListSearchText(const QString&str);
    void downloadPhoto(const QString&photeId);
    void getBullets(const QString& videoId);
    void addPlayNumber(const QString& videoId);
    // void downloadVideo(const QString& videoId);

private:
    // 封装好的 发送 请求
    QNetworkReply* sendHttpRequest(const QString& request_path,QJsonObject& json_body);
    QJsonObject handHttpResponse(QNetworkReply* reply,bool&is_ok,QString & error_msg);


private:
    QString baseUrl;
    QNetworkAccessManager manage;
    model::DataCenter* dataCenter = nullptr;

};
}




