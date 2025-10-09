#include "dataCenter.h"

namespace model
{
DataCenter* DataCenter::instance = nullptr;

void DataCenter::setMode(bool is_append)
{
    isAppend = is_append;

    LOG() << "isAppend is "  << is_append;
}

DataCenter::DataCenter(QObject *parent)
    : QObject{parent}, isAppend(false)
{
    client = std::make_unique<net::NetClient>(this);
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
/// \brief DataCenter::setAvatarAsync
/// \param fileId
///
void DataCenter::setAvatarAsync(const QString &fileId)
{
    client->setAvatar(fileId);
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
/// \brief DataCenter::addPlayNumberAsync
/// \param videoId
///
void DataCenter::addPlayNumberAsync(const QString &videoId)
{
    client->addPlayNumber(videoId);
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
void DataCenter::addLikeNumberAsync(const QString &videoId)
{
    client->addLikeNumber(videoId);
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

void DataCenter::uploadPhotoAsync(const QByteArray &photo)
{
    client->uploadPhoto(photo);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::getMyselfInfoAsync
///
void DataCenter::getMyselfInfoAsync()
{
    client->getUserInfo("");
}
///////////////////////////////////////




///////////////////////////////////////
/// \brief DataCenter::getOtherInfoAsync
/// \param user_id
///
void DataCenter::getOtherInfoAsync(const QString &user_id)
{
    client->getUserInfo(user_id);
}
///////////////////////////////////////








///////////////////////////////////////
/// \brief DataCenter::downloadVideoAsync
/// \param videoId
///
// void DataCenter::downloadVideoAsync(const QString &videoId)
// {
//    client.downloadVideo(videoId);
// }
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
///
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
        LOG()<<"不是追加模式 情理中...";
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
    if(myselfInfo == nullptr)
    {
        myselfInfo = std::make_shared<UserInfo>();
    }

    myselfInfo->loadUserInfo(myself_json);
}
//////////////////////////////////////



//////////////////////////////////////
/// \brief DataCenter::setOtherInfo
/// \param other_json
///
void DataCenter::setOtherInfo(const QJsonObject &other_json)
{
    if(otherInfo == nullptr)
    {
        otherInfo = std::make_shared<UserInfo>();
    }

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
std::shared_ptr<UserInfo> DataCenter::getMyselfUserInfo() const
{
    return myselfInfo;
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::getOtherUserInfo
/// \return
///
std::shared_ptr<UserInfo> DataCenter::getOtherUserInfo() const
{
    return otherInfo;
}
///////////////////////////////////////



}
