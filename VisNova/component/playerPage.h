#pragma once
#include <QWidget>
#include <QMouseEvent>
#include "style.h"
#include "mpvPlayer.h"
#include "playSpeed.h"
#include "volume.h"
#include "common/myLog.h"
#include "bulletEdit.h"

namespace Ui {
class PlayerPage;
}

class PlayerPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerPage(QWidget *parent = nullptr);
    ~PlayerPage();
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void startPlay(const QString& videoPath);

private:
    void moveVolumeWindow(const QPoint& point);
    void moveSpeedWindow(const QPoint& point);
    void initConnect();


private slots:
    // 点击 弹出 窗口
    void onVolumeBtnClicked();
    void onPlaySpeedBtnClicked();
    void onPlayBtnClicked();
    void onPlaySpeedChanged(double speed);
    void onVolumeChanged(int volume);
    void onPlayPositionChanged(int64_t playTime);


private:
    Ui::PlayerPage *ui;
    QPoint dragPos;
    Volume* volume;
    PlaySpeed* speedCtl;
    BulletEdit* bulletEdit;
    MpvPlayer* mpvPlayer = nullptr;
    bool isPlaying = false;
};


