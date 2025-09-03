#pragma once
#include <QWidget>
#include <QMouseEvent>
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

private:
    void moveVolumeWindow(const QPoint& point);
    void moveSpeedWindow(const QPoint& point);

private slots:
    // 点击 弹出 窗口
    void onVolumeBtnClicked();
    void onPlaySpeedBtnClicked();

private:
    Ui::PlayerPage *ui;
    QPoint dragPos;
    Volume* volume;
    PlaySpeed* speedCtl;
    BulletEdit* bulletEdit;
};


