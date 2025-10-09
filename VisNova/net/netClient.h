#pragma once
#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QUuid>
#include <QStandardPaths>
#include "dataCenter/videoInfo.h"
#include "common/myLog.h"
#include "common/ReadLocalFile.h"
#include "dataCenter/bulletInfo.h"


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
    void loginTemplateAccess();

    QString makeRequestUuid();

    void setAvatar(const QString& fileId);

    void getAllVidelList();
    void getVideoByKind(int kindId);
    void getVideoByTag(int tagId);
    void getAllVideoListSearchText(const QString&str);
    void getBullets(const QString& videoId);
    void getUserInfo(const QString&userId);

    void downloadPhoto(const QString&photeId);

    void addPlayNumber(const QString& videoId);
    void isLikeBtnClicked(const QString&videoId);
    void addLikeNumber(const QString&videoId);

    void sendBullet(const QString&videoId,const model::BulletInfo&bulletInfo);
    void uploadPhoto(const QByteArray& photo_data);

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




