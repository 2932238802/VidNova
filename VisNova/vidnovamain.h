#pragma once
#include <QGraphicsDropShadowEffect>
#include <QWidget>
#include <QMouseEvent>
#include "myPage.h"
#include"style.h"
#include"uploadVideoPage.h"

QT_BEGIN_NAMESPACE
namespace Ui{
class VidNovaMain;
}
QT_END_NAMESPACE

enum StackWidgetPage{
    HOME_PAGE,
    MY_PAGE,
    SYSTEM_PAGE,
    UPLOADVEDIO_PAGE
};

class VidNovaMain : public QWidget
{
    Q_OBJECT

public:
    static VidNovaMain* getInstance();
    ~VidNovaMain() =default;

    void showSystemBtn(bool is_show);


private:
    VidNovaMain(QWidget *parent = nullptr);
    void initUi();
    void connectSignalAndSlot();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);


// 槽函数
private slots:
    void onSwitchPage(int page_id);

private:
    QPoint dragPosition;
    bool isDragging;
    void resetSwitchButton(int page_id);
    Ui::VidNovaMain *ui;

};

