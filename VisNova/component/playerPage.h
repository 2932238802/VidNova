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
#include "dataCenter/videoInfo.h"
#include "dataCenter/dataCenter.h"
#include "common/intToString.h"
#include "lrPage/login.h"

namespace Ui {
class PlayerPage;
}

class PlayerPage : public QWidget
{
    Q_OBJECT

// 外部函数
public:
    explicit PlayerPage(const model::VideoInfo& info,QWidget *parent = nullptr);
    void setUserAvatar(QPixmap &&avatar);
    void startPlay();

// 内置函数
private:
    void moveVolumeWindow(const QPoint& point);
    void moveSpeedWindow(const QPoint& point);
    void initConnect();
    void initBullet();
    QString secondToTime(double seconds);
    void updataPlayNumber();
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    ~PlayerPage();

protected:
    void closeEvent(QCloseEvent* event) override;

// 信号
private slots:
    // 点击 弹出 窗口
    void onVolumeBtnClicked();
    void onPlaySpeedBtnClicked();
    void onPlayBtnClicked();
    void onPlaySpeedChanged(double speed);
    void onVolumeChanged(int volume);
    void onPlayPositionChanged(double play_yime);
    void onPlayPositionDraged(double ratio);
    void onMedioLoaded(double total_time);
    void onMedioFinished();
    void onBulletScreenBtnClicked(); // 弹幕
    void onAcceptSignalsByBulletEdit(const QString& str);
    void isLikeBtnClicked(const QString&video_id,bool is_liked); // 这个只是个检查
    void onLikeBtnClicked();

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

    Volume* volume;
    model::VideoInfo videoInfo;
    MpvPlayer* mpvPlayer = nullptr;
    PlaySpeed* speedCtl;
    BulletEdit* bulletEdit;

};


