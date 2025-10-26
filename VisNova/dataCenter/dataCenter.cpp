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
    myselfInfo = std::make_unique<UserInfo>();
    otherInfo = std::make_unique<UserInfo>();
    adminList = std::make_unique<AdminList>();

    // 初始化的时候 尝试从本地 读取到 sessionId
    // 所以 一开始 其实 就应该是有数据的
    loadDataFile();
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
    saveDataFile();
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
#ifdef DATACENTER_TEST
    LOG() << "DataCenter::tempLoginAsync()";
#endif

    client->loginTemplateAccess();
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief DataCenter::logout
///
void DataCenter::logoutAsync()
{
#ifdef DATACENTER_TEST
    LOG() << "DataCenter::logout()";
#endif

    client->logout();
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::loadTempUserInfo
/// 加载临时用户的信息
void DataCenter::loadTempUserInfo()
{

#ifdef DATACENTER_TEST
    LOG() << "DataCenter::loadTempUserInfo()";
#endif

    QJsonObject obj;

    obj["userId"] = "0";
    obj["photoNumber"] = "0";
    obj["nickName"] = "临时用户";

    QJsonArray arr;
    arr.append(4);

    obj["roleType"] = arr;

    obj["likeCount"] = 0;
    obj["playCount"] = 0;
    obj["fansCount"] = 0;

    obj["userState"] = 0;
    obj["isFollowed"] = 0;

    obj["userMemo"] = "作为临时用户...";
    obj["userCreateTime"] = "";
    obj["avatarFileId"] = "";

    setMyselfInfo(obj);

}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::lrByAuthCodeAsync
/// \param email
/// \param auth_code
///
void DataCenter::lrByAuthCodeAsync(const QString &email, const QString &auth_code,const QString&codeId)
{

#ifdef DATACENTER_TEST
    LOG() << "DataCenter::lrByAuthCodeAsync(const QString &email, const QString &auth_code,const QString&codeId)";

#endif


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
/// \brief DataCenter::loginBySessionAsync
/// session登录
void DataCenter::loginBySessionAsync()
{
    client->loginBySession();
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::putOnVideoAsync
/// \param videoId
///
void DataCenter::putOnVideoAsync(const QString &videoId)
{
    client->putOnVideo(videoId);
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief DataCenter::putDownVideoAsync
/// \param videoId
///
void DataCenter::putDownVideoAsync(const QString &videoId)
{
    client->putDownVideo(videoId);
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
/// \brief DataCenter::serAdminAsync
/// \param adminUserInfo
///
void DataCenter::setAdminAsync(const AdminInfo &adminUserInfo)
{
    client->setAdmin(adminUserInfo);
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
/// \brief DataCenter::setNewpassWord
/// \param password
///
void DataCenter::setNewPasswordAsync(const QString &password)
{
    client->setNewPassword(password);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::setNicknameAsync
/// \param nickName
/// 修改昵称
void DataCenter::setNicknameAsync(const QString &nickName)
{
    client->setNickname(nickName);
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief DataCenter::setAdminState
/// \param userId
/// \param state
///
void DataCenter::setAdminStateAsync(const QString &userId, AdminState state)
{
     client->setAdminState(userId,state);
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
/// \brief DataCenter::getVideoByStateAsync
/// \param videoState
/// \param page_count
///
void DataCenter::getVideoByStateAsync(model::VideoState videoState,int page_index)
{
    client->getVideoByState(videoState,page_index);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::getVideoListForMyselfOrOtherAsync
/// \param userId
/// \param pageIndex
/// 获取视频列表
void DataCenter::getVideoListForMyselfOrOtherAsync(const QString &user_id, int pageIndex,GetVideoPage page)
{

#ifdef DATACENTER_TEST
    LOG() << "DataCenter::getVideoListForMyselfOrOtherAsync(const QString &userId, int pageIndex)..."
          << "\nuserId: " << user_id
          << "\npageIndex: " << pageIndex;
#endif

    client->getVideoListForMyselfOrOther(userId,pageIndex,page);
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
/// \brief DataCenter::addAdminAsync
/// \param userInfo
///
void DataCenter::addAdminAsync(const AdminInfo &userInfo)
{
#ifdef DATACENTER_TEST
    LOG() << " DataCenter::addAdminAsync(const AdminInfo &userInfo) ";
#endif
    client->addAdmin(userInfo);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::checkVideoAsync
/// \param videoId
/// \param result
///
void DataCenter::checkVideoAsync(const QString &videoId, bool result)
{
#ifdef DATACENTER_TEST
    LOG() << "DataCenter::checkVideoAsync(const QString &videoId, bool result)";
#endif

    client->checkVideo(videoId, result);
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
void DataCenter::uploadPhotoAsync(const QByteArray &photo,PhotoUploadPurpose pup)
{
#ifdef DATACENTER_TEST
    LOG() << "DataCenter::uploadPhotoAsync(const QByteArray &photo,PhotoUploadPurpose pup)";
    LOG() <<  "pup" << static_cast<int>(pup);
#endif

    client->uploadPhoto(photo,pup);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::uploadVideoAsync
/// \param video_path
///
void DataCenter::uploadVideoAsync(const QString &video_path)
{
    client->uploadVideo(video_path);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::uploadVideoInfoForUploadAsync
/// \param videoInfoForUpload
///
void DataCenter::uploadVideoInfoForUploadAsync(const model::VideoInfoForUpload &videoInfoForUpload)
{
    client->uploadVideoInfoForUpload(videoInfoForUpload);
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
/// \brief DataCenter::delAdminAsync
/// \param userId
///
void DataCenter::delAdminAsync(const QString &userId)
{
#ifdef DATACENTER_TEST
    LOG() << "DataCenter::delAdminAsync(const QString &userId)";
#endif
    client->delAdmin(userId);
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
/// \brief DataCenter::getAdminInfoByPhoneAsync
/// \param photoNumber
///
void DataCenter::getAdminInfoByEmailAsync(const QString &photoNumber)
{
    client->getAdminInfoByEmail(photoNumber);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::getAdminInfoByStateAsync
/// \param page
/// \param state
///
void DataCenter::getAdminInfoByStateAsync(int page, AdminState state)
{
     client->getAdminInfoByState(page,state);
}
///////////////////////////////////////




///////////////////////////////////////
/// \brief DataCenter::setSessionId
/// \param sessionId
///
void DataCenter::setSessionId(const QString &session_id)
{

    if(session_id != sessionId)
    {
        sessionId = session_id;
        saveDataFile();
    }
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
/// \brief DataCenter::getManageSearchVideoList
/// \return
///
VideoList *DataCenter::getManageSearchVideoList()
{
    if(manageSearchVideoList == nullptr)
    {
        // videoList = new VideoList();
        manageSearchVideoList = std::make_unique<VideoList>();
    }
    return manageSearchVideoList.get();
}
//////////////////////////////////////



//////////////////////////////////////
/// \brief DataCenter::getAdminList
/// \return
/// 获取 管理员的指针
AdminList *DataCenter::getAdminList()
{
#ifdef DATACENTER_TEST
    LOG() << "DataCenter::getAdminList()";
#endif

    if(!adminList)
    {
        adminList = std::make_unique<AdminList>();
    }
    return adminList.get();
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
        VideoInfoForLoad videoInfo;
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
/// \brief DataCenter::setManageSearchVideoList
/// \param videoListJsonObject
/// 设置视频列表
void DataCenter::setManageSearchVideoList(const QJsonObject &videoListJsonObject)
{

#ifdef DATACENTER_TEST
    LOG()<<"DataCenter::setManageSearchVideoList(const QJsonObject &videoListJsonObject)";
#endif

    getManageSearchVideoList();

    if(!isAppend)
    {
#ifdef DATACENTER_TEST
        LOG()<<"不是追加模式 清理中...";
#endif
        manageSearchVideoList->clearVideoList();
    }

    manageSearchVideoList->setVideoTotalCount(videoListJsonObject["totalCount"].toInteger());

    QJsonArray videoListArray = videoListJsonObject["videoList"].toArray();

    // 解析出 视频信息 放到  DataCenter 的 videoList里面
    for(int i = 0 ;i < videoListArray.size() ; i++)
    {
        QJsonObject videoInfoObj = videoListArray[i].toObject();
        VideoInfoForLoad videoInfo;
        videoInfo.loadVideoInfoFromJson(videoInfoObj);
        manageSearchVideoList->addVideoInfo(videoInfo);
    }

    manageSearchVideoList->setVideoTotalCount(videoListJsonObject["totalCount"].toInteger());

    if(0 == videoListArray.size())
    {
        manageSearchVideoList->setPageIndex(videoList->getPageIndex()-1);
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

        VideoInfoForLoad info;

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
/// \brief DataCenter::setAdminList
/// \param adminListJson
/// \param isAdminState
/// 如果 isAdminState 是 false 那么就是 根据手机号 进行获取的
/// 如果 是 true 那么就是 根据 状态进行获取的
void DataCenter::setAdminList(const QJsonObject &resultJson, bool isAdminState)
{
#ifdef DATACENTER_TEST
    LOG() << "设置管理员列表";
#endif


#ifdef DATACENTER_TEST
    LOG() << "先调用 getAdminList() 避免 空指针";
#endif
    getAdminList();


    if(isAdminState)
    {
        // 表示 通过 状态进行 获取
#ifdef DATACENTER_TEST
        LOG() << "通过管理员的状态 进行获取 管理员信息 可以一次性获取多个信息";
#endif
        int64_t totalAdminCount = resultJson["totalCount"].toInteger();

        // 设置总数
        adminList->totalCount = totalAdminCount;

        // 解析出 各个 信息
        QJsonArray adminInfoArray = resultJson["userList"].toArray();
        for(int i = 0 ; i < adminInfoArray.size(); i ++)
        {
            QJsonObject adminInfoJson = adminInfoArray[i].toObject();
            AdminInfo adminInfo;
            adminInfo.LoadFromJson(adminInfoJson); // 从 json 转化
            adminList->addAdmin(adminInfo);
        }
    }
    else
    {
#ifdef DATACENTER_TEST
        LOG() << "通过管理员的手机号码 进行获取 管理员的信息 只能获取 一个";
#endif
        AdminInfo adminInfo;
        QJsonObject adminJson = resultJson["userInfo"].toObject();
        adminInfo.LoadFromJson(adminJson);
        adminList->addAdmin(adminInfo);
        adminList->totalCount = 1; // 一个
    }
}
//////////////////////////////////////



//////////////////////////////////////
/// \brief DataCenter::initDataFile
///
///
void DataCenter::initDataFile()
{

#ifdef DATACENTER_TEST
    LOG() << "DataCenter::initDataFile()";
    LOG() << "初始化文件系统";
#endif


    // 构造出
    QString basePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QString filePath = basePath + "/Vidnova.json"; // 用json 进行处理


#ifdef DATACENTER_TEST
    LOG() << "filePath：" << filePath;
#endif

    // 检测路径是不是存在
    QDir dir;

    if(!dir.exists(basePath))
    {
        dir.mkpath(basePath);
    }

    // 在构建好的路径 创建一下文件

    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
#ifdef DATACENTER_TEST
        LOG() << "以写的方式 失败..." << file.errorString();
#endif
    }

#ifdef DATACENTER_TEST
    LOG() << "打开的文件成功...";
#endif

    QString str{"{\n\n}"};
    file.write(str.toUtf8());
    file.close();

}
//////////////////////////////////////


//////////////////////////////////////
/// \brief DataCenter::savaDataFile
///
void DataCenter::saveDataFile()
{
#ifdef DATACENTER_TEST
    LOG() << "DataCenter::savaDataFile()";
#endif

    // 构造出
    QString basePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QString filePath = basePath + "/Vidnova.json"; // 用json 进行处理

    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        LOG () << "文件打开失败 .." << file.errorString();
        return;
    }

    // 写入数据 以json的方式 进行组织
    QJsonObject json;
    json["sessionId"] = sessionId;
    QJsonArray roleType;
    for(auto& role : myselfInfo->roleType)
    {
        roleType.append(role);
    }

    json["roleType"] = roleType;

    QJsonArray identitys;
    for(auto& identity : myselfInfo->identityType)
    {
        identitys.append(identity);
    }
    json["identity"] = identitys;


    QJsonDocument jsonDoc(json);
    QString jsonStr = jsonDoc.toJson();
    file.write(jsonStr.toUtf8());

    file.close();
}
//////////////////////////////////////



//////////////////////////////////////
/// \brief DataCenter::loadDataFile
///
void DataCenter::loadDataFile()
{
#ifdef DATACENTER_TEST
    LOG() << "DataCenter::loadDataFile()";
#endif

    // 加载sessionid等 数据

    // 判断文件是不是存在
    // 构造出
    QString basePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QString filePath = basePath + "/Vidnova.json"; // 用json 进行处理

    QFileInfo fileInfo(filePath);
    if(!fileInfo.exists())
    {

#ifdef DATACENTER_TEST
        LOG() << "文件不存在 ...";
        LOG() << "所以进入 文件的初始化" << " initDataFile()";
#endif

        initDataFile();
    }

    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
#ifdef DATACENTER_TEST
        LOG() << "文件以只读的方式打开失败... " << file.errorString();
#endif
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    if(jsonDoc.isNull())
    {
#ifdef DATACENTER_TEST

        LOG() << "解析json的时候出错了 JSON格式有误" << file.errorString();
#endif
        return;
    }

    // 从 Json 中将 数据解析出来
    QJsonObject jsonObj = jsonDoc.object();

    // 解析出 sessionid
    sessionId = jsonObj["sessionId"].toString();

#ifdef DATACENTER_TEST
    LOG() << "本地的session以jsonObj读取 " << jsonObj;
#endif

    // 解析
    QJsonArray roleTypeArray = jsonObj["roleType"].toArray();

    if(myselfInfo == nullptr)
    {
#ifdef DATACENTER_TEST
        LOG() << "myselfInfo 是空指针";
#endif
        myselfInfo = std::make_unique<UserInfo>();
    }

    for(int i = 0; i < roleTypeArray.size() ; i++)
    {
        myselfInfo->roleType.append(roleTypeArray[i].toInt());

    }

    QJsonArray identityArray = jsonObj["identityType"].toArray();
    for(int i = 0; i < identityArray.size() ; i++)
    {
        myselfInfo->identityType.append(identityArray[i].toInt());
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
UserInfo* DataCenter::getMyselfInfo() const
{
    return myselfInfo.get();
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief DataCenter::getOtherUserInfo
/// \return
///
UserInfo* DataCenter::getOtherInfo() const
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
/// \brief DataCenter::clear
///
void DataCenter::clear()
{
    sessionId.clear();
    userId.clear();
}
///////////////////////////////////////



}
