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

    class KindAndTags{

    public:
        KindAndTags();
        const QList<QString> getAllKinds() const; // 获取所有的分类
        const QHash<QString,int> getAllLabels(const QString& kind) const; // 获取所有的标签
        int getKindId(const QString& kind_name) const;
        int getTagId(const QString& kind_name,const QString& tag_name) const;

    private:
        // 分类 这个int 就是对应的 id 用于服务器
        QHash<QString,int> kinds;
        QHash<QString,QHash<QString,int>> tags;
        static int id;
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


    public:
        void loadVideoInfoFromJson(const QJsonObject& videoInfoJson);
    };


    class VideoList{

    public:
        VideoList();
        void setPageIndex(int page_index);
        int getPageIndex() const;

        int getVideoCount() const;
        void setVideoCount(int64_t count);

        int getVideoTotalCount() const;
        void setVideoTotalCount(int64_t count) ;
        void addVideoInfo(const VideoInfo& info);
        const QList<VideoInfo>& getVideoListOfVideoInfo() const;
        void clearVideoList(); // 清空一下任务列表
        void updateLikeNumber(const QString& videoId,int64_t likeCount);

    public:
        QList<VideoInfo> videoInfoLists;
        int pageIndex;
        int64_t videoCount;
        int64_t videoTotalCount;
        const static int PAGE_COUNT = 20;  // 一页中的

    };

    class BulletInfo{
    public:
        QString barrageId; // 弹幕id
        QString userId; // 用户id
        int64_t playTime; //
        QString text;

    public:
        void loadBarrageInfo(const QJsonObject& barrage_object_info);
    };

};


