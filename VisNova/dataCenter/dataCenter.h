#pragma once
#include <QObject>
#include <QJsonArray>
#include "net/netClient.h"
#include "bulletInfo.h"
#include "kindandtags.h"
#include "videoList.h"
#include "dataCenter/userInfo.h"
#include "dataCenter/videoList.h"

#include "common/myLog.h"

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
        void setBulletArray(const QJsonArray& bulletArray); // 封面的视频列表
        void setMyselfInfo(const QJsonObject& myself_json); // 用户信息
        void setOtherInfo(const QJsonObject& other_json); // 他人的用户信息
        void setAvatar(const QString& fileId); // 设置头像 个人的
        void setUserVideoList(const QJsonObject& videoList); // 设置用户的视频列表

        VideoList* getUserVideoList();
        static DataCenter* getInstance();
        const QString& getSessionId()const;
        const QString& getUrl() const;
        VideoList* getVideoList();
        KindAndTags *getkatPtr();
        const QHash<int64_t,QList<BulletInfo>>& getBullets();
        UserInfo* getMyselfUserInfo() const; // 获取个人信息
        UserInfo* getOtherUserInfo() const;

        void buildTempUserInfo();

        ~DataCenter();

    public:
        void helloAsync();
        void tempLoginAsync();

        void setAvatarAsync(const QString& fileId);
        void setUserIdOnce(const QString& userId);

        void getCodeFromEmailAsync(const QString& email);
        void getAllVideoListAsync();
        void getVideoByKindAsync(int kindId); //根据分类 获得视频
        void getVideoByTagAsync(int tagId); //根据分类 获得视频
        void getVideoListForMyselfOrOtherAsync(const QString &userId,int pageIndex);
        void getBulletsAsync(const QString& videoId);
        void getAllVideoListSearchTextAsync(const QString& searchText);
        void getMyselfInfoAsync();
        void getOtherInfoAsync(const QString& user_id);

        void downloadPhotoAsync(const QString& photeId); // 下载图片

        void isLikeBtnClickedAsync(const QString& videoId); // 是否被点赞过
        void alterAttentionAsync(const QString& user_id);

        void addPlayNumberAsync(const QString& videoId); // 增加播放量
        void addLikeNumberAsync(const QString& videoId);
        void addAttentionAsync(const QString& userId); // 新增关注

        void sendBulletAsync(const QString& videoId,const BulletInfo& bulletInfo);
        void uploadPhotoAsync(const QByteArray& photo);
        // void downloadVideoAsync(const QString& videoId);

        void deleteVideoAsync(const QString& video);
        void delAttentionAsync(const QString&userId); // 取消关注

    // 信号
    signals:
        void _helloDone();
        void _loginSucDone();

        void _isLikeBtnClicked(const QString& videoId,bool is_liked);

        void _downloadPhotoDone(const QString& photeId,QByteArray imageData);
        void _downloadVideoDone(const QString&  m3u8Path,const QString& videoId);

        void _getVideoBySearchTextDone(const QString& searchText);
        void _getBulletsDone(const QString& videoId);
        void _getAllVideoListDone();
        void _getVideoByKindDone();
        void _getVideoByTagDone();
        void _getMyselfInfoDone();
        void _getOtherInfoDone();
        void _getVideoListForMyselfOrOtherDone(const QString& userId);
        void _getCodeFromEmailDone(const QString& authCode);

        void _uploadPhotoDone(const QString& file_id);
        void _setAvatarDone(); // 这个表示用户头像设置成功

        void _deleteVideoDone(const QString& userId);
        void _delAttention();
        void _addAttention();



    private:
        static DataCenter* instance;
        QHash<int64_t,QList<BulletInfo>> bullets;

        std::unique_ptr<net::NetClient> client;
        std::unique_ptr<KindAndTags> kat;

        std::unique_ptr<VideoList> videoList;
        std::unique_ptr<VideoList> userVideoList;

        std::unique_ptr<UserInfo> myselfInfo;
        std::unique_ptr<UserInfo> otherInfo;

        const QString serverUrl = "http://127.0.0.1:8080";
        QString sessionId;

        QString userId; // 这个存放userId // 只能被登录的时候初始化一次
        QString userIdInMyPage;

        bool isAppend;
        bool isOriginUser = false;
    };
}
