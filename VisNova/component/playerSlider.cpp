#include "playerSlider.h"
#include "ui_playerSlider.h"

PlayerSlider::PlayerSlider(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerSlider),
    playProgress(0)
{
    ui->setupUi(this);
}

PlayerSlider::~PlayerSlider()
{
    delete ui;
}

void PlayerSlider::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) // 表示左键 暗下来
    {
        playProgress = event->pos().x(); // 这些都是 相对于 当前得 QWidget 而言的
        moveSlider(); // 移动一下
        return;
    }

    QWidget::mousePressEvent(event);
}

void PlayerSlider::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) // 表示左键 暗下来
    {
        playProgress = event->pos().x();
        moveSlider(); // 移动一下
        return;
    }

    QWidget::mouseReleaseEvent(event);
}

void PlayerSlider::mouseMoveEvent(QMouseEvent *event)
{
    if(this->geometry().contains(event->pos()) && event->button() == Qt::LeftButton) // 表示左键 暗下来
    {
        playProgress = event->pos().x();
        int width = this->width();
        if(playProgress < 0) playProgress = 0;
        if(playProgress > width) playProgress = width;
        moveSlider(); // 移动一下
        return;
    }

    QWidget::mouseMoveEvent(event);
}

void PlayerSlider::moveSlider() const
{
    ui->outLine->setGeometry(ui->outLine->x(),ui->outLine->y(),playProgress,ui->outLine->height());
    // TODO: 播放进度
}





