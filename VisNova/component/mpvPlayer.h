#pragma once
#include <QObject>
#include<QWidget>
#include <mpv/client.h>
#include "common/myLog.h"

class MpvPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MpvPlayer(QObject *parent = nullptr,QWidget* videoRenderWnd = nullptr);
    ~MpvPlayer();

private:
    mpv_handle* mpv = nullptr;

private slots:
    void onMpvEvents();
    // void

signals:
    void mpvEvents(); // 当mpv 触发事件的时候 发射该信号 用户程序处理 这个 信号
};


