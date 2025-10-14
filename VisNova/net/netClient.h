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
#include "dataCenter/videoInfo.h"
#include "dataCenter/bulletInfo.h"
#include "dataCenter/videoList.h"


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

    void lrByAuthCode(const QString &email, const QString &auth_code,const QString &codeId);
    void lrByPd(const QString& at, const QString& pd);

    QString makeRequestUuid();

    void setAvatar(const QString& file_id);

    void getCodeFromEmail(const QString& email);
    void getAllVidelList();
    void getVideoByKind(int kind_id);
    void getVideoByTag(int tagId);
    void getAllVideoListSearchText(const QString&str);
    void getBullets(const QString& video_id);
    void getUserInfo(const QString&user_id);
    void getVideoListForMyselfOrOther(const QString& user_id,int page_index);

    void downloadPhoto(const QString&phote_id);

    void isLikeBtnClicked(const QString&video_id);
    void addPlayNumber(const QString& video_id);
    void alterAttention(const QString& user_id);
    void addAttention(const QString& user_id);

    void addLikeNumber(const QString&videoId);

    void sendBullet(const QString&video_id,const model::BulletInfo&bullet_info);
    void uploadPhoto(const QByteArray& photo_data);

    void deleteVideo(const QString& video_id);

    void delAttention(const QString& user_id);
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




