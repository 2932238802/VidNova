
#include "netClient.h"
#include "dataCenter/dataCenter.h"

net::NetClient::NetClient(model::DataCenter* data_center):
    dataCenter(data_center)
{
    baseUrl = dataCenter->getUrl();

#ifdef NETCLIENT_TEST
    LOG()<<"baseUrl "<<baseUrl;
#endif
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


///////////////////////////////////////
/// \brief net::NetClient::makeRequestUuid
/// \return
///
QString net::NetClient::makeRequestUuid()
{
    // 使用 后面12位
    return 'R' + QUuid::createUuid().toString().slice(24,12);
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::setAvatar
/// \param fileId
///
void net::NetClient::setAvatar(const QString &fileId)
{
#ifdef NETCLIENT_TEST
    LOG()<<"进入 setAvatar ..." << "fileId 是 " << fileId;
#endif

    QJsonObject replyBody ; // 构造请求体
    replyBody["sessionId"] = dataCenter->getSessionId(); //登录之后 获得的
    replyBody["fileId"] = fileId;

    // 发送请求
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/data/set_avatar",replyBody);

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

        dataCenter->setAvatar(fileId);

        emit dataCenter->_setAvatarDone();


        QJsonObject resultObject = replyObject["result"].toObject();
        QJsonObject userInfo = resultObject["userInfo"].toObject();


    });

}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::setNewPassword
/// \param password
///
void net::NetClient::setNewPassword(const QString &password)
{
#ifdef NETCLIENT_TEST
    LOG()<<"net::NetClient::setNewPassword(const QString &password)" ;
#endif

    QJsonObject replyBody ; // 构造请求体
    replyBody["sessionId"] = dataCenter->getSessionId(); //登录之后 获得的
    replyBody["password"] = password; //登录之后 获得的

    // 发送请求
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/data/set_password",replyBody);

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

        // 发送 密码修改成功 的信号
        emit dataCenter->_setPasswordDone();

#ifdef NETCLIENT_TEST
        LOG()<<"修改密码 发送成功..." ;
#endif
    });

}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::setNickname
/// \param nickname
/// 设置昵称
void net::NetClient::setNickname(const QString &nickname)
{
#ifdef NETCLIENT_TEST
    LOG()<<"net::NetClient::setNickname(const QString &nickname)" ;
#endif

    QJsonObject replyBody ; // 构造请求体
    replyBody["sessionId"] = dataCenter->getSessionId(); //登录之后 获得的
    replyBody["nickname"] = nickname; //登录之后 获得的

    // 发送请求
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/data/set_nickname",replyBody);

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

        // 发送 密码修改成功 的信号
        emit dataCenter->_setNicknameDone(nickname);

#ifdef NETCLIENT_TEST
        LOG()<<"设置昵称 发送成功..." ;
#endif
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::getCodeFromEmail
/// \param email
///
void net::NetClient::getCodeFromEmail(const QString &email)
{
#ifdef NETCLIENT_TEST
    LOG()<<"进入 getCodeFromEmail ..." << "email 是 " << email;
#endif

    QJsonObject replyBody ; // 构造请求体
    replyBody["sessionId"] = dataCenter->getSessionId(); //登录之后 获得的
    replyBody["email"] = email;

    // 发送请求
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/data/get_code_from_email",replyBody);

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

        QJsonObject rltObject = replyObject["result"].toObject();
        QString authCode = rltObject["authCode"].toString();
        QString codeId = rltObject["codeId"].toString();

#ifdef NETCLIENT_TEST
        LOG() << "net::NetClient::getCodeFromEmail(const QString &email)";
        LOG() << "从服务器获得验证码: " << authCode;
#endif

        emit dataCenter->_getCodeFromEmailDone(authCode,codeId); // 把验证码发出去
    });
}
///////////////////////////////////////



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
            LOG()<<"请求出错了..." << "";
            return;
        }

        QJsonObject resultObject = replyObject["result"].toObject();

        dataCenter->setSessionId(resultObject["sessionId"].toString());

        LOG()<<"[inf] resultObject"<<resultObject;
        LOG()<<"[inf] 临时用户登录成功 requestId: " << replyObject["requestId"].toString();

        emit dataCenter->_loginSucDone(); // 发送登录 成功信号/
    });
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief net::NetClient::lrByAuthCode
/// \param email
/// \param auth_code
///
void net::NetClient::lrByAuthCode(const QString &email, const QString &auth_code,const QString &codeId)
{
    QJsonObject replyBody ; // 构造请求体
    auto videoList = dataCenter->getVideoList();
    int curPageIndex = videoList->getPageIndex();

#ifdef NETCLIENT_TEST
    LOG()<< "net::NetClient::lrByAuthCode(const QString &email, const QString &auth_code,const QString &codeId)";
    LOG()<< "email: " << email;
    LOG()<< "authCode" << auth_code;
    LOG()<< "codeId" << codeId;
#endif

    replyBody["requestId"] = makeRequestUuid();
    replyBody["sessionId"] = dataCenter->getSessionId();

    replyBody["email"] = email;
    replyBody["authCode"] = auth_code; // 每次请求 20 个

    replyBody["codeId"] = codeId;

    // 发送请求
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/auth/lr_by_authcode",replyBody);

    connect(httpReply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;

        QJsonObject replyObject = handHttpResponse(httpReply,ok,reason);

        if(!ok)
        {
            LOG()<<"请求出错了...";
            emit dataCenter->_lrByAuthCodeFailed(reason);
            return;
        }

        // TODO: 这里还没有改
        emit dataCenter->_lrByAuthCodeSuc(); // 发送登录 成功信号/
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::lrByPd
/// \param at
/// \param pd
///
void net::NetClient::lrByPd(const QString &at, const QString &pd)
{
    QJsonObject replyBody ; // 构造请求体

    QString sessionId = dataCenter->getSessionId();

#ifdef NETCLIENT_TEST
    LOG()<< "net::NetClient::lrByPd(const QString &at, const QString &pd)";
    LOG()<< "at: " << at; // 请求的账号
    LOG()<< "pd: " << pd; // 请求的密码
#endif

    replyBody["requestId"] = makeRequestUuid();
    replyBody["account"] = at;
    replyBody["password"] = pd;

    // 发送请求 账号密码登录
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/auth/lr_by_pd",replyBody);

    connect(httpReply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;

        QJsonObject replyObject = handHttpResponse(httpReply,ok,reason);

        if(!ok)
        {
            LOG()<<"请求出错了...";
            LOG()<<"登录失败了...";
            emit dataCenter->_lrByPdFailed(reason);
            return;
        }


        // TODO: 这里还没有改
        QString userId = replyObject["userId"].toString();

        QString sessionId = replyObject["sessionId"].toString();

#ifdef NETCLIENT_TEST
        LOG()<< "net::NetClient::lrByPd(const QString &at, const QString &pd)";
        LOG()<< "服务器返回内容是:" << replyObject;
        LOG()<< "userId " << userId; // 请求的账号
#endif

        dataCenter->setUserIdOnce(userId);
        dataCenter->setSessionId(sessionId);
        emit dataCenter->_lrByPdSuc(); // 发送登录 成功信号/
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::loginBySession
///
void net::NetClient::loginBySession()
{
    QJsonObject replyBody ; // 构造请求体

#ifdef NETCLIENT_TEST
    LOG()<< "net::NetClient::loginBySession()";
#endif

    replyBody["requestId"] = makeRequestUuid();
    replyBody["sessionId"] = dataCenter->getSessionId();

    // 发送请求 账号密码登录
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/auth/login_by_session",replyBody);

    connect(httpReply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;

        QJsonObject replyObject = handHttpResponse(httpReply,ok,reason);

#ifdef NETCLIENT_TEST
        LOG()<< "replyObject: " << replyObject;
#endif

        if(!ok)
        {
            LOG()<<"请求出错了...";
            LOG()<<"登录失败了...";
            emit dataCenter->_loginBySessionFailed(reason);
            return;
        }

        QJsonObject rst = replyObject["result"].toObject();
        QString userId = rst["userId"].toString();

        dataCenter->setUserIdOnce(userId);

        emit dataCenter->_loginBySessionSuc(rst["isTemp"].toBool()); // 发送登录 成功信号/
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::logout
/// 退出登录
void net::NetClient::logout()
{
    QJsonObject replyBody ; // 构造请求体

#ifdef NETCLIENT_TEST
    LOG()<< "net::NetClient::loginBySession()";
#endif

    replyBody["requestId"] = makeRequestUuid();
    replyBody["sessionId"] = dataCenter->getSessionId();

    // 发送请求 账号密码登录
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/auth/logout",replyBody);

    connect(httpReply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;
        QJsonObject replyObject = handHttpResponse(httpReply,ok,reason);

        emit dataCenter->_logoutDone();
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


        LOG()<<"requestId是：" << replyObject["requestId"].toString();

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
/// \brief net::NetClient::getVideoByState
/// \param video_state
/// \param page_count
/// 获取视频列表
void net::NetClient::getVideoByState(model::VideoState video_state, int page_index)
{
#ifdef NETCLIENT_TEST
    LOG()<<"net::NetClient::getVideoByState(model::VideoState video_state, int page_count)" ;
#endif

    QJsonObject replyBody ; // 构造请求体
    auto videoList = dataCenter->getVideoList();
    int curPageIndex = videoList->getPageIndex();
    replyBody["requestId"] = makeRequestUuid();
    replyBody["sessionId"] = dataCenter->getSessionId(); //登录之后 获得的
    replyBody["pageCount"] = model::VideoList::PAGE_COUNT; // 每次请求 20 个
    replyBody["pageIndex"] = page_index;
    replyBody["videoState"] = video_state;

    // 为了下次能够获取下一页
    videoList->setPageIndex(curPageIndex+1);


    // 发送请求
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/data/get_video_by_state",replyBody);

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
        dataCenter->setManageSearchVideoList(resultObject);
        emit dataCenter->_getVideoByStateDone(); // 发送登录 成功信号/
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
/// \brief net::NetClient::getUserInfo
/// \param userId
///
void net::NetClient::getUserInfo(const QString &userId)
{
#ifdef NETCLIENT_TEST
    LOG()<<"进入 getUserInfo ..." << "userId 是" << userId;
#endif

    QJsonObject replyBody ; // 构造请求体
    replyBody["requestId"] = makeRequestUuid();
    replyBody["sessionId"] = dataCenter->getSessionId(); //登录之后 获得的
    replyBody["userId"] = userId;

    // 发送请求
    QNetworkReply* httpReply = sendHttpRequest("/VidNova/data/get_user_info",replyBody);

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

        QJsonObject resultObject = replyObject["result"].toObject();
        QJsonObject userInfo = resultObject["userInfo"].toObject();
        if(userId == dataCenter->getUserId())
        {

#ifdef NETCLIENT_TEST
            LOG()<<"获取个人信息";
            LOG()<< "userId" << userId;
#endif


            dataCenter->setMyselfInfo(userInfo);
            emit dataCenter->_getMyselfInfoDone();
        }
        else{

#ifdef NETCLIENT_TEST
            LOG()<<"获取他人信息";
            LOG()<< "userId" << userId;
#endif

            dataCenter->setOtherInfo(userInfo);
            emit dataCenter->_getOtherInfoDone(); // 发送登录 成功信号/
        }


    });

}
///////////////////////////////////////


///////////////////////////////////////
/// \brief net::NetClient::getVideoListForMyselfOrOther
/// \param userId
/// \param pageIndex
///
void net::NetClient::getVideoListForMyselfOrOther(const QString &userId, int page_index,model::GetVideoPage page)
{

#ifdef NETCLIENT_TEST
    LOG() << "net::NetClient::getVideoListForMyselfOrOther(const QString &userId, int page_index,model::GetVideoPage page)";
#endif

    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["requestId"] = makeRequestUuid();
    request["userId"] = userId;
    request["pageIndex"] = page_index;
    request["pageCount"] = model::VideoList::PAGE_COUNT; // 一次性要多少个


    QNetworkReply* reply = sendHttpRequest("/VidNova/data/user_video_list",request);

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

        if(page == model::GetVideoPage::ManagePage)
        {

#ifdef NETCLIENT_TEST
            LOG() << "获取个人他人的信息";
#endif
            dataCenter->setManageSearchVideoList(resultJson);
        }
        else if(page  == model::GetVideoPage::MyPage)
        {

#ifdef NETCLIENT_TEST
            LOG() << "获取指定用户的信息";
#endif
            dataCenter->setUserVideoList(resultJson);
        }

        emit dataCenter->_getVideoListForMyselfOrOtherDone(userId,page);

    });
}
///////////////////////////////////////




///////////////////////////////////////
/// \brief net::NetClient::getAdminInfoByEmail
/// \param emailNumber
/// 通过 手机号 查询的方式 获取管理员信息
void net::NetClient::getAdminInfoByEmail(const QString &emailNumber)
{
#ifdef NETCLIENT_TEST
    LOG() << "net::NetClient::getAdminInfoByPhone(const QString &emailNumber)";
#endif

    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["requestId"] = makeRequestUuid();
    request["emailNumber"] = emailNumber;

    QNetworkReply* reply = sendHttpRequest("/VidNova/admin/get_admin_by_email",request);

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
        dataCenter->setAdminList(resultJson,false);

        emit dataCenter->_getAdminInfoByEmailDone();
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::getAdminInfoByState
/// \param page_index
/// \param state
///
void net::NetClient::getAdminInfoByState(int page_index, model::AdminState state)
{
#ifdef NETCLIENT_TEST
    LOG() << "net::NetClient::getAdminInfoByPhone(const QString &emailNumber)";
#endif

    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["requestId"] = makeRequestUuid();
    request["pageCount"] = model::AdminList::PAGE_COUNT;
    request["pageIndex"] = page_index;
    request["userState"] = state;

    QNetworkReply* reply = sendHttpRequest("/VidNova/admin/get_admin_by_state",request);

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
        dataCenter->setAdminList(resultJson,true); // 状态进行获取

        emit dataCenter->_getAdminInfoByStateDone();
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::putOnVideo
/// \param videoId
/// 上架视频
void net::NetClient::putOnVideo(const QString &videoId)
{
#ifdef NETCLIENT_TEST
    LOG() << "net::NetClient::putOnVideo(const QString &videoId)";
#endif

    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["requestId"] = makeRequestUuid();
    request["videoId"] = videoId;

    QNetworkReply* reply = sendHttpRequest("/VidNova/admin/put_on_video",request);

    connect(reply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;
        QJsonObject replyObject = handHttpResponse(reply,ok,reason);
        if(!ok)
        {
            LOG()<<"请求出错了..." << reason;
            return;
        }

        emit dataCenter->_putOnVideoDone();

    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::putDownVideo
/// \param videoId
///
void net::NetClient::putDownVideo(const QString &videoId)
{
#ifdef NETCLIENT_TEST
    LOG() << "net::NetClient::putDownVideo(const QString &videoId)";
#endif

    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["requestId"] = makeRequestUuid();
    request["videoId"] = videoId;

    QNetworkReply* reply = sendHttpRequest("/VidNova/admin/put_down_video",request);

    connect(reply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;
        QJsonObject replyObject = handHttpResponse(reply,ok,reason);
        if(!ok)
        {
            LOG()<<"请求出错了..." << reason;
            return;
        }

        emit dataCenter->_putDownVideoDone();

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

        reply->deleteLater();
    });
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief net::NetClient::alterAttention
/// \param user_id
///
void net::NetClient::alterAttention(const QString &user_id)
{
#ifdef NETCLIENT_TEST
    LOG() << "net::NetClient::alterAttention(const QString &user_id)";
    LOG() << "更改关注状态";
    LOG() << "user_id" << user_id;
#endif

    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["userId"] = user_id;
    request["requestId"] = makeRequestUuid();
    QNetworkReply* reply = sendHttpRequest("/VidNova/data/alter_attention",request);

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
            LOG() <<"alterAttention请求发送成功";
        }
        reply->deleteLater();
    });
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief net::NetClient::addAttention
/// \param user_id
///
void net::NetClient::addAttention(const QString &user_id)
{

#ifdef NETCLIENT_TEST
    LOG() << "net::NetClient::addAttention(const QString &user_id)";
    LOG() << "关注了一个up主：";
    LOG() << "user_id" << user_id;
#endif

    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["userId"] = user_id;
    request["requestId"] = makeRequestUuid();
    QNetworkReply* reply = sendHttpRequest("/VidNova/data/add_attention",request);
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
            LOG() <<"addAttention请求发送成功";
        }
        emit dataCenter->_addAttention();

        reply->deleteLater();
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

        reply->deleteLater();
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::checkVideo
/// \param videoId
/// \param result
///
void net::NetClient::checkVideo(const QString &videoId, bool result)
{
    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["videoId"] = videoId;
    request["requestId"] = makeRequestUuid();
    request["checkResult"] = result; // 审查结果

    QNetworkReply* reply = sendHttpRequest("/VidNova/admin/checkVideo",request);

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
            LOG() <<"checkVideo 请求发送成功";
        }

        emit dataCenter->_checkVideoDone();

        reply->deleteLater();
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

        reply->deleteLater();
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::uploadPhoto
/// \param photo_data
///  上传图片
void net::NetClient::uploadPhoto(const QByteArray &photo_data,PhotoUploadPurpose pup)
{
    // 构造请求
    // 发送请求
    QString queryString;
    queryString+="requestId=";
    queryString+=makeRequestUuid();
    queryString+="&";
    queryString+="sessionId=";
    queryString+=dataCenter->getSessionId();


    QNetworkRequest request;
    request.setUrl(QUrl(baseUrl + "/VidNova/data/upload_photo?" + queryString));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/octet-stream");
    // 发送亲求

    QNetworkReply* reply = manage.post(request,photo_data);


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
            LOG() <<"uploadPhoto 请求发送成功";
        }

        const QString& requestId = replyObject["requestId"].toString();

        QJsonObject resultObject = replyObject["result"].toObject();

        const QString& fileId = resultObject["fileId"].toString();

        emit dataCenter->_uploadPhotoDone(fileId,pup);

        reply->deleteLater();

    });
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief net::NetClient::uploadVideo
/// \param video_path
///
void net::NetClient::uploadVideo(const QString &video_path)
{
    // 构造请求
    // 发送请求
    // QString queryString;
    // queryString+="requestId=";
    // queryString+=makeRequestUuid();
    // queryString+="&";
    // queryString+="sessionId=";
    // queryString+=dataCenter->getSessionId();


    QUrl url(baseUrl + "/VidNova/data/upload_video?");
    QUrlQuery query;
    query.addQueryItem("requestId",makeRequestUuid());
    query.addQueryItem("sessionId",dataCenter->getSessionId());
    url.setQuery(query);

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader,"multipart/form-data");

    // 读取文件数据
    QByteArray videoData = loadFileToByteArray(video_path);

    QNetworkReply* reply = manage.post(request,videoData);

    connect(reply,&QNetworkReply::finished,this,[=](){

        bool ok = false;
        QString reason; // 错误原因
        QJsonObject replyObject = handHttpResponse(reply,ok,reason);

        if(!ok)
        {
#ifdef DATACENTER_TEST
            LOG()<<"请求出错了..." << reason;
#endif
            reply->deleteLater();
            return;
        }
        else{
#ifdef DATACENTER_TEST
            LOG() <<"uploadVideo 请求发送成功";
#endif
        }

        const QString& requestId = replyObject["requestId"].toString();

        QJsonObject resultObject = replyObject["result"].toObject();

        const QString& fileId = resultObject["fileId"].toString();

        // 发送信号
        emit dataCenter->_uploadVideoDone(fileId);
        reply->deleteLater();
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::uploadVideoInfoForUpload
/// \param video_info_for_upload
///
void net::NetClient::uploadVideoInfoForUpload(const model::VideoInfoForUpload &video_info_for_upload)
{
    QJsonObject reqBody;
    reqBody["requestId"] = makeRequestUuid();
    reqBody["sessionId"] = dataCenter->getSessionId();

    QJsonObject videoInfo;
    videoInfo["videoFileId"] = video_info_for_upload.videoFileId;
    videoInfo["photoFileId"] = video_info_for_upload.photoFileId;
    videoInfo["videoTitle"] = video_info_for_upload.videoTitle;
    videoInfo["videoDesc"] = video_info_for_upload.videoDesc;
    videoInfo["duration"] = video_info_for_upload.duration;

    // videoInfo["kind"] = video_info_for_upload.getKinds();
    // videoInfo["tag"] = video_info_for_upload.getTag();

    auto kindAndTag = dataCenter->getkatPtr();
    if(!video_info_for_upload.kind.isEmpty())
    {
        //
        videoInfo["videoType"] = kindAndTag->getKindId(video_info_for_upload.kind);

        QJsonArray tagsArray;
        for(auto &tag: video_info_for_upload.tags)
        {
            tagsArray.append(kindAndTag->getTagId(video_info_for_upload.kind,tag));
        }

        videoInfo["videoTags"] = tagsArray;
    }

    reqBody["videoInfo"] = videoInfo;

    QNetworkReply* httpReply = sendHttpRequest("/VidNova/data/newVideo",reqBody);

    connect(httpReply,&QNetworkReply::finished,this,[=](){

        bool ok = false;
        QString reason; // 错误原因
        QJsonObject replyObject = handHttpResponse(httpReply,ok,reason);

        if(!ok)
        {
#ifdef DATACENTER_TEST
            LOG()<<"请求出错了..." << reason;
#endif
            httpReply->deleteLater();
            return;
        }
        else{
#ifdef DATACENTER_TEST
            LOG() <<"uploadVideo 请求发送成功";
#endif
        }

        emit dataCenter->_uploadVideoInfoForUpload();
        httpReply->deleteLater();
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::deleteVideo
/// \param video_id
///
void net::NetClient::deleteVideo(const QString &video_id)
{
    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["videoId"] = video_id;

#ifdef NETCLIENT_TEST
    LOG ()<<"net::NetClient::deleteVideo(const QString &video_id)";
    LOG() << "video_id" << video_id;
#endif

    QNetworkReply *reply =
        sendHttpRequest("/VidNova/data/delete_video", request);

    connect(reply,&QNetworkReply::finished,this,[=](){
        bool ok = false;
        QString reason;
        QJsonObject replyObject = handHttpResponse(reply,ok,reason);
        if(!ok)
        {
            LOG()<<"deleteVideo 请求出错了..." << reason;
            return;
        }
        else{
            LOG() <<"deleteVideo 请求发送成功";
        }


        emit dataCenter->_deleteVideoDone(video_id);
        reply->deleteLater();
    });
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief net::NetClient::delAttention
/// \param user_id
/// 取消了一个关注
void net::NetClient::delAttention(const QString &user_id)
{
#ifdef NETCLIENT_TEST
    LOG() << "net::NetClient::delAttention(const QString &user_id)";
    LOG() << "取关了一个up主：";
    LOG() << "user_id" << user_id;
#endif

    QJsonObject request;
    request["sessionId"] = dataCenter->getSessionId();
    request["userId"] = user_id;
    request["requestId"] = makeRequestUuid();
    QNetworkReply* reply = sendHttpRequest("/VidNova/data/del_attention",request);
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
            LOG() <<"delAttention请求发送成功";
        }

        emit dataCenter->_delAttention();
        reply->deleteLater();
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












