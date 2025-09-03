#pragma once
#include <QGraphicsDropShadowEffect>
#include <QWidget>
#include <QMouseEvent>
#include "myPage.h"
#include"style.h"
#include"uploadVedioPage.h"

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
    VidNovaMain(QWidget *parent = nullptr);
    ~VidNovaMain();

private:
    void initUi();
    void connectSignalAndSlot();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    QPoint dragPosition;
    bool isDragging;
    void resetSwitchButton(int page_id);

// 槽函数
private slots:
    void onSwitchPage(int page_id);

private:
    Ui::VidNovaMain *ui;
};

