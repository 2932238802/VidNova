#include "netClient.h"


net::netClient::netClient()
{

}

void net::netClient::hello()
{
    QJsonObject reqBody;
    QNetworkRequest httpReq;
    httpReq.setUrl(baseUrl + "/hello");
    httpReq.setHeader(QNetworkRequest::ContentTypeHeader,"application/json; charset=utf8");

    reqBody["msg"] = "hello world!";
    reqBody["requestId"] = makeRequestUuid();

    QJsonDocument document(reqBody);
    QNetworkReply* reply = manage.post(httpReq,document.toJson());
    connect(reply , &QNetworkReply::finished,this,[=](){
        if(reply->error() != QNetworkReply::NoError)
        {
            LOG()<< "[err]"<<reply->errorString();

            return;
        }
        QByteArray replyBody = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(replyBody);
        if(jsonDoc.isNull())
        {
            LOG()<<"解析json失败...";
            return;
        }

        //  业务逻辑的判断
        QJsonObject jsonObject = jsonDoc.object();
        if(jsonObject["errorCode"].toInt()!= 0)
        {
            LOG()<<jsonObject["errorMsg"].toString(); // 打印错误信息
            return;
        }

        // 解析响应的数据
        /* {
         *      errorCode:
         *      errorMsg:
         *      data{
         *
         *      }
         *
         *
         * }
        */
        QJsonObject userData = jsonObject["data"].toObject();
        LOG() << userData["msg"].toString();

        reply->deleteLater();
    });
}

QString net::netClient::makeRequestUuid()
{
    // 使用 后面12位
    return QUuid::createUuid().toString().slice(24,12);
}


















