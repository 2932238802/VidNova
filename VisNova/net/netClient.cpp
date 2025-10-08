
#include "netClient.h"
#include "dataCenter/dataCenter.h"

net::NetClient::NetClient(model::DataCenter* data_center):
    dataCenter(data_center)
{
    baseUrl = dataCenter->getUrl();
}

void net::NetClient::hello()
{
    QJsonObject reqBody;
    reqBody["msg"] = "hello world!";
    reqBody["requestId"] = makeRequestUuid();
    QNetworkReply *reply = sendHttpRequest("/hello",reqBody);
    connect(reply , &QNetworkReply::finished,this,[=](){
        bool isOk = false;
        QString reason = "";
        QJsonObject replyObj = handHttpResponse(reply,isOk,reason);
        if(!isOk)
        {
            LOG()<<"hello 请求出错 , reason = "<< reason ;
        }
        QJsonObject userData = replyObj["data"].toObject();
        LOG() << userData["msg"].toString();

        emit dataCenter->_helloDone();
    });



}



QString net::NetClient::makeRequestUuid()
{
    // 使用 后面12位
    return 'R' + QUuid::createUuid().toString().slice(24,12);
}


///////////////////////////////////////
/// \brief net::netClient::sendHttpRequest
/// \param request_path
/// \param json_body
/// \return
///
QNetworkReply *net::NetClient::sendHttpRequest(const QString &request_path, QJsonObject &json_body)
{

    QJsonObject reqBody;

    QNetworkRequest httpReq;
    httpReq.setUrl(baseUrl + request_path);
    httpReq.setHeader(QNetworkRequest::ContentTypeHeader,"application/json; charset=utf8");

    //
    QJsonDocument document(json_body);

    // 这里会发出 一个 信号
    QNetworkReply* reply = manage.post(httpReq,document.toJson());

    return reply;
}
///////////////////////////////////////




///////////////////////////////////////
/// \brief net::netClient::handHttpResponse
/// \param reply
/// \param is_ok
/// \param error_msg
/// \return
///
QJsonObject net::NetClient::handHttpResponse(QNetworkReply *reply, bool&is_ok, QString &error_msg)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        is_ok = false;
        LOG()<< "[err]"<<reply->errorString();
        error_msg = reply->errorString();
        return QJsonObject{};
    }
    QByteArray replyBody = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(replyBody);
    if(jsonDoc.isNull())
    {
        LOG()<<"解析json失败...";
        is_ok = false;
        error_msg = "解析json失败...";
        return QJsonObject{};
    }

    //  业务逻辑的判断
    QJsonObject jsonObject = jsonDoc.object();



    if(jsonObject["errorCode"].toInt()!= 0)
    {
        is_ok = false;
        LOG()<<jsonObject["errorMsg"].toString(); // 打印错误信息
        error_msg = jsonObject["errorMsg"].toString();
        return QJsonObject{};
    }

    is_ok = true;
    reply->deleteLater();
    return jsonObject;

}
///////////////////////////////////////





///////////////////////////////////////
/// \brief DataCenter::loginTemplateAccess
/// 临时用户登录 成功
void net::NetClient::loginTemplateAccess()
{
    QJsonObject replyBody ; // 构造请求体
    replyBody["requestId"] = makeRequestUuid();

    // 发送请求
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/auth/login",replyBody);

    connect(httpReply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;

        QJsonObject replyObject = handHttpResponse(httpReply,ok,reason);

        if(!ok)
        {
            LOG()<<"请求出错了...";
            return;
        }

        QJsonObject resultObject = replyObject["result"].toObject();
        dataCenter->setSessionId(replyObject["sessionId"].toString());

        LOG()<<"[inf] resultObject"<<resultObject;
        LOG()<<"[inf] 临时用户登录成功 requestId: " << replyObject["requestId"].toString();

        emit dataCenter->_loginSucDone(); // 发送登录 成功信号/
    });
}
///////////////////////////////////////

///////////////////////////////////////
/// \brief net::NetClient::getAllVidelList
///
void net::NetClient::getAllVidelList()
{
    QJsonObject replyBody ; // 构造请求体
    auto videoList = dataCenter->getVideoList();
    int curPageIndex = videoList->getPageIndex();

    replyBody["requestId"] = makeRequestUuid();
    replyBody["sessionId"] = dataCenter->getSessionId();

    replyBody["pageCount"] =  model::VideoList::PAGE_COUNT;;
    replyBody["pageIndex"] = curPageIndex; // 每次请求 20 个

    videoList->setPageIndex(curPageIndex+1);

    // 发送请求
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/data/get_all_video",replyBody);

    connect(httpReply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;

        QJsonObject replyObject = handHttpResponse(httpReply,ok,reason);

        if(!ok)
        {
            LOG()<<"请求出错了...";
            return;
        }

        // resultObject 是服务器的 新
        QJsonObject resultObject = replyObject["result"].toObject();


        dataCenter->setVideoList(resultObject);


        LOG()<<"[inf] 用户id" << replyObject["requestId"].toString();

        emit dataCenter->_getAllVideoListDone(); // 发送登录 成功信号/
    });
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief net::NetClient::getVideoByKind
///
void net::NetClient::getVideoByKind(int kind_id)
{

#ifdef NETCLIENT_TEST
    LOG()<<"进入 getVideoByKind函数 ..." << "kind_id 是" << kind_id;
#endif


    QJsonObject replyBody ; // 构造请求体
    auto videoList = dataCenter->getVideoList();
    int curPageIndex = videoList->getPageIndex();
    replyBody["requestId"] = makeRequestUuid();
    replyBody["sessionId"] = dataCenter->getSessionId(); //登录之后 获得的
    replyBody["pageCount"] = model::VideoList::PAGE_COUNT; // 每次请求 20 个
    replyBody["pageIndex"] = curPageIndex;
    replyBody["videoTypeId"] = kind_id;

    // 为了下次能够获取下一页
    videoList->setPageIndex(curPageIndex+1);


    // 发送请求
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/data/get_video_by_kind",replyBody);

    connect(httpReply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;

        QJsonObject replyObject = handHttpResponse(httpReply,ok,reason);

        if(!ok)
        {
            LOG()<<"请求出错了...";
            return;
        }

        // resultObject 是服务器的 新
        QJsonObject resultObject = replyObject["result"].toObject();

        dataCenter->setVideoList(resultObject);

        LOG()<<"[inf] 用户id" << replyObject["requestId"].toString();

        emit dataCenter->_getVideoByKindDone(); // 发送登录 成功信号/
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::getVideoByTag
/// \param tagId
///
void net::NetClient::getVideoByTag(int tagId)
{

#ifdef NETCLIENT_TEST
    LOG()<<"进入 getVideoByTag函数 ..." << "kind_id 是" << tagId;
#endif


    QJsonObject replyBody ; // 构造请求体
    auto videoList = dataCenter->getVideoList();
    int curPageIndex = videoList->getPageIndex();
    replyBody["requestId"] = makeRequestUuid();
    replyBody["sessionId"] = dataCenter->getSessionId(); //登录之后 获得的
    replyBody["pageCount"] = model::VideoList::PAGE_COUNT; // 每次请求 20 个
    replyBody["pageIndex"] = curPageIndex;
    replyBody["videoTagId"] = tagId;

    // 为了下次能够获取下一页
    videoList->setPageIndex(curPageIndex+1);


    // 发送请求
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/data/get_video_by_tag",replyBody);

    connect(httpReply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;

        // handHttpResponse 会处理这个 ok 到底 不ok
        // 还有就是这个消息
        QJsonObject replyObject = handHttpResponse(httpReply,ok,reason);

        if(!ok)
        {
            LOG()<<"请求出错了..." << reason;
            return;
        }

        // resultObject 是服务器的 新
        QJsonObject resultObject = replyObject["result"].toObject();

        dataCenter->setVideoList(resultObject);

        LOG()<<"[inf] 用户id" << replyObject["requestId"].toString();

        emit dataCenter->_getVideoByTagDone(); // 发送登录 成功信号/
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::getAllVideoListSearchText
/// \param str
/// 通过搜索 找到标签
void net::NetClient::getAllVideoListSearchText(const QString &str)
{

#ifdef NETCLIENT_TEST
    LOG()<<"进入 getVideoByTag函数 ..." << "str 是" << str;
#endif

    QJsonObject replyBody ; // 构造请求体
    auto videoList = dataCenter->getVideoList();
    int curPageIndex = videoList->getPageIndex();
    replyBody["requestId"] = makeRequestUuid();
    replyBody["sessionId"] = dataCenter->getSessionId(); //登录之后 获得的
    replyBody["pageCount"] = model::VideoList::PAGE_COUNT; // 每次请求 20 个
    replyBody["pageIndex"] = curPageIndex;
    replyBody["searchKey"] = str;


    // 为了下次能够获取下一页
    videoList->setPageIndex(curPageIndex+1);


    // 发送请求
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/data/get_video_by_key",replyBody);

    connect(httpReply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;

        // handHttpResponse 会处理这个 ok 到底 不ok
        // 还有就是这个消息
        QJsonObject replyObject = handHttpResponse(httpReply,ok,reason);

        if(!ok)
        {
            LOG()<<"请求出错了..." << reason;
            return;
        }

        // resultObject 是服务器的 新
        QJsonObject resultObject = replyObject["result"].toObject();

        dataCenter->setVideoList(resultObject);

        LOG()<<"[inf] 用户id" << replyObject["requestId"].toString();

        emit dataCenter->_getVideoBySearchTextDone(str); // 发送登录 成功信号/
    });

}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::downloadPhoto
/// \param photeId
///
void net::NetClient::downloadPhoto(const QString &photeId)
{
    // 构造请求
    // 发送请求

    QString queryString;
    queryString+="requestId=";
    queryString+=makeRequestUuid();
    queryString+="&";
    queryString+="sessionId=";
    queryString+=dataCenter->getSessionId();
    queryString+="&";
    queryString+="fileId=";
    queryString+= photeId;

    QNetworkRequest request;
    request.setUrl(QUrl(baseUrl + "/VidNova/data/download_photo?" + queryString));

    // 发送亲求

    QNetworkReply* reply = manage.get(request);


    connect(reply,&QNetworkReply::finished,this,[=](){
        // 判定 http 层面 是不是通过

        if(reply->error() != QNetworkReply::NoError)
        {

#ifdef NETCLIENT_TEST
            LOG()<< "网络层发生错误..." << reply->error();
#endif
            reply->deleteLater();
            return ;
        }



        // 获取 图片数据
        QByteArray imageData = reply->readAll();
        QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();

        if(contentType.startsWith("image"))
        {

            emit dataCenter->_downloadPhotoDone(photeId,imageData);

        }
        else{

#ifdef NETCLIENT_TEST
            LOG() << "error type" << contentType;
#endif

            emit dataCenter->_downloadPhotoDone(photeId,QByteArray{});
        }

        reply->deleteLater();

    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::getBullets
/// \param videoId
///
void net::NetClient::getBullets(const QString &videoId)
{

#ifdef NETCLIENT_TEST
    LOG()<<"进入 getBullets ..." << "str 是" << videoId;
#endif

    QJsonObject replyBody ; // 构造请求体
    auto videoList = dataCenter->getVideoList();
    int curPageIndex = videoList->getPageIndex();
    replyBody["requestId"] = makeRequestUuid();
    replyBody["sessionId"] = dataCenter->getSessionId(); //登录之后 获得的
    replyBody["videoId"] = videoId; // 每次请求 20 个


    // 发送请求
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/data/get_bullets",replyBody);

    connect(httpReply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;

        // handHttpResponse 会处理这个 ok 到底 不ok
        // 还有就是这个消息
        QJsonObject replyObject = handHttpResponse(httpReply,ok,reason);

        if(!ok)
        {
            LOG()<<"请求出错了..." << reason;
            return;
        }

        // resultObject 是服务器的 新
        QJsonObject resultObject = replyObject["result"].toObject();

        dataCenter->setBulletArray(resultObject["bulletList"].toArray());

        LOG()<<"[inf] 用户id" << replyObject["requestId"].toString();

        emit dataCenter->_getBulletsDone(videoId); // 发送登录 成功信号/
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::addPlayNumber
/// \param videoId
///
void net::NetClient::addPlayNumber(const QString &videoId)
{
    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["videoId"] = videoId;
    request["requestId"] = makeRequestUuid();

    QNetworkReply* reply = sendHttpRequest("/VidNova/data/add_play_number",request);

    connect(reply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;
        QJsonObject replyObject = handHttpResponse(reply,ok,reason);
        if(!ok)
        {
            LOG()<<"请求出错了..." << reason;
            return;
        }


    });

}
///////////////////////////////////////


///////////////////////////////////////
/// \brief net::NetClient::isLikeBtnClicked
/// \param videoId
///
void net::NetClient::isLikeBtnClicked(const QString &videoId)
{
    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["videoId"] = videoId;
    request["requestId"] = makeRequestUuid();

    QNetworkReply* reply = sendHttpRequest("/VidNova/data/is_likeBtn_clicked",request);

    connect(reply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;
        QJsonObject replyObject = handHttpResponse(reply,ok,reason);
        if(!ok)
        {
            LOG()<<"请求出错了..." << reason;
            return;
        }

        QJsonObject resultJson = replyObject["result"].toObject();

        emit dataCenter->_isLikeBtnClicked(videoId,resultJson["isLiked"].toBool());
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::addLikeNumber
/// \param videoId
///
void net::NetClient::addLikeNumber(const QString &videoId)
{
    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["videoId"] = videoId;
    request["requestId"] = makeRequestUuid();

    QNetworkReply* reply = sendHttpRequest("/VidNova/data/likeBtn",request);

    connect(reply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;
        QJsonObject replyObject = handHttpResponse(reply,ok,reason);
        if(!ok)
        {
            LOG()<<"请求出错了..." << reason;
            return;
        }
        else{
            LOG() <<"addLikeNumber请求发送成功";
        }
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::sendBullet
/// \param videoId
/// \param bulletInfo
///
void net::NetClient::sendBullet(const QString &videoId, const model::BulletInfo &bulletInfo)
{
    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["videoId"] = videoId;
    request["requestId"] = makeRequestUuid();

    QJsonObject bulletInfoObject;
    bulletInfoObject["content"] = bulletInfo.text;
    bulletInfoObject["sendTime"] = bulletInfo.playTime;

    request["bulletInfo"] = bulletInfoObject;

    QNetworkReply* reply = sendHttpRequest("/VidNova/data/sendBullet",request);

    connect(reply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;
        QJsonObject replyObject = handHttpResponse(reply,ok,reason);
        if(!ok)
        {
            LOG()<<"请求出错了..." << reason;
            return;
        }
        else{
            LOG() <<"sendBullet 请求发送成功";
        }
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::downloadVideo
/// \param videoId
///
// void net::NetClient::downloadVideo(const QString &videoId)
// {
//     // 构造请求
//     // 发送请求
//     QString queryString;
//     queryString+="fileId=";
//     queryString+= videoId;


//     // 发送亲求
//     QNetworkRequest request;
//     request.setUrl(QUrl(baseUrl + "/VidNova/data/download_video?" + queryString));
//     QNetworkReply* reply = manage.get(request);


//     connect(reply,&QNetworkReply::finished,this,[=](){
//         // 判定 http 层面 是不是通过

//         if(reply->error() != QNetworkReply::NoError)
//         {

// #ifdef NETCLIENT_TEST
//             LOG()<< "网络层发生错误..." << reply->error();
// #endif
//             reply->deleteLater();
//             return ;
//         }

//         // 获取 图片数据
//         QByteArray videoData = reply->readAll();
//         QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();
//         QString m3u8FilePath = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
//         m3u8FilePath+="/";
//         m3u8FilePath+=videoId;
//         m3u8FilePath+=".m3u8";

// #ifdef NETCLIENT_TEST
//         LOG() << "m3u8FilePath:" << m3u8FilePath;
// #endif

//         writeByteArrayToFile(m3u8FilePath,videoData);

//         // 发送信号
//         emit dataCenter->_downloadVideoDone(m3u8FilePath,videoId); // 发送成功下载的信号
//         reply->deleteLater();
//     });
// }
///////////////////////////////////////












