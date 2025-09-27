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
    start_page startPage;
    startPage.exec();

#ifdef HTTP_TEST
    TestFromRequest();
#endif

    w->show();

    return a.exec();
}
