#pragma once
#include <QObject>
#include <QHttpServer>
#include <QJsonDocument>
#include <QTcpServer>
#include <QHttpServerResponse>
#include <QJsonObject>
#include <QJsonArray>
#include <QMimeDatabase>
#include <QDir>
#include <QMimeType>
#include "data.h"
#include "mylog.h"
#include "loadFileToByteArray.h"
#include "rand.h"
#include "common/loadFileToByteArray.h"

enum RoleType{
    SuperAdmin = 1,
    Admin,
    User,
    TempUser
};


//////////////////////////////////////////////////////
/// \brief The HttpServer class
///
class HttpServer : public QObject
{
    Q_OBJECT
public:
    static HttpServer* getInstance(); // 单例模式
    void buildResponseData();
    bool init();

private:
    explicit HttpServer(QObject *parent = nullptr);

    QHttpServerResponse allVideoList(const QHttpServerRequest& request);
    QHttpServerResponse addPlayNumber(const QHttpServerRequest& request);
    QHttpServerResponse addLikeNumber(const QHttpServerRequest& request);
    QHttpServerResponse addAttention(const QHttpServerRequest& request);
    QHttpServerResponse alterAttention(const QHttpServerRequest& request);

    QHttpServerResponse checkVideo(const QHttpServerRequest& request);


    QHttpServerResponse downloadPhoto(const QHttpServerRequest& request);
    QHttpServerResponse downloadVideoM3u8File(const QHttpServerRequest& request);
    QHttpServerResponse downloadVideoSegmentation(const QString& request);
    QHttpServerResponse deleteVideo(const QHttpServerRequest& request);
    QHttpServerResponse delAttention(const QHttpServerRequest& request);

    QHttpServerResponse getBullets(const QHttpServerRequest& request);
    QHttpServerResponse getUserInfo(const QHttpServerRequest& request);
    QHttpServerResponse getCodeFromEmail(const QHttpServerRequest& request);
    QHttpServerResponse getUserVideoInfo(const QHttpServerRequest& request);
    QHttpServerResponse getAdminListByEmail(const QHttpServerRequest& request);
    QHttpServerResponse getAdminListByState(const QHttpServerRequest& request);

    QHttpServerResponse helloService(const QHttpServerRequest& request);

    QHttpServerResponse isLikeBtnClicked(const QHttpServerRequest& request);

    QHttpServerResponse lrByAuthCode(const QHttpServerRequest& request);
    QHttpServerResponse lrByPd(const QHttpServerRequest& request);
    QHttpServerResponse loginBySession(const QHttpServerRequest& request); // session 登录
    QHttpServerResponse logout(const QHttpServerRequest& request);

    QHttpServerResponse newBullet(const QHttpServerRequest& request);
    QHttpServerResponse newVideo(const QHttpServerRequest& request);

    QHttpServerResponse putOnVideo(const QHttpServerRequest& request);
    QHttpServerResponse putDownVideo(const QHttpServerRequest& request);


    QHttpServerResponse setAvatar(const QHttpServerRequest& request);
    QHttpServerResponse setPassword(const QHttpServerRequest& request);
    QHttpServerResponse setNickname(const QHttpServerRequest& request);

    QHttpServerResponse uploadPhoto(const QHttpServerRequest& request);
    QHttpServerResponse uploadVideo(const QHttpServerRequest& request);

    QHttpServerResponse videoByKind(const QHttpServerRequest& request);
    QHttpServerResponse videoByTag(const QHttpServerRequest& request);
    QHttpServerResponse videoByKey(const QHttpServerRequest& request);
    QHttpServerResponse videoByState(const QHttpServerRequest& request);



private:
    static HttpServer* instance;
    std::unique_ptr<QHttpServer> httpServer; // 服务
    std::unique_ptr<QTcpServer> tcpServer;
    QMap<QString,QString> m_sessions;

public:

    QMap<QString,QString> idPathMap; // 映射表
    QHash<int64_t,QList<BulletInfo>> bullets; // 弹幕数据
    RoleType roleType = RoleType::TempUser;
    int pageCount = 20;
};
//////////////////////////////////////////////////////
