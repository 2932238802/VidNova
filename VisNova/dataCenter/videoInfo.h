#pragma once
#include <QString>
#include <QList>
#include <QHash>
#include <QMap>
#include <QObject>
#include <QJsonObject>
#include "common/myLog.h"
/// 处理数据结构


namespace model{

enum VideoStatus{
    NoStatus = 0,
    WaitForChecking, // 待审核
    Accessed, // 审核通过
    Reject,
    Discard, // 下架了 之前是上架的
};


class VideoInfo{

public:
    QString videoId;
    QString userId;
    QString photoId;
    QString userAvatarId;
    QString videoFileId;
    QString nickName;

    int64_t likeCount;
    int64_t playCount;
    int64_t videoSize;
    QString videoDesc;
    QString videoTitle;
    int64_t videoDuration;
    QString loadupTime; // 上传时间

    int videoStatus; // 视频状态
    QString checkerId; // 审核管理员的Id
    QString checkerName; // 审核管理员的名字
    QString checkAvatarId; // 审核管理员的图像Id

public:
    void loadVideoInfoFromJson(const QJsonObject& videoInfoJson);
};
};


