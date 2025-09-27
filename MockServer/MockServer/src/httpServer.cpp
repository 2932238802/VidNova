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
/// \brief HttpServer::init
/// \return
/// 绑定端口等 初始化 工作
bool HttpServer::init()
{
    httpServer->route("/hello",[=](const QHttpServerRequest& req){
        return this->helloService(req);
    });
    bool ret = tcpServer->listen(QHostAddress::Any,8080);
    bool ret_2 = httpServer->bind(tcpServer.get());

    LOG()<<"ret"<<ret;
    LOG()<<"ret_2"<<ret_2;

    return ret and ret_2;
}
////////////////////////////////////


