#include "dataCenter.h"

namespace model
{
DataCenter* DataCenter::instance = nullptr;

void DataCenter::setMode(bool is_append)
{
    isAppend = is_append;

#ifdef DATACENTER_TEST
    LOG() << "DataCenter::setMode(bool is_append)";
    LOG() << "isAppend is "  << is_append;
#endif


}

DataCenter::DataCenter(QObject *parent)
    : QObject{parent}, isAppend(false)
{
    client = std::make_unique<net::NetClient>(this);

    userVideoList = std::make_unique<VideoList>();

    kat = std::make_unique<KindAndTags>();

    videoList = std::make_unique<VideoList>();

    myselfInfo = nullptr;

    otherInfo = nullptr;
}

KindAndTags *DataCenter::getkatPtr()
{
    if(kat == nullptr)
    {
        kat = std::make_unique<KindAndTags>();
    }
    return kat.get();
}



DataCenter::~DataCenter()
{

}

///////////////////////////////////////
/// \brief DataCenter::helloAsync
///
void DataCenter::helloAsync()
{
    client->hello();
}
///////////////////////////////////////

///////////////////////////////////////
/// \brief DataCenter::tempLoginAsync
///
void DataCenter::tempLoginAsync()
{
    client->loginTemplateAccess();
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::lrByAuthCodeAsync
/// \param email
/// \param auth_code
///
void DataCenter::lrByAuthCodeAsync(const QString &email, const QString &auth_code,const QString&codeId)
{
    client->lrByAuthCode(email,auth_code,codeId);
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief DataCenter::lrByPdAsync
/// \param at
/// \param pd
///
void DataCenter::lrByPdAsync(const QString &at, const QString &pd)
{

#ifdef DATACENTER_TEST
    LOG() << "DataCenter::lrByPdAsync(const QString &at, const QString &pd)";
    LOG() << "at:" << at;
    LOG() << "pd:" << pd;
#endif

    client->lrByPd(at,pd);
}
///////////////////////////////////////




///////////////////////////////////////
/// \brief DataCenter::setAvatarAsync
/// \param fileId
///
void DataCenter::setAvatarAsync(const QString &fileId)
{
    client->setAvatar(fileId);
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief DataCenter::setUserIdOnce
/// \param userId
///
void DataCenter::setUserIdOnce(const QString &user_id)
{
    if(!userId.isEmpty())
    {
#ifdef DATACENTER_TEST
        LOG() << "userId 已经被初始化了 不能再次进行赋值" ;
#endif
        return;
    }
    userId = user_id;
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief DataCenter::getCodeFromEmail
/// \param email
/// 获取短信 验证码
void DataCenter::getCodeFromEmailAsync(const QString &email)
{
    client->getCodeFromEmail(email);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::getAllVideoListAsync
///
void DataCenter::getAllVideoListAsync()
{
    client->getAllVidelList();
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief DataCenter::getVideoByKindAsync
/// \param kindId
///
void DataCenter::getVideoByKindAsync(int kindId)
{
    client->getVideoByKind(kindId);
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief DataCenter::getVideoByTagAsync
/// \param tagId
///
void DataCenter::getVideoByTagAsync(int tagId)
{
    client->getVideoByTag(tagId);
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief DataCenter::getVideoListForMyselfOrOtherAsync
/// \param userId
/// \param pageIndex
/// 获取视频列表
void DataCenter::getVideoListForMyselfOrOtherAsync(const QString &userId, int pageIndex)
{

#ifdef DATACENTER_TEST
    LOG() << "DataCenter::getVideoListForMyselfOrOtherAsync(const QString &userId, int pageIndex)..."
          << "\nuserId: " << userId
          << "\npageIndex: " << pageIndex;
#endif

    client->getVideoListForMyselfOrOther(userId,pageIndex);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::getAllVideoListSearchTextAsync
/// \param searchText
///
void DataCenter::getAllVideoListSearchTextAsync(const QString &searchText)
{
    client->getAllVideoListSearchText(searchText);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::downloadPhotoAsync
/// \param photeId
///
void DataCenter::downloadPhotoAsync(const QString &photeId)
{
    client->downloadPhoto(photeId);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::getBulletsAsync
/// \param videoId
///
void DataCenter::getBulletsAsync(const QString &videoId)
{
    client->getBullets(videoId);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::isLikeBtnClicked
/// \param videoId
///
void DataCenter::isLikeBtnClickedAsync(const QString &videoId)
{
    client->isLikeBtnClicked(videoId);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::alterAttentionAsync
/// \param user_id
/// 获取 更改 用户对其它用户的关注状态
void DataCenter::alterAttentionAsync(const QString &user_id)
{
    client->alterAttention(user_id);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::addPlayNumberAsync
/// \param videoId
///
void DataCenter::addPlayNumberAsync(const QString &videoId)
{
    client->addPlayNumber(videoId);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::addLikeNumberAsync
/// \param videoId
///
void DataCenter::addLikeNumberAsync(const QString &videoId)
{
    client->addLikeNumber(videoId);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::addAttention
/// \param userId
///
void DataCenter::addAttentionAsync(const QString &userId)
{
#ifdef DATACENTER_TEST
        LOG() << "DataCenter::addAttention(const QString &userId)";
#endif

    client->addAttention(userId);
}
///////////////////////////////////////




///////////////////////////////////////
/// \brief DataCenter::sendBulletAsync
/// \param videoId
/// \param bulletInfo
/// 发送弹幕信息
void DataCenter::sendBulletAsync(const QString &videoId, const BulletInfo &bulletInfo)
{
    client->sendBullet(videoId,bulletInfo);
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief DataCenter::uploadPhotoAsync
/// \param photo
///
void DataCenter::uploadPhotoAsync(const QByteArray &photo)
{
    client->uploadPhoto(photo);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::deleteVideoAsync
/// \param video
///
void DataCenter::deleteVideoAsync(const QString &video_id)
{
    client->deleteVideo(video_id);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::delAttention
/// \param userId
/// 取消关注
void DataCenter::delAttentionAsync(const QString &userId)
{
#ifdef DATACENTER_TEST
    LOG() << "DataCenter::delAttention(const QString &userId)";
#endif
    client->delAttention(userId);
}
///////////////////////////////////////




///////////////////////////////////////
/// \brief DataCenter::getMyselfInfoAsync
///
void DataCenter::getMyselfInfoAsync()
{
#ifdef DATACENTER_TEST
    LOG() << "进入 DataCenter 的 getMyselfInfoAsync 函数...";
    LOG() << "userId: " << userId;
#endif
    client->getUserInfo(userId);
}
///////////////////////////////////////




///////////////////////////////////////
/// \brief DataCenter::getOtherInfoAsync
/// \param user_id
///
void DataCenter::getOtherInfoAsync(const QString &user_id)
{
#ifdef DATACENTER_TEST
    LOG() << "进入getOtherInfoAsync 函数...";
#endif
    if(user_id != userId)
    {
        client->getUserInfo(user_id);
    }
}
///////////////////////////////////////




///////////////////////////////////////
/// \brief DataCenter::setSessionId
/// \param sessionId
///
void DataCenter::setSessionId(const QString &session_id)
{
    sessionId = session_id;
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::getSessionId
/// \return
///
const QString& DataCenter::getSessionId() const
{
    return sessionId;
}
///////////////////////////////////////




//////////////////////////////////////
/// \brief DataCenter::getVideoList
/// \return
/// 这个是 homePage的
VideoList *DataCenter::getVideoList()
{
    if(videoList == nullptr)
    {
        // videoList = new VideoList();
        videoList = std::make_unique<VideoList>();
    }
    return videoList.get();
}
//////////////////////////////////////





//////////////////////////////////////
/// \brief DataCenter::setVideoList
/// \param videoListJsonObject
/// dataCenter 是接口
/// netclient 是实现
void DataCenter::setVideoList(const QJsonObject &videoListJsonObject)
{
    getVideoList();

    if(!isAppend)
    {
#ifdef DATACENTER_TEST
        LOG()<<"不是追加模式 清理中...";
#endif
        videoList->clearVideoList();
    }

    videoList->setVideoTotalCount(videoListJsonObject["totalCount"].toInteger());


    QJsonArray videoListArray = videoListJsonObject["videoList"].toArray();

    // 解析出 视频信息 放到  DataCenter 的 videoList里面
    for(int i = 0 ;i < videoListArray.size() ; i++)
    {
        QJsonObject videoInfoObj = videoListArray[i].toObject();
        VideoInfo videoInfo;
        videoInfo.loadVideoInfoFromJson(videoInfoObj);
        videoList->addVideoInfo(videoInfo);
    }

    videoList->setVideoTotalCount(videoListJsonObject["totalCount"].toInteger());

    if(0 == videoListArray.size())
    {
        videoList->setPageIndex(videoList->getPageIndex()-1);
    }
}
//////////////////////////////////////



//////////////////////////////////////
/// \brief DataCenter::setBulletArray
/// \param bulletArray
///
void DataCenter::setBulletArray(const QJsonArray &bulletArray)
{
    // 解析 出 单个
    bullets.clear();
    if(bulletArray.size() < 1) return;

    QList<BulletInfo> timeBullets;

    QJsonObject bulletObject = bulletArray[0].toObject();
    BulletInfo info;
    info.loadBarrageInfo(bulletObject);
    timeBullets.append(info);
    int64_t time_ = info.playTime;

    for(int i = 1 ;i < bulletArray.size() ; i++)
    {
        QJsonObject bulletObject = bulletArray[i].toObject();
        BulletInfo info;
        info.loadBarrageInfo(bulletObject);

        if(time_ != info.playTime)
        {
            bullets.insert(time_,timeBullets);
            timeBullets.clear();
            time_ = info.playTime;
        }

        timeBullets.append(info);
    }

    if (!timeBullets.isEmpty()) {
        bullets.insert(time_, timeBullets);
    }
}
//////////////////////////////////////



//////////////////////////////////////
/// \brief DataCenter::setMyselfInfo
/// \param myself_json
///
void DataCenter::setMyselfInfo(const QJsonObject &myself_json)
{
    myselfInfo = std::make_unique<UserInfo>();
    otherInfo = std::make_unique<UserInfo>();
    myselfInfo->loadUserInfo(myself_json);
}
//////////////////////////////////////



//////////////////////////////////////
/// \brief DataCenter::setOtherInfo
/// \param other_json
///
void DataCenter::setOtherInfo(const QJsonObject &other_json)
{
    otherInfo = std::make_unique<UserInfo>();
    myselfInfo = std::make_unique<UserInfo>();
    otherInfo->loadUserInfo(other_json);
}
//////////////////////////////////////



//////////////////////////////////////
/// \brief DataCenter::setAvatar
/// \param fileId
///
void DataCenter::setAvatar(const QString &fileId)
{
    myselfInfo->avatarFileId = fileId;
}
//////////////////////////////////////



//////////////////////////////////////
/// \brief DataCenter::setUserVideoList
/// \param videoList
///
void DataCenter::setUserVideoList(const QJsonObject &resultJson)
{
    if(!isOriginUser)
    {
        userVideoList = std::make_unique<VideoList>();
    }
    isOriginUser = true;

    QJsonArray videoListArray = resultJson["videoList"].toArray();

    for(int i = 0; i < videoListArray.size(); i++)
    {
        QJsonObject videoInfoSingle = videoListArray[i].toObject();

        VideoInfo info;

        info.loadVideoInfoFromJson(videoInfoSingle);
        userVideoList->addVideoInfo(info);
    }
    int videoTotalCount = resultJson["totalCount"].toInt();

    userVideoList->setVideoTotalCount(videoTotalCount);
    if(0 == videoListArray.size())
    {
        userVideoList->setPageIndex(userVideoList->getPageIndex()-1);
    }

}
//////////////////////////////////////



//////////////////////////////////////
/// \brief DataCenter::getUserVideoList
/// \return
///
VideoList *DataCenter::getUserVideoList()
{
    return userVideoList.get();
}
//////////////////////////////////////




//////////////////////////////////////
/// \brief DataCenter::getBullets
/// \return
///
const QHash<int64_t, QList<BulletInfo>> &DataCenter::getBullets()
{
    return bullets;
}
//////////////////////////////////////



//////////////////////////////////////
/// \brief DataCenter::getUrl
/// \return
///
const QString &DataCenter::getUrl() const
{

    return serverUrl;
}
//////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::getInstance
/// \return
///
// DataCenter *DataCenter::getInstance()
// {
//     if(instance == nullptr)
//     {
//         instance = new DataCenter();
//     }
//     return instance;
// }
DataCenter *DataCenter::getInstance()
{
    static DataCenter instance;
    return &instance;
}



///////////////////////////////////////
/// \brief DataCenter::getMyselfUserInfo
/// \return
///
UserInfo* DataCenter::getMyselfUserInfo() const
{
    return myselfInfo.get();
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::getOtherUserInfo
/// \return
///
UserInfo* DataCenter::getOtherUserInfo() const
{
    return otherInfo.get();
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief DataCenter::getUserId
/// \return
///
const QString& DataCenter::getUserId()
{
    return userId;
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::buildTempUserInfo
/// 构造临时 用户信息
void DataCenter::buildTempUserInfo()
{

    if (myselfInfo != nullptr){
        myselfInfo = std::make_unique<UserInfo>();
    }
    myselfInfo->buildTmpUserInfo();
}
///////////////////////////////////////



}
