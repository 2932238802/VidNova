#pragma once
#include <QObject>
#include <QJsonArray>
#include "net/netClient.h"
#include "dataCenter/videoInfo.h"
#include "common/myLog.h"
#include "bulletInfo.h"
#include "kindandtags.h"
#include "videoList.h"
#include "dataCenter/userInfo.h"

namespace model
{
    class DataCenter : public QObject
    {
        Q_OBJECT
    public:
        explicit DataCenter(QObject *parent = nullptr);
        DataCenter(const DataCenter &) = delete;
        DataCenter(DataCenter &&) = delete;
        DataCenter &operator=(const DataCenter &) = delete;
        DataCenter &operator=(DataCenter &&) = delete;

        void setMode(bool is_append);
        void setSessionId(const QString& sessionId); // 设置sessionid;
        void setVideoList(const QJsonObject& videoListJsonObject);
        void setBulletArray(const QJsonArray& bulletArray);
        void setMyselfInfo(const QJsonObject& myself_json);
        void setOtherInfo(const QJsonObject& other_json);
        void setAvatar(const QString& fileId);


        static DataCenter* getInstance();
        const QString& getSessionId()const;
        const QString& getUrl() const;
        VideoList* getVideoList();
        KindAndTags *getkatPtr();
        const QHash<int64_t,QList<BulletInfo>>& getBullets();
        std::shared_ptr<UserInfo> getMyselfUserInfo() const; // 获取个人信息
        std::shared_ptr<UserInfo> getOtherUserInfo() const;
        ~DataCenter();

    public:
        void helloAsync();
        void tempLoginAsync();

        void setAvatarAsync(const QString& fileId);

        void getAllVideoListAsync();
        void getVideoByKindAsync(int kindId); //根据分类 获得视频
        void getVideoByTagAsync(int tagId); //根据分类 获得视频
        void getBulletsAsync(const QString& videoId);
        void getAllVideoListSearchTextAsync(const QString& searchText);
        void getMyselfInfoAsync();
        void getOtherInfoAsync(const QString& user_id);

        void downloadPhotoAsync(const QString& photeId); // 下载图片

        void isLikeBtnClickedAsync(const QString& videoId); // 是否被点赞过

        void addPlayNumberAsync(const QString& videoId); // 增加播放量
        void addLikeNumberAsync(const QString& videoId);

        void sendBulletAsync(const QString& videoId,const BulletInfo& bulletInfo);
        void uploadPhotoAsync(const QByteArray& photo);
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
        void _getMyselfInfoDone();
        void _getOtherInfoDone();
        void _uploadPhotoDone(const QString& file_id);
        void _setAvatarDone(); // 这个表示用户头像设置成功


    private:
        static DataCenter* instance;
        QHash<int64_t,QList<BulletInfo>> bullets;
        std::unique_ptr<net::NetClient> client;
        std::unique_ptr<KindAndTags> kat = nullptr;
        std::unique_ptr<VideoList> videoList = nullptr;
        std::shared_ptr<UserInfo> myselfInfo;
        std::shared_ptr<UserInfo> otherInfo;

        const QString serverUrl = "http://127.0.0.1:8080";
        QString sessionId;
        bool isAppend;
    };
}
