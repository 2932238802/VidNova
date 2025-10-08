#pragma once
#include <QObject>
#include <QJsonArray>

#include "net/netClient.h"
#include "dataCenter/data.h"
#include "common/myLog.h"


namespace model
{
    class DataCenter : public QObject
    {
        Q_OBJECT
    public:
        void setMode(bool is_append);
        explicit DataCenter(QObject *parent = nullptr);
        DataCenter(const DataCenter &) = delete;
        DataCenter(DataCenter &&) = delete;
        DataCenter &operator=(const DataCenter &) = delete;
        DataCenter &operator=(DataCenter &&) = delete;
        const KindAndTags *getkatPtr();
        static DataCenter* getInstance();
        void setSessionId(const QString& sessionId); // 设置sessionid;
        QString getSessionId();
        VideoList* getVideoList();
        void setVideoList(const QJsonObject& videoListJsonObject);
        void setBulletArray(const QJsonArray& bulletArray);
        const QHash<int64_t,QList<BulletInfo>>& getBullets();
        const QString& getUrl() const;
        ~DataCenter();

    public slots: // 信号槽 所有的异步请求
        void helloAsync();
        void tempLoginAsync();
        void getAllVideoListAsync();
        void getVideoByKindAsync(int kindId); //根据分类 获得视频
        void getVideoByTagAsync(int tagId); //根据分类 获得视频
        void getAllVideoListSearchTextAsync(const QString& searchText);
        void downloadPhotoAsync(const QString& photeId); // 下载图片
        void getBulletsAsync(const QString& videoId);
        void addPlayNumberAsync(const QString& videoId); // 增加播放量
        void isLikeBtnClickedAsync(const QString& videoId); // 是否被点赞过
        void addLikeNumberAsync(const QString& videoId);
        void sendBulletAsync(const QString& videoId,const BulletInfo& bulletInfo);
        // void downloadVideoAsync(const QString& videoId);

    // 信号
    signals:
        void _helloDone();
        void _loginSucDone();
        void _getAllVideoListDone();
        void _getVideoByKindDone();
        void _getVideoByTagDone();
        void _getVideoBySearchTextDone(const QString& searchText);
        void _downloadPhotoDone(const QString& photeId,QByteArray imageData);
        void _downloadVideoDone(const QString&  m3u8Path,const QString& videoId);
        void _getBulletsDone(const QString& videoId);
        void _isLikeBtnClicked(const QString& videoId,bool is_liked);


    private:
        static DataCenter* instance;
        bool isAppend;
        const QString serverUrl = "http://127.0.0.1:8080";

        VideoList* videoList = nullptr;
        QHash<int64_t,QList<BulletInfo>> bullets;
        KindAndTags* kat = nullptr;
        net::NetClient client;
        QString sessionId;
    };
}
