#pragma once
#include <QWidget>
#include <QMouseEvent>
#include "common/myLog.h"

namespace Ui {
class PlayerSlider;
}

///
/// \brief The PlayerSlider class
/// 进度条
class PlayerSlider : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerSlider(QWidget *parent = nullptr);
    void setPlayStepByTimeStep(double stepRadio); // 设置进度条 进度
    ~PlayerSlider();

private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void moveSlider();

signals:
    void onPlayTimeDrag(double ratio);

private:
    Ui::PlayerSlider *ui;
    double playProgress;
    double ratio;
    bool isDraging;
};

