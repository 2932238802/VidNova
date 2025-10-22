#include "httpServer.h"

HttpServer* HttpServer::instance = nullptr;

////////////////////////////////////
/// \brief HttpServer::HttpServer
/// \param parent
///
HttpServer::HttpServer(QObject *parent)
    : QObject{parent}
{
    httpServer = std::make_unique<QHttpServer>();
    tcpServer = std::make_unique<QTcpServer>();
    buildResponseData();
}
////////////////////////////////////


QHttpServerResponse HttpServer::helloService(const QHttpServerRequest &request)
{
    // 获取 到 请求中数据
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());

    const QJsonObject& jsonObject = docReq.object();

    LOG()<<"收到请求"<<jsonObject["requestId"];

    QJsonObject jsonBody;
    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonObject dataObject;
    dataObject["msg"] = "hello world ~ ";

    jsonBody["data"] = dataObject;

    QJsonDocument docRes;
    docRes.setObject(jsonBody);

    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}

// ////////////////////////////////////
// /// \brief HttpServer::tempLoginService
// /// \param request
// /// \return
// ///
// QHttpServerResponse HttpServer::tempLoginService(const QHttpServerRequest &request)
// {
//     // 获取 到 请求中数据
//     QJsonDocument docReq = QJsonDocument::fromJson(request.body());

//     const QJsonObject& jsonObject = docReq.object();

//     LOG()<<"收到请求"<<jsonObject["requestId"];

//     QJsonObject jsonBody;
//     jsonBody["requestId"] = jsonObject["requestId"].toString();
//     jsonBody["errorCode"] = 0;
//     jsonBody["errorMsg"] = "";

//     QJsonObject dataObject;
//     QString sessionId = QUuid::createUuid().toString();
//     sessionId = sessionId.mid(25,12);

//     dataObject["sessionId"] = sessionId;

//     jsonBody["result"] = dataObject;

//     QJsonDocument docRes;
//     docRes.setObject(jsonBody);

//     QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);

//     LOG()<<"docRes.toJson()"<<docRes.toJson();

//     QHttpHeaders headers;
//     headers.append("Content-Type", "application/json; charset=utf-8");
//     httpRes.setHeaders(headers);
//     return httpRes;
// }
// ////////////////////////////////////


////////////////////////////////////
/// \brief HttpServer::lrByAuthCode
/// \param request
/// \return
///
QHttpServerResponse HttpServer::lrByAuthCode(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());

    const QJsonObject& jsonObject = docReq.object();

    LOG()<<"收到请求"<<jsonObject["requestId"];

    QJsonObject jsonBody;
    jsonBody["requestId"] = jsonObject["requestId"].toString();

    jsonBody["errorCode"] = 0;

    jsonBody["errorMsg"] = "";

    QString email = jsonBody["email"].toString();

    QString code = jsonBody["authCode"].toString();

    QString codeId = jsonBody["codeId"].toString();

#ifdef HTTPSERVER_TEST
    LOG() << "HttpServer::lrByAuthCode(const QHttpServerRequest &request)";
    LOG() << "email: " << email;
    LOG() << "authCode: " << email;
    LOG() << "codeId: " << email;
#endif

    QJsonDocument docRes;

    docRes.setObject(jsonBody);

    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);

    QHttpHeaders headers;

    headers.append("Content-Type", "application/json; charset=utf-8");

    httpRes.setHeaders(headers);

    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::lrByPd
/// \param request
/// \return
///
QHttpServerResponse HttpServer::lrByPd(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());

    const QJsonObject& jsonObject = docReq.object();

    QJsonObject jsonBodyForReply;

    jsonBodyForReply["requestId"] = jsonObject["requestId"].toString();

    QString pd = jsonObject["password"].toString();

    QString at = jsonObject["account"].toString();

    QString sessionId = QUuid::createUuid().toString();

#ifdef HTTPSERVER_TEST
    LOG() << "HttpServer::lrByPd(const QHttpServerRequest &request)";
    LOG() << "pd: " << pd;
    LOG() << "at: " << at;
#endif

    QJsonDocument docRes;

    if(pd == "!Lsj20041021" && at == "19857198709")
    {
        jsonBodyForReply["userId"] = "123";

        jsonBodyForReply["errorCode"] = 0;

        jsonBodyForReply["errorMsg"] = "";

        jsonBodyForReply["sessionId"] = sessionId;

        m_sessions.insert(sessionId,"123");
    }
    else
    {
        // TODO 修改一下
        jsonBodyForReply["errorCode"] = 700;

        jsonBodyForReply["errorMsg"] = "密码账号错误(测试)";
    }

    docRes.setObject(jsonBodyForReply);

    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);

    QHttpHeaders headers;

    headers.append("Content-Type", "application/json; charset=utf-8");

    httpRes.setHeaders(headers);

    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::loginBySession
/// \param request
/// \return
/// 通过sessionId 登录
QHttpServerResponse HttpServer::loginBySession(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());

    const QJsonObject& jsonObject = docReq.object();

    QJsonObject jsonBodyForReply;

    jsonBodyForReply["requestId"] = jsonObject["requestId"].toString();

    QString sessionId = jsonObject["sessionId"].toString();

#ifdef HTTPSERVER_TEST
    LOG () << "sessionId" <<  sessionId;
#endif

    QJsonDocument docRes;

    if(m_sessions.contains(sessionId))
    {

        jsonBodyForReply["errorCode"] = 0;
        jsonBodyForReply["errorMsg"] = "";
        QJsonObject rlt;

        rlt["isTemp"] = false ;
        rlt["userId"] = m_sessions.value(sessionId);
        jsonBodyForReply["result"] = rlt;

    }else{
        jsonBodyForReply["errorCode"] = 6001;
        jsonBodyForReply["errorMsg"] = "session登录失败 重新登录";
    }

    docRes.setObject(jsonBodyForReply);

    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);

    QHttpHeaders headers;

    headers.append("Content-Type", "application/json; charset=utf-8");

    httpRes.setHeaders(headers);

    return httpRes;
}
////////////////////////////////////




////////////////////////////////////
/// \brief HttpServer::logout
/// \param request
/// \return
/// 退出登录的亲求
QHttpServerResponse HttpServer::logout(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());

    const QJsonObject& jsonObject = docReq.object();

    QJsonObject jsonBodyForReply;

    jsonBodyForReply["requestId"] = jsonObject["requestId"].toString();

    QString sessionId = jsonObject["sessionId"].toString();

#ifdef HTTPSERVER_TEST
    LOG () << "sessionId" <<  sessionId;
#endif

    QJsonDocument docRes;

    jsonBodyForReply["requestId"] = jsonObject["requestId"].toString();
    jsonBodyForReply["errorCode"] = 0;
    jsonBodyForReply["errorMsg"] = "";

    QJsonObject result;

    result["sessionId"] = sessionId ; // TODO
    jsonBodyForReply["result"] = result;


    docRes.setObject(jsonBodyForReply);

    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::allVideoList
/// \param request
/// \return
///
QHttpServerResponse HttpServer::allVideoList(const QHttpServerRequest &request)
{
    // 获取 到 请求中数据

    QJsonDocument docReq = QJsonDocument::fromJson(request.body());

    const QJsonObject& jsonObject = docReq.object();

    LOG()<<"收到请求"<<jsonObject["requestId"].toString();

    QJsonObject jsonBody; // 总的

    jsonBody["requestId"] = jsonObject["requestId"].toString();

    jsonBody["errorCode"] = 0;

    jsonBody["errorMsg"] = "";

    // JsonBody 部分
    QJsonObject resultObject;

    resultObject["totalCount"] = 100;

#ifdef TEST_VIDEOLIST

    int videoId = 10000;

    int userId = 10000;

    int resourceId = 10000;

    QJsonArray videoLists;

    for(int i = 0; i < pageCount ;i ++)
    {
        QJsonObject videoJsonObject;

        videoJsonObject["videoId"] = QString::number(videoId++);

        videoJsonObject["userId"] = QString::number(userId++);

        videoJsonObject["photoId"] = QString::number(resourceId++); // 视频封面

        videoJsonObject["userAvatarId"] = QString::number(resourceId++);

        videoJsonObject["videoFileId"] = QString::number(resourceId++);

        videoJsonObject["nickname"] = "用户昵称";

        videoJsonObject["likeCount"] = 645;

        videoJsonObject["playCount"] = 645;

        videoJsonObject["videoSize"] = 654645;

        videoJsonObject["nickname"] = "用户昵称";

        videoJsonObject["videoDesc"] = "qwertyuiopasdfghjklzxcvbnm";

        videoJsonObject["videoTitle"] = "qwertyuiop";

        videoJsonObject["videoDuration"] = 10;

        videoJsonObject["loadupTime"] = "9-16 12:28:58";

        videoLists.append(videoJsonObject);
    }

#endif
    resultObject["videoList"] = videoLists;

    jsonBody["result"] = resultObject;

    QJsonDocument docRes;
    docRes.setObject(jsonBody);

    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);

    QHttpHeaders headers;

    headers.append("Content-Type", "application/json; charset=utf-8");

    httpRes.setHeaders(headers);

    return httpRes;
}
////////////////////////////////////




////////////////////////////////////
/// \brief HttpServer::videoByKind
/// \param request
/// \return
///
QHttpServerResponse HttpServer::videoByKind(const QHttpServerRequest &request)
{
    // 获取 到 请求中数据
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());

    const QJsonObject& jsonObject = docReq.object();

    LOG()<<"videoByKind 收到请求"<<jsonObject["requestId"];

    QJsonObject jsonBody; // 总的

    jsonBody["requestId"] = jsonObject["requestId"].toString();

    jsonBody["errorCode"] = 0;

    jsonBody["errorMsg"] = "";

    // JsonBody 部分
    QJsonObject resultObject;

    resultObject["totalCount"] = 100; // 区分一下

#ifdef TEST_VIDEOLIST
    int videoId = 20000;

    int userId = 20000;

    int resourceId = 20000;

    QJsonArray videoLists;

    for(int i = 0; i < pageCount ;i ++)
    {
        QJsonObject videoJsonObject;
        videoJsonObject["videoId"] = QString::number(videoId++);
        videoJsonObject["userId"] = QString::number(userId++);

        videoJsonObject["photoId"] = QString::number(resourceId++); // 视频封面
        videoJsonObject["userAvatarId"] = QString::number(resourceId++);
        videoJsonObject["videoFileId"] = QString::number(resourceId++);

        videoJsonObject["nickname"] = "用户昵称";


        videoJsonObject["likeCount"] = 534;
        videoJsonObject["playCount"] = 5345;
        videoJsonObject["videoSize"] = 5435;
        videoJsonObject["nickname"] = "用户昵称";
        videoJsonObject["videoDesc"] = "qwertyuiopasdfghjklzxcvbnm";
        videoJsonObject["videoTitle"] = "qwertyuiop";
        videoJsonObject["videoDuration"] = 10;

        videoJsonObject["loadupTime"] = "9-16 12:28:58";

        videoLists.append(videoJsonObject);
    }
#endif

    resultObject["videoList"] = videoLists;
    jsonBody["result"] = resultObject;


    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);

    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;

}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::videoByTag
/// \param request
/// \return
///
QHttpServerResponse HttpServer::videoByTag(const QHttpServerRequest &request)
{
    // 获取 到 请求中数据
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());

    const QJsonObject& jsonObject = docReq.object();

    LOG()<<"videoByTag 收到请求"<<jsonObject["requestId"].toString();

    QJsonObject jsonBody; // 总的
    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";


    // JsonBody 部分
    QJsonObject resultObject;


    resultObject["totalCount"] = 40; // 区分一下


#ifdef TEST_VIDEOLIST

    LOG()<<"服务端 接收到了 videoByTag 请求...";

    int videoId = 30000;
    int userId = 30000;
    int resourceId = 30000;

    QJsonArray videoLists;
    for(int i = 0; i < pageCount ;i ++)
    {
        QJsonObject videoJsonObject;
        videoJsonObject["videoId"] = QString::number(videoId++);
        videoJsonObject["userId"] = QString::number(userId++);
        videoJsonObject["photoId"] = QString::number(resourceId++); // 视频封面
        videoJsonObject["userAvatarId"] = QString::number(resourceId++);
        videoJsonObject["videoFileId"] = QString::number(resourceId++);
        videoJsonObject["nickname"] = "用户昵称";


        videoJsonObject["likeCount"] = 4234;
        videoJsonObject["playCount"] = 4234;
        videoJsonObject["videoSize"] = 23423;
        videoJsonObject["nickname"] = "用户昵称";
        videoJsonObject["videoDesc"] = "qwertyuiopasdfghjklzxcvbnm";
        videoJsonObject["videoTitle"] = "qwertyuiop";
        videoJsonObject["videoDuration"] = 10;

        videoJsonObject["loadupTime"] = "9-16 12:28:58";

        videoLists.append(videoJsonObject);
    }
#endif

    resultObject["videoList"] = videoLists;
    jsonBody["result"] = resultObject;

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    // LOG()<<"docRes.toJson()"<<docRes.toJson();

    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////


////////////////////////////////////
/// \brief HttpServer::videoByKey
/// \param request
/// \return
///
QHttpServerResponse HttpServer::videoByKey(const QHttpServerRequest &request)
{
    // 获取 到 请求中数据
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());

    const QJsonObject& jsonObject = docReq.object();

    LOG()<<"videoByTag 收到请求"<<jsonObject["requestId"];

    QJsonObject jsonBody; // 总的
    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";


    // JsonBody 部分
    QJsonObject resultObject;


    resultObject["totalCount"] = 100; // 区分一下


#ifdef TEST_VIDEOLIST

    LOG()<<"服务端 接收到了 videoByKey 请求...";

    int videoId = 40000;
    int userId = 40000;
    int resourceId = 40000;

    QJsonArray videoLists;

    for(int i = 0; i < pageCount ;i ++)
    {
        QJsonObject videoJsonObject;
        videoJsonObject["videoId"] = QString::number(videoId++);
        videoJsonObject["userId"] = QString::number(userId++);
        videoJsonObject["photoId"] = QString::number(resourceId++); // 视频封面
        videoJsonObject["userAvatarId"] = QString::number(resourceId++);
        videoJsonObject["videoFileId"] = QString::number(resourceId++);
        videoJsonObject["nickname"] = "用户昵称";

        // 视频封面
        videoJsonObject["likeCount"] = 31231;
        videoJsonObject["playCount"] = 31231;
        videoJsonObject["videoSize"] = 312;
        videoJsonObject["nickname"] = "用户昵称";
        videoJsonObject["videoDesc"] = "qwertyuiopasdfghjklzxcvbnm";
        videoJsonObject["videoTitle"] = "qwertyuiop";
        videoJsonObject["videoDuration"] = 10;

        videoJsonObject["loadupTime"] = "9-16 12:28:58";

        videoLists.append(videoJsonObject);
    }
#endif

    resultObject["videoList"] = videoLists;
    jsonBody["result"] = resultObject;

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    LOG()<<"docRes.toJson()"<<docRes.toJson();
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;

}
////////////////////////////////////


////////////////////////////////////
/// \brief HttpServer::getUserVideoInfo
/// \param request
/// \return
///
QHttpServerResponse HttpServer::getUserVideoInfo(const QHttpServerRequest &request)
{
    // 获取 到 请求中数据
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());

#ifdef TEST_VIDEOLIST
    LOG() << "QHttpServerResponse HttpServer::getUserVideoInfo(const QHttpServerRequest &request)";
    LOG() << "docReq" << docReq;
#endif

    const QJsonObject& jsonObject = docReq.object();
    LOG()<<"getUserVideoInfo 收到请求"<<jsonObject["requestId"].toString();

    QJsonObject jsonBody; // 总的
    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    // JsonBody 部分
    QJsonObject resultObject;

    resultObject["totalCount"] = 100; // 区分一下

#ifdef TEST_VIDEOLIST
    int videoId = 10000;
    int userId = 20000;
    int resourceId = 50000;
    QJsonArray videoLists;

    for(int i = 0; i < pageCount ;i ++)
    {
        QJsonObject videoJsonObject;
        videoJsonObject["videoId"] = QString::number(videoId++);
        videoJsonObject["userId"] = QString::number(userId++);

        videoJsonObject["photoId"] = QString::number(resourceId++); // 视频封面
        videoJsonObject["userAvatarId"] = QString::number(resourceId++);
        videoJsonObject["videoFileId"] = QString::number(resourceId++);

        videoJsonObject["nickname"] = "用户昵称";

        videoJsonObject["likeCount"] = 534;
        videoJsonObject["playCount"] = 5345;
        videoJsonObject["videoSize"] = 5435;
        videoJsonObject["nickname"] = "用户昵称";
        videoJsonObject["videoDesc"] = "qwertyuiopasdfghjklzxcvbnm";
        videoJsonObject["videoTitle"] = "qwertyuiop";
        videoJsonObject["videoDuration"] = 10;

        videoJsonObject["loadupTime"] = "9-16 12:28:58";

        videoJsonObject["checkerId"] = "1234";
        videoJsonObject["checkerName"] = "张三";
        videoJsonObject["checkerAvatar"] = "50000";
        videoJsonObject["videoStatus"] = 2;

        videoLists.append(videoJsonObject);
    }
#endif
    resultObject["videoList"] = videoLists;
    jsonBody["result"] = resultObject;

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);

#ifdef HTTPSERVER_TEST
    LOG() << "getUserVideoInfo 答复内容为" << docRes.toJson();
#endif

    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////




////////////////////////////////////
/// \brief HttpServer::downloadPhoto
/// \param request
/// \return
///
QHttpServerResponse HttpServer::downloadPhoto(const QHttpServerRequest &request)
{
    // 从 Url 解析出
    QUrlQuery query(request.url());
    QString requestId =  query.queryItemValue("requestId");
    QString fileId = query.queryItemValue("fileId");


    QDir dir(QDir::current());
    dir.cdUp();
    dir.cdUp();
    QString imagePath = dir.absolutePath();
    imagePath += idPathMap[fileId];


    // 读取图片数据
    QByteArray data = loadFileToByteArray(imagePath);

    QMimeDatabase db;
    QMimeType mimeType = db.mimeTypeForFile(imagePath);
    QString contentType = mimeType.name();

    // 构造请求 并返回
    QHttpServerResponse response(data,QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type",contentType);
    response.setHeaders(headers);
    return response;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::downloadVideoM3u8File
/// \param request
/// \return
///
QHttpServerResponse HttpServer::downloadVideoM3u8File(const QHttpServerRequest &request)
{
    // 从 Url 解析出
    QUrlQuery query(request.url());
    QString fileId = query.queryItemValue("fileId");

    // 构造视频的地址
    QDir dir(QDir::current());
    dir.cdUp();
    dir.cdUp();
    QString videoPath = dir.absolutePath();
    videoPath += idPathMap[fileId];

#ifdef HTTPSERVER_TEST
    LOG() << "fileId: " << fileId;
    LOG() << "videoPath :" << videoPath;
#endif

    // 读取图片数据
    QByteArray data = loadFileToByteArray(videoPath);

    QMimeDatabase db;
    QMimeType mimeType = db.mimeTypeForFile(videoPath);
    QString contentType = mimeType.name();

    // 构造请求 并返回
    QHttpServerResponse response(data,QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type",contentType);
    response.setHeaders(headers);
    return response;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::downloadVideoSegmentation
/// \param request
/// \return
///
QHttpServerResponse HttpServer::downloadVideoSegmentation(const QString& file_name)
{
    QDir dir(QDir::current());
    dir.cdUp();
    dir.cdUp();
    QString videoSegmentationPath = dir.absolutePath();

    videoSegmentationPath += "/video/";
    videoSegmentationPath += file_name;


    QByteArray videoData  = loadFileToByteArray(videoSegmentationPath);

    QMimeDatabase db;
    QMimeType mimeType = db.mimeTypeForFile(videoSegmentationPath);
    QString contentType = mimeType.name();

    QHttpServerResponse response(videoData,QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type",contentType);
    response.setHeaders(headers);
    return response;
}
////////////////////////////////////


////////////////////////////////////
/// \brief HttpServer::getBullets
/// \param request
/// \return
///
QHttpServerResponse HttpServer::getBullets(const QHttpServerRequest &request)
{
    // 获取 到 请求中数据
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());

    const QJsonObject& jsonObject = docReq.object();

    LOG()<<"getBullets 收到请求"<<jsonObject["requestId"];

    QJsonObject jsonBody; // 总的 jsonBody 回复体
    QString videoId = jsonObject["videoId"].toString();

    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonArray bulletArray;

    for(int i = 0; i < Rand::RandNumber(5,10) ; i ++ )
    {
        QList<BulletInfo> tempList; // 用来存放 特定时间的 弹幕组
        int playTime = Rand::RandNumber(1,45);

        for(int j = 0; j < Rand::RandNumber(3,10);j++)
        {
            // BulletInfo info{"10001",playTime,Rand::RandChars(5)};
            // tempList.append(info);
            QJsonObject bulletSingle;
            bulletSingle["userId"] = "10001";
            bulletSingle["bulletId"] = "50000" + QString::number(j);
            bulletSingle["playTime"] = playTime;
            bulletSingle["text"] = Rand::RandChars(5);
            bulletArray.append(bulletSingle);
        }
    }

    QJsonObject bulletList;
    bulletList["bulletList"] = bulletArray;
    jsonBody["result"] = bulletList;

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::addPlayNumber
/// \param request
/// \return
///
QHttpServerResponse HttpServer::addPlayNumber(const QHttpServerRequest &request)
{
    // 获取 到 请求中数据
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonObject = docReq.object();
    LOG()<<"addPlayNumber 收到请求"<<jsonObject["requestId"];

    QJsonObject jsonBody; // 总的 jsonBody 回复体
    QString videoId = jsonObject["videoId"].toString();

    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::isLikeBtnClicked
/// \param request
/// \return
///
QHttpServerResponse HttpServer::isLikeBtnClicked(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonObject = docReq.object();

    QJsonObject jsonBody; // 总的 jsonBody 回复体
    QString videoId = jsonObject["videoId"].toString();

    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonObject rst;
    rst["isLiked"] = true;
    jsonBody["result"] = rst;

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::alterAttention
/// \param request
/// \return
/// 更新用户关注 状态
QHttpServerResponse HttpServer::alterAttention(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonObject = docReq.object();

#ifdef HTTPSERVER_TEST
    LOG() << "HttpServer::alterAttention(const QHttpServerRequest &request)";
    LOG() << "更新用户 关注状态";
#endif

    // 总的 jsonBody 回复体
    QJsonObject jsonBody;
    QString videoId = jsonObject["videoId"].toString();

    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::addLikeNumber
/// \param request
/// \return
/// 点赞按钮 点击 服务器的处理
QHttpServerResponse HttpServer::addLikeNumber(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonObject = docReq.object();
    LOG()<<"addLikeNumber 收到请求"<<jsonObject["requestId"];

    QJsonObject jsonBody;
    QString videoId = jsonObject["videoId"].toString();

    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}

QHttpServerResponse HttpServer::addAttention(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonObject = docReq.object();

#ifdef HTTPSERVER_TEST
    LOG()<<"addAttention 收到请求";
    LOG()<<"requestId 是: "<<jsonObject["requestId"].toString();
    LOG()<<"userId是" << jsonObject["userId"].toString();
#endif

    QJsonObject jsonBody;
    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);

    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::newBullet
/// \param request
/// \return
///
QHttpServerResponse HttpServer::newBullet(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonObject = docReq.object();

#ifdef HTTPSERVER_TEST
    LOG()<<"newBullet 收到请求"<<jsonObject["requestId"];
#endif

    QJsonObject jsonBody; // 总的 jsonBody 回复体
    QString videoId = jsonObject["videoId"].toString();

    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::newVideo
/// \param request
/// \return
/// 上传 创造视频
QHttpServerResponse HttpServer::newVideo(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonObject = docReq.object();

#ifdef HTTPSERVER_TEST
    LOG()<<"HttpServer::newVideo(const QHttpServerRequest &request)";
#endif

    // 总的 jsonBody 回复体
    QJsonObject jsonBody;

    QJsonObject videoInfo = jsonObject["videoInfo"].toObject();
    QString videoFileId = jsonObject["videoId"].toString();
    QString videoTitleId = jsonObject["videoTitleId"].toString();
    QString photoFileId = jsonObject["photoFileId"].toString();
    int videoType = jsonObject["videoType"].toInt();
    QString videoDesc = jsonObject["videoDesc"].toString();
    int64_t duration = jsonObject["duration"].toInt();

#ifdef HTTPSERVER_TEST
    LOG() << "videoInfo: " << videoInfo;
    LOG() << "videoFileId: " << videoFileId;
    LOG() << "photoFileId: " << photoFileId;
    LOG() << "photoFileId: " << photoFileId;
    LOG() << "videoType: " << videoType;
    LOG() << "videoDesc: " << videoDesc;
    LOG() << "duration: " << duration;
#endif

    QJsonArray tagsArray = jsonObject["videoTags"].toArray();
    for(int i =0 ;i < tagsArray.size() ;i++)
    {
        int tagId = tagsArray[i].toInt();
        LOG() << "tagId" << i << " = " << tagId;
    }

    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::getUserInfo
/// \param request
/// \return
///
QHttpServerResponse HttpServer::getUserInfo(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonObject = docReq.object();
    const QString userId = jsonObject["userId"].toString();

#ifdef HTTPSERVER_TEST
    LOG()<<"getUserInfo 收到请求"<<jsonObject["requestId"].toString()
          << "userId" << userId;
#endif

    QJsonObject jsonBody;
    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    // 构造用户信息
    QJsonObject userInfoJson;
    if(userId.isEmpty())
    {
        userInfoJson["userId"] = "2932238802";
        userInfoJson["photoNumber"] = "12312345678";
        userInfoJson["nickName"] = "LosAngelous";
        QJsonArray userType;
        userType.append(3);
        userInfoJson["roleType"] = userType;

        QJsonArray identityType;
        identityType.append(1);
        userInfoJson["identityType"] = identityType;

        userInfoJson["likeCount"] = 30002;

        userInfoJson["playCount"] = 1232131;

        userInfoJson["fansCount"] = 13123;

        userInfoJson["followCount"] = 30002;

        userInfoJson["userState"] = 0;
        userInfoJson["isFollowed"] = 0;
        userInfoJson["userMemo"] = "mei you beizhu xinxi";
        userInfoJson["userCreateTime"] = "";
        userInfoJson["avatarFileId"] = "10001";
    }
    else if(userId == "123"){
        userInfoJson["userId"] = "123";
        userInfoJson["photoNumber"] = "19857198709";
        userInfoJson["nickName"] = "lsj";
        QJsonArray userType;
        userType.append(3);
        userInfoJson["roleType"] = userType;

        QJsonArray identityType;
        identityType.append(1);
        userInfoJson["identityType"] = identityType;

        userInfoJson["likeCount"] = 3123;

        userInfoJson["playCount"] = 543;

        userInfoJson["fansCount"] = 675;

        userInfoJson["followCount"] = 32;

        userInfoJson["userState"] = 0;
        userInfoJson["isFollowed"] = 0;
        userInfoJson["userMemo"] = "其它用户";
        userInfoJson["userCreateTime"] = "";
        userInfoJson["avatarFileId"] = "20001";
    }else{
        userInfoJson["userId"] = "111";
        userInfoJson["photoNumber"] = "1111";
        userInfoJson["nickName"] = "11111";
        QJsonArray userType;
        userType.append(3);
        userInfoJson["roleType"] = userType;

        QJsonArray identityType;
        identityType.append(1);
        userInfoJson["identityType"] = identityType;

        userInfoJson["likeCount"] = 99999;

        userInfoJson["playCount"] = 999999;

        userInfoJson["fansCount"] = 99999;

        userInfoJson["followCount"] = 99;

        userInfoJson["userState"] = 0;
        userInfoJson["isFollowed"] = 0;
        userInfoJson["userMemo"] = "其它用户";
        userInfoJson["userCreateTime"] = "";
        userInfoJson["avatarFileId"] = "30001";
    }

    QJsonObject rstJson;
    rstJson["userInfo"] = userInfoJson;
    jsonBody["result"] = rstJson;

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////


////////////////////////////////////
/// \brief HttpServer::getCodeFromEmail
/// \param request
/// \return
///
QHttpServerResponse HttpServer::getCodeFromEmail(const QHttpServerRequest &request)
{
#ifdef HTTPSERVER_TEST
    LOG() << "HttpServer::getCodeFromEmail(const QHttpServerRequest &request)";
#endif

    QJsonDocument docreq =QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonReq = docreq.object();

    QJsonObject jsonBody;

    QString email = jsonReq["email"].toString();

#ifdef HTTPSERVER_TEST
    LOG() << "email：" << email;
#endif

    jsonBody["requestId"] = jsonReq["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonObject resultJson;
    resultJson["authCode"] = "520888";
    jsonBody["result"] = resultJson;

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::uploadPhoto
/// \param request
/// \return
///
QHttpServerResponse HttpServer::uploadPhoto(const QHttpServerRequest &request)
{
    QUrlQuery query(request.url());
    QString requestId = query.queryItemValue("requestId");
    QString sessionId = query.queryItemValue("sessionId");

    QByteArray imageData = request.body();

    QDir dir(QDir::currentPath()); // exe 所在的目录
    dir.cdUp();
    dir.cdUp();
    QString imagePath = dir.absolutePath();
    imagePath += "/image/temp.png";

#ifdef HTTPSERVER_TEST
    LOG() << imagePath;
#endif

    writeByteArrayToFile(imagePath,imageData);

    QJsonObject jsonBody;

    jsonBody["requestId"] = requestId;
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";


    QJsonObject resultJson;
    resultJson["fileId"] = "1000";
    jsonBody["result"] = resultJson;

    idPathMap.insert("1000","/image/temp.png");

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::uploadVideo
/// \param request
/// \return
///
QHttpServerResponse HttpServer::uploadVideo(const QHttpServerRequest &request)
{
    QUrlQuery query(request.url());
    QString requestId = query.queryItemValue("requestId");

#ifdef HTTPSERVER_TEST
    LOG() << "HttpServer::uploadVideo(const QHttpServerRequest &request)";
    LOG() << "requestId: " << requestId;
#endif

    QByteArray videoData = request.body();

    QDir dir(QDir::currentPath()); // exe 所在的目录
    dir.cdUp();
    dir.cdUp();
    QString videoPath = dir.absolutePath();
    videoPath += idPathMap["60000"];
    videoPath += "222.mp4";

#ifdef HTTPSERVER_TEST
    LOG() <<videoPath;
#endif

    writeByteArrayToFile(videoPath,videoData);

    // 构建响应体
    QJsonObject jsonBody;
    jsonBody["requestId"] = requestId;
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";


    QJsonObject resultJson;
    resultJson["fileId"] = "60000";
    jsonBody["result"] = resultJson;

    QJsonDocument docRes;
    docRes.setObject(jsonBody);

    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::setAvatar
/// \param request
/// \return
///
QHttpServerResponse HttpServer::setAvatar(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonObject = docReq.object();
    const QString userId = jsonObject["userId"].toString();

#ifdef HTTPSERVER_TEST
    LOG()<<"setAvatar 收到请求"<<jsonObject["requestId"].toString();
#endif

    QJsonObject jsonBody;
    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////


////////////////////////////////////
/// \brief HttpServer::setPassword
/// \param request
/// \return
///
QHttpServerResponse HttpServer::setPassword(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonObject = docReq.object();

#ifdef HTTPSERVER_TEST
    LOG()<<"setPassword 收到请求 收到的密码是:" << jsonObject["password"].toString();
#endif

    QJsonObject jsonBody;
    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////


////////////////////////////////////
/// \brief HttpServer::setNickname
/// \param request
/// \return
///
QHttpServerResponse HttpServer::setNickname(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonObject = docReq.object();

#ifdef HTTPSERVER_TEST
    LOG()<<"setNickname 收到请求 收到的昵称是:" << jsonObject["nickname"].toString();
#endif

    QJsonObject jsonBody;
    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);
    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::deleteVideo
/// \param request
/// \return
///
QHttpServerResponse HttpServer::deleteVideo(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonObject = docReq.object();

#ifdef HTTPSERVER_TEST
    LOG()<<"deleteVideo 收到请求";
    LOG()<<"requestId 是: "<<jsonObject["requestId"].toString();
    LOG()<<"videoId是" << jsonObject["videoId"].toString();
#endif

    QJsonObject jsonBody;
    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);

    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::delAttention
/// \param request
/// \return
/// 取关
QHttpServerResponse HttpServer::delAttention(const QHttpServerRequest &request)
{
    QJsonDocument docReq = QJsonDocument::fromJson(request.body());
    const QJsonObject& jsonObject = docReq.object();

#ifdef HTTPSERVER_TEST
    LOG()<<"deleteVideo 收到请求";
    LOG()<<"requestId 是: "<<jsonObject["requestId"].toString();
    LOG()<<"userId是" << jsonObject["userId"].toString();
#endif

    QJsonObject jsonBody;
    jsonBody["requestId"] = jsonObject["requestId"].toString();
    jsonBody["errorCode"] = 0;
    jsonBody["errorMsg"] = "";

    QJsonDocument docRes;
    docRes.setObject(jsonBody);
    QHttpServerResponse httpRes(docRes.toJson(),QHttpServerResponse::StatusCode::Ok);

    QHttpHeaders headers;
    headers.append("Content-Type", "application/json; charset=utf-8");
    httpRes.setHeaders(headers);
    return httpRes;
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::getInstance
/// \return
/// 单例化
HttpServer *HttpServer::getInstance()
{
    if(instance ==nullptr)
    {
        instance =new HttpServer();
    }
    return instance;
}
////////////////////////////////////


////////////////////////////////////
/// \brief HttpServer::buildResponseData
///
void HttpServer::buildResponseData()
{

    int resourceId = 10000;
    for(int i = 0; i < 100; i++)
    {
        idPathMap.insert(QString::number(resourceId++),"/image/videoImage.png");
        idPathMap.insert(QString::number(resourceId++),"/image/touXiang.png");
        idPathMap.insert(QString::number(resourceId++),"/video/output.m3u8");
    }

    resourceId = 20000;
    for(int i = 0; i < 100; i ++)
    {
        idPathMap.insert(QString::number(resourceId++),"/image/videoImage1.png");
        idPathMap.insert(QString::number(resourceId++),"/image/touXiang1.png");
        idPathMap.insert(QString::number(resourceId++),"/video/output.m3u8");

    }

    resourceId = 30000;
    for(int i = 0; i < 100; i ++)
    {
        idPathMap.insert(QString::number(resourceId++),"/image/videoImage2.png");
        idPathMap.insert(QString::number(resourceId++),"/image/touXiang2.png");
        idPathMap.insert(QString::number(resourceId++),"/video/output.m3u8");
    }

    resourceId = 40000;
    for(int i = 0; i < 100; i ++)
    {
        idPathMap.insert(QString::number(resourceId++),"/image/videoImage3.png");
        idPathMap.insert(QString::number(resourceId++),"/image/touXiang3.png");
        idPathMap.insert(QString::number(resourceId++),"/video/output.m3u8");
    }

    resourceId = 50000;
    for(int i = 0; i < 100; i ++)
    {
        idPathMap.insert(QString::number(resourceId++),"/image/videoImage3.png");
        idPathMap.insert(QString::number(resourceId++),"/image/touXiang3.png");
        idPathMap.insert(QString::number(resourceId++),"/video/output.m3u8");
    }


    idPathMap.insert(QString::number(60000),"/video/");
}
////////////////////////////////////



////////////////////////////////////
/// \brief HttpServer::init
/// \return
/// 绑定端口等 初始化 工作
bool HttpServer::init()
{
    httpServer->route("/hello",[=](const QHttpServerRequest& req){
        return this->helloService(req);
    });

    // httpServer->route("/VidNova/auth/login",[=](const QHttpServerRequest& req){
    //     return this->tempLoginService(req);
    // });  // 接收到 /VidNova/auth/login 来自这个请求 提供对应的 tempLoginService 服务

    httpServer->route("/VidNova/data/get_all_video",[=](const QHttpServerRequest& req){
        return this->allVideoList(req);
    });  //

    httpServer->route("/VidNova/data/get_video_by_kind",[=](const QHttpServerRequest& req){
        return this->videoByKind(req);
    });  //


    httpServer->route("/VidNova/data/get_video_by_tag",[=](const QHttpServerRequest& req){
        return this->videoByTag(req);
    });  //

    httpServer->route("/VidNova/data/get_video_by_key",[=](const QHttpServerRequest& req){
        return this->videoByKey(req);
    });  // 获取所有视频

    httpServer->route("/VidNova/data/download_photo",[=](const QHttpServerRequest& req){
        return this->downloadPhoto(req);
    });  // 获取图片

    httpServer->route("/VidNova/data/download_video",[=](const QHttpServerRequest& req){
        return this->downloadVideoM3u8File(req);
    });  // 获取视频

    httpServer->route("/VidNova/data/get_bullets",[=](const QHttpServerRequest& req){
        return this->getBullets(req);
    });  // 获取视频

    httpServer->route("/video/<arg>",[=](const QString& file_name, const QHttpServerRequest &request){
        return this->downloadVideoSegmentation(file_name);
    });  // 获取视频切片


    httpServer->route("/VidNova/data/add_play_number",[=](const QHttpServerRequest& req){
        return this->addPlayNumber(req);
    });


    httpServer->route("/VidNova/data/is_likeBtn_clicked",[=](const QHttpServerRequest& req){
        return this->isLikeBtnClicked(req);
    });

    httpServer->route("/VidNova/data/likeBtn",[=](const QHttpServerRequest& req){
        return this->addLikeNumber(req);
    });

    httpServer->route("/VidNova/data/sendBullet",[=](const QHttpServerRequest& req){
        return this->newBullet(req);
    });

    httpServer->route("/VidNova/data/get_user_info",[=](const QHttpServerRequest& req){
        return this->getUserInfo(req);
    });


    httpServer->route("/VidNova/data/upload_photo",[=](const QHttpServerRequest& req){
        return this->uploadPhoto(req);
    });

    httpServer->route("/VidNova/data/set_avatar",[=](const QHttpServerRequest& req){
        return this->setAvatar(req);
    });

    // 获取视频列表
    httpServer->route("/VidNova/data/user_video_list",[=](const QHttpServerRequest& req){
        return this->getUserVideoInfo(req);
    });

    // 删除用户列表的视频
    httpServer->route("/VidNova/data/delete_video",[=](const QHttpServerRequest& req){
        return this->deleteVideo(req);
    });

    // 更新用户关注状态
    httpServer->route("/VidNova/data/alter_attention",[=](const QHttpServerRequest& req){
        return this->alterAttention(req);
    });

    httpServer->route("/VidNova/data/add_attention",[=](const QHttpServerRequest& req){
        return this->addAttention(req);
    });

    httpServer->route("/VidNova/data/del_attention",[=](const QHttpServerRequest& req){
        return this->delAttention(req);
    });

    httpServer->route("/VidNova/data/get_code_from_email",[=](const QHttpServerRequest& req){
        return this->getCodeFromEmail(req);
    });

    httpServer->route("/VidNova/auth/lr_by_authcode",[=](const QHttpServerRequest& req){
        return this->lrByAuthCode(req);
    });

    httpServer->route("/VidNova/auth/lr_by_pd",[=](const QHttpServerRequest& req){
        return this->lrByPd(req);
    });

    httpServer->route("/VidNova/auth/login_by_session",[=](const QHttpServerRequest& req){
        return this->loginBySession(req);
    });

    httpServer->route("/VidNova/auth/logout",[=](const QHttpServerRequest& req){
        return this->logout(req);
    });

    // 设置密码
    httpServer->route("/VidNova/data/set_password",[=](const QHttpServerRequest& req){
        return this->setPassword(req);
    });

    httpServer->route("/VidNova/data/set_nickname",[=](const QHttpServerRequest& req){
        return this->setNickname(req);
    });

    httpServer->route("/VidNova/data/upload_video",[=](const QHttpServerRequest& req){
        return this->uploadVideo(req);
    });

    httpServer->route("/VidNova/data/newVideo",[=](const QHttpServerRequest& req){
        return this->newVideo(req);
    });

    httpServer->route("/<arg:.*>", [](const QHttpServerRequest &request) {
        LOG() << "URL:" << request.url().toString();
        LOG() << "Method:" << request.method();
        LOG() << "Headers:" << request.headers();
        return QHttpServerResponse(QHttpServerResponse::StatusCode::NotFound);
    });


    bool ret_1 = tcpServer->listen(QHostAddress::Any,8080);
    bool ret_2 = httpServer->bind(tcpServer.get());

    return ret_1 and ret_2;
}
////////////////////////////////////


