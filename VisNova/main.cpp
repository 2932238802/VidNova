#include "vidnovamain.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "startPage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "VisNova_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    VidNovaMain*w = VidNovaMain::getInstance();

    // 先显示启动
    start_page startPage;
    startPage.exec();


    w->show();
    return a.exec();
}
