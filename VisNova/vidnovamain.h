#pragma once
#include <QGraphicsDropShadowEffect>
#include <QWidget>
#include <QMouseEvent>
#include "myPage.h"
#include"style.h"
#include"uploadVideoPage.h"



// 1. 可以实现 其它用户界面更新了 但是 再次点击 我的界面的之后 没有更新回 我的界面


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

    void switchMyPageForOtherUser(const QString& user_id);

    void onlySwitchPage(int page_id);

private:
    VidNovaMain(QWidget *parent = nullptr);
    void initUi();
    void connectSignalAndSlot();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

// 槽函数
private slots:
    void onSwitchPageAndUpdataUiForMyPage(int page_id);
    void onSwitchPageAndUpdataUiForUploadVideoPage(int page_id,const QString& filename);

private:
    QPoint dragPosition;
    bool isDragging;
    void resetSwitchButton(int page_id);
    Ui::VidNovaMain *ui;
    static VidNovaMain* instance;

};

