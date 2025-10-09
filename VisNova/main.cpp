#include "vidnovamain.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "startPage.h"
#include "net/testHttp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VidNovaMain*w = VidNovaMain::getInstance();

    // 先显示启动
    StartPage startPage;
    startPage.exec();

    w->show();

    return a.exec();
}
