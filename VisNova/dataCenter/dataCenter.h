#pragma once
#include <QObject>
#include <QJsonArray>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>

#include "getVideoPageType.h"
#include "bulletInfo.h"
#include "kindandtags.h"
#include "videoList.h"
#include "dataCenter/userInfo.h"
#include "dataCenter/videoList.h"
#include "dataCenter/videoInfoForUpload.h"
#include "dataCenter/adminInfo.h"
#include "net/netClient.h"
#include "common/myLog.h"
#include "common/constants.h"

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

        void setAdminList(const QJsonObject& adminListJson,bool isAdminState = true);
        void setMode(bool is_append);
        void setSessionId(const QString& sessionId); // 设置sessionid;
        void setVideoList(const QJsonObject& videoListJsonObject);
        void setManageSearchVideoList(const QJsonObject& videoListJsonObject); // 管理员 界面通过 搜索关键 字 设置 对应的视频列表
        void setBulletArray(const QJsonArray& bulletArray); // 封面的视频列表
        void setMyselfInfo(const QJsonObject& myself_json); // 用户信息
        void setOtherInfo(const QJsonObject& other_json); // 他人的用户信息
        void setAvatar(const QString& fileId); // 设置头像 个人的
        void setUserVideoList(const QJsonObject& videoList); // 设置用户的视频列表

        void initDataFile();
        void saveDataFile();
        void loadDataFile();

        VideoList* getUserVideoList();
        static DataCenter* getInstance();
        const QString& getSessionId()const;
        const QString& getUrl() const;
        VideoList* getVideoList();
        VideoList* getManageSearchVideoList();
        AdminList* getAdminList();
        KindAndTags *getkatPtr();
        const QHash<int64_t,QList<BulletInfo>>& getBullets();
        UserInfo* getMyselfInfo() const; // 获取个人信息
        UserInfo* getOtherInfo() const;
        const QString& getUserId();

        void clear();

        ~DataCenter();

    public:
        void alterAttentionAsync(const QString& user_id);
        void addPlayNumberAsync(const QString& videoId); // 增加播放量
        void addLikeNumberAsync(const QString& videoId);
        void addAttentionAsync(const QString& userId); // 新增关注
        void addAdminAsync(const model::AdminInfo& userInfo);

        void checkVideoAsync(const QString& videoId,bool result);

        void downloadPhotoAsync(const QString& photeId); // 下载图片
        void deleteVideoAsync(const QString& video);
        void delAttentionAsync(const QString&userId); // 取消关注
        void delAdminAsync(const QString& userId);


        void getCodeFromEmailAsync(const QString& email);
        void getAllVideoListAsync();
        void getVideoByKindAsync(int kindId); //根据分类 获得视频
        void getVideoByTagAsync(int tagId); //根据分类 获得视频
        void getVideoByStateAsync(model::VideoState videoState,int page_index); // 根据视频 状态获取视频列表 管理员的
        void getVideoListForMyselfOrOtherAsync(const QString &userId,int pageIndex,GetVideoPage page);
        void getBulletsAsync(const QString& videoId);
        void getAllVideoListSearchTextAsync(const QString& searchText);
        void getMyselfInfoAsync();
        void getOtherInfoAsync(const QString& user_id);
        void getAdminInfoByEmailAsync(const QString& photoNumber);
        void getAdminInfoByStateAsync(int page, AdminState state);

        void helloAsync();

        void isLikeBtnClickedAsync(const QString& videoId); // 是否被点赞过

        void logoutAsync();        // 登出
        void loadTempUserInfo();
        void lrByAuthCodeAsync(const QString &email, const QString &auth_code,const QString&codeId);
        void lrByPdAsync(const QString& at,const QString& pd);
        void loginBySessionAsync();

        void putOnVideoAsync(const QString& videoId);
        void putDownVideoAsync(const QString& videoId);

        void setAvatarAsync(const QString& fileId);
        void setAdminAsync(const model::AdminInfo& adminUserInfo);
        void setUserIdOnce(const QString& userId);
        void setNewPasswordAsync(const QString& password);
        void setNicknameAsync(const QString& nickName);
        void setAdminStateAsync(const QString& userId,AdminState state);
        void sendBulletAsync(const QString& videoId,const BulletInfo& bulletInfo);


        void tempLoginAsync();

        void uploadPhotoAsync(const QByteArray& photo,PhotoUploadPurpose pup);
        void uploadVideoAsync(const QString& video_path);
        void uploadVideoInfoForUploadAsync(const VideoInfoForUpload& videoInfoForUpload);

    signals:
        void _addAttention();
        void _addAdminDone();

        void _checkVideoDone(); // 视频审核的接口

        void _downloadPhotoDone(const QString& photeId,QByteArray imageData);
        void _downloadVideoDone(const QString&  m3u8Path,const QString& videoId);
        void _deleteVideoDone(const QString& userId);
        void _delAttention();
        void _delAdminDone();

        void _getVideoBySearchTextDone(const QString& searchText);
        void _getBulletsDone(const QString& videoId);
        void _getAllVideoListDone();
        void _getVideoByKindDone();
        void _getVideoByTagDone();
        void _getVideoByStateDone(); // 管理员 获取状态视频列表
        void _getMyselfInfoDone();
        void _getOtherInfoDone();
        void _getVideoListForMyselfOrOtherDone(const QString& userId,GetVideoPage page);
        void _getCodeFromEmailDone(const QString& authCode,const QString& codeId);
        void _getAdminInfoByEmailDone();
        void _getAdminInfoByStateDone();


        void _helloDone();

        void _isLikeBtnClicked(const QString& videoId,bool is_liked);

        void _loginSucDone();
        void _lrByAuthCodeSuc();
        void _lrByAuthCodeFailed(const QString& msg);
        void _loginBySessionSuc(bool isTemp);
        void _loginBySessionFailed(const QString& msg);
        void _logoutDone();
        void _lrByPdSuc();                                   // 登录成功
        void _lrByPdFailed(const QString& msg);             // 登录失败

        void _putOnVideoDone();
        void _putDownVideoDone();

        void _setAvatarDone();                              // 这个表示用户头像设置成功
        void _setPasswordDone();                            // 设置密码
        void _setNicknameDone(const QString& nickName);                            // 设置昵称成功
        void _setAdminDone();
        void _setAdminStateDone();

        void _uploadPhotoDone(const QString& file_id,PhotoUploadPurpose pup);
        void _uploadVideoDone(const QString& video_path);
        void _uploadVideoInfoForUpload();

    private:
        static DataCenter* instance;
        QHash<int64_t,QList<BulletInfo>> bullets;

        std::unique_ptr<net::NetClient> client;
        std::unique_ptr<KindAndTags> kat;

        std::unique_ptr<VideoList> videoList;
        std::unique_ptr<VideoList> userVideoList;
        std::unique_ptr<VideoList> manageSearchVideoList; // 管理员 通过搜索引擎 搜索的视频列表

        std::unique_ptr<AdminList> adminList;
        std::unique_ptr<UserInfo> myselfInfo;
        std::unique_ptr<UserInfo> otherInfo;

        const QString serverUrl = "http://127.0.0.1:8080";

        QString sessionId;
        QString userId; // 这个存放userId // 只能被登录的时候初始化一次

        bool isAppend;
        bool isOriginUser = false;
    };
}
