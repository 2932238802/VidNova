#pragma once
#include <QObject>
#include<QWidget>
#include <mpv/client.h>
#include "common/constants.h"
#include "common/myLog.h"

class MpvPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MpvPlayer(QWidget* videoRenderWnd = nullptr,QObject *parent = nullptr);
    ~MpvPlayer();
    void startPlay(const QString& videoPath);
    void setSpeed(double speed);
    void play(); // 开始
    void pause(); // 暂停
    void mute(bool isMute);
    void setVolume(int64_t volume); // 音量调节方法
    void setTimePos(double timePos); //
    double getPlayTotalTime() const;

private:
    void handleMpvEvent(mpv_event* event);


private:
    mpv_handle* mpv = nullptr;

private slots:
    void onMpvEvents();

    // void

signals:
    void mpvEvents(); // 当mpv 触发事件的时候 发射该信号 用户程序处理 这个 信号
    void playPositionSignals(double seconds);
    void medioLoaded(double totalTime);
    void medioFinished();
};


