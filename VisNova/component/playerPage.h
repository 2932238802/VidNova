#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <QShortcut>
#include <QFrame>
#include <QDialog>
#include <memory.h>
#include <toast.h>
#include "bulletItem.h"
#include "style.h"
#include "mpvPlayer.h"
#include "playSpeed.h"
#include "volume.h"
#include "common/myLog.h"
#include "bulletEdit.h"
#include "bulletManage.h"

namespace Ui {
class PlayerPage;
}

class PlayerPage : public QWidget
{
    Q_OBJECT

// 外部函数
public:
    explicit PlayerPage(QWidget *parent = nullptr);
    ~PlayerPage();
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void startPlay(const QString& videoPath);

// 内置函数
private:
    void moveVolumeWindow(const QPoint& point);
    void moveSpeedWindow(const QPoint& point);
    void initConnect();
    QString secondToTime(double seconds);

// 信号
private slots:
    // 点击 弹出 窗口
    void onVolumeBtnClicked();
    void onPlaySpeedBtnClicked();
    void onPlayBtnClicked();
    void onPlaySpeedChanged(double speed);
    void onVolumeChanged(int volume);
    void onPlayPositionChanged(double playTime);
    void onPlayPositionDraged(double ratio);
    void onMedioLoaded(double total_time);
    void onMedioFinished();
    void onBulletScreenBtnClicked();
    void onAcceptSignalsByBulletEdit(const QString& str);

private:
    Ui::PlayerPage *ui;
    QPoint dragPos;
    Volume* volume;
    PlaySpeed* speedCtl;
    BulletEdit* bulletEdit;
    MpvPlayer* mpvPlayer = nullptr;
    bool isPlaying = false;
    bool isShowBullet =true;
    double playTime;
    double totalTime;
    QString videoPath;
    std::unique_ptr<BulletManage> bm;
    int lastSecondsForBullet;
    QShortcut* shortCut;
    // 左边是播放时间 右边是弹幕列表

};


