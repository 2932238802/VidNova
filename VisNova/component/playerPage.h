#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <QShortcut>
#include <QFrame>
#include <QDialog>
#include <memory.h>
#include <toast.h>
#include "vidnovamain.h"
#include "bulletItem.h"
#include "style.h"
#include "mpvPlayer.h"
#include "playSpeed.h"
#include "volume.h"
#include "common/myLog.h"
#include "bulletEdit.h"
#include "bulletManage.h"
#include "dataCenter/videoInfoForLoad.h"
#include "dataCenter/dataCenter.h"
#include "common/intToString.h"
#include "lrPage/login.h"

namespace Ui {
class PlayerPage;
}


enum PlayerMode{
    InView = 1,
    Shelve = 2
};


class PlayerPage : public QWidget
{
    Q_OBJECT

// 外部函数
public:
    explicit PlayerPage(const model::VideoInfoForLoad& info,QWidget *parent = nullptr,PlayerMode needBullet = PlayerMode::Shelve );
    void setUserAvatar(QPixmap avatar);
    void startPlay();
    // 析构
    ~PlayerPage();

// 内置函数
private:
    void initConnect();
    void initBullet();
    void setupForMode();

    bool loginCheck();

    // 音量大小的位置设置
    void moveVolumeWindow(const QPoint& point);

    // 视频播放速度的大小 位置设置
    void moveSpeedWindow(const QPoint& point);

    // 时间格式化 调整的设置
    QString secondToTime(double seconds);

    // 播放次数的设置
    void updataPlayNumber();

    // 屏幕拖拽逻辑的重写
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

protected:
    void closeEvent(QCloseEvent* event) override;

// 信号
private slots:
    // 点击 弹出 窗口
    void onVolumeBtnClicked();

    // 播放速度按钮 点击与拖拽
    void onPlaySpeedBtnClicked();
    void onPlaySpeedChanged(double speed);

    // 播放按钮的点击触发的槽函数
    void onPlayBtnClicked();

    // 音量改变触发的槽函数
    void onVolumeChanged(int volume);

    // 播放位置的改变触发的槽函数
    void onPlayPositionChanged(double play_yime);
    void onPlayPositionDraged(double ratio);

    // 视频加载好 之后触发的槽函数
    void onMedioLoaded(double total_time);

    // 视频结束后 触发的槽函数
    void onMedioFinished();

    // 弹幕 弹幕按钮 点击 隐藏弹幕
    void onBulletScreenBtnClicked();
    void onAcceptSignalsByBulletEdit(const QString& str);

    // 点赞逻辑处理
    void isLikeBtnClicked(const QString&video_id,bool is_liked); // 这个只是个检查
    void onLikeBtnClicked();

    // 用户头像点击触发的槽函数
    void onAvatarClicked();


signals:
    void _updateLikeNumber(int64_t like_count);


private:
    Ui::PlayerPage *ui;
    QString videoPath;
    QPoint dragPos;
    QShortcut* shortCut;
    QPixmap userAvatar;

    bool isPlaying = false;
    bool isShowBullet =true;
    bool isLikedBefore = false;
    bool isLikedAfter = false;

    int lastSecondsForBullet;
    double playTime;
    double totalTime;
    std::unique_ptr<BulletManage> bm;


    PlayerMode l_mode;
    Volume* volume;
    model::VideoInfoForLoad videoInfo;
    MpvPlayer* mpvPlayer = nullptr;
    PlaySpeed* speedCtl;
    BulletEdit* bulletEdit;

};


