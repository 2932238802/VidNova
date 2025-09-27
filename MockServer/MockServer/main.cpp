#include "mockServer.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "src/httpServer.h"
#include "common/mylog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HttpServer* server = HttpServer::getInstance();
    if(!server->init())
    {
        LOG()<<"初始化失败...";
        return -1;
    }


    MockServer w;
    w.show();
    return a.exec();
}
