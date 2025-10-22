#pragma once
#include <QObject>
#include<QWidget>
#include <mpv/client.h>
#include <QStringList>
#include <QDir>
#include <QProcess>
#include "common/constants.h"
#include "common/myLog.h"

class MpvPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MpvPlayer(QWidget* videoRenderWnd = nullptr,QObject *parent = nullptr);
    ~MpvPlayer();

    double getPlayTotalTime() const;
    static QString getVideoFirstPage(const QString& video_path);

    void mute(bool isMute);

    void play(); // 开始
    void pause(); // 暂停

    void startPlay(const QString& video_path);
    void setSpeed(double speed);
    void setTimePos(double time_pos); //
    void setVolume(int64_t volume); // 音量调节方法


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
    void _duration(int64_t duration);
};


