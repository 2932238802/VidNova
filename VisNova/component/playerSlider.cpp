#include "playerSlider.h"
#include "ui_playerSlider.h"

PlayerSlider::PlayerSlider(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerSlider),
    playProgress(0),
    ratio(0),
    isDraging(false)
{
    ui->setupUi(this);
}

// 设置进度条的位置
// 当前 / 总 = 当前宽 / 当前总
void PlayerSlider::setPlayStepByTimeStep(double stepRadio)
{
    if(!isDraging)
    {
        playProgress = ui->inLine->width() * 1.0 * stepRadio;
        moveSlider();
    }
}

PlayerSlider::~PlayerSlider()
{
    delete ui;
}

void PlayerSlider::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) // 表示左键 暗下来
    {
        isDraging = true;
        playProgress = event->pos().x(); // 这些都是 相对于 当前得 QWidget 而言的
        moveSlider(); // 移动一下
        emit onPlayTimeDrag(ratio);
        return;
    }
    QWidget::mousePressEvent(event);
}

void PlayerSlider::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) // 表示左键 按下来
    {
        // playProgress = event->pos().x();
        // moveSlider(); // 移动一下
        // emit onPlayTimeDrag(ratio);

        isDraging = false;
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
        emit onPlayTimeDrag(ratio);
        return;
    }
    QWidget::mouseMoveEvent(event);
}

///
/// \brief PlayerSlider::moveSlider
/// 移动进度条
void PlayerSlider::moveSlider()
{
    ui->outLine->setGeometry(ui->outLine->x(),ui->outLine->y(),playProgress,ui->outLine->height());
    // TODO: 播放进度
    ratio = playProgress / ui->inLine->width();

#ifdef PAGE_SLIDER_TEST
    LOG()<<"ratio"<<ratio;
    LOG()<<"playProgress"<<playProgress;
    LOG()<<"ui->outLine->width()" << ui->outLine->width();
#endif

}





