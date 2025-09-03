#include "playerPage.h"
#include "ui_playerPage.h"

PlayerPage::PlayerPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerPage)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_ShowModal); // 模块化的方式 进行展示

    volume = new Volume(this);
    speedCtl = new PlaySpeed(this);

    //
    connect(ui->minBtn,&QPushButton::clicked,this,&QWidget::showMinimized);
    connect(ui->quitBtn,&QPushButton::clicked,this,&QWidget::close);
    connect(ui->volumeBtn,&QPushButton::clicked,this,&PlayerPage::onVolumeBtnClicked);
    connect(ui->speedBtn,&QPushButton::clicked,this,&PlayerPage::onPlaySpeedBtnClicked);
}


// 重写按钮
void PlayerPage::mousePressEvent(QMouseEvent *event)
{
    // 获取位置 相对于 播放 界面的位置
    QPoint point = event->position().toPoint();
    if(ui->playerHead->geometry().contains(point))
    {
        if(event->button() == Qt::LeftButton)
        {
            // 鼠标左键
            // 计算 鼠标按下之后的全局坐标 和 左上角的距离
            dragPos = event->globalPosition().toPoint()-geometry().topLeft();
            return;
        }
    }

    QWidget::mousePressEvent(event);
}

void PlayerPage::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->position().toPoint();

    if(ui->playerHead->geometry().contains(point))
    {
        if(event->buttons() & Qt::LeftButton)
        {
            move(event->globalPosition().toPoint()-dragPos);
        }
    }
    QWidget::mouseMoveEvent(event);
}


///
/// \brief PlayerPage::onVolumeBtnClicked
/// 弹出 窗口 点其它地方 应该消失
void PlayerPage::onVolumeBtnClicked()
{
    // QPoint(0,0) 是相对于 组件来说的
    // mapToGlobal 转化到 全局
    QPoint windowPoint{mapToGlobal(QPoint(0,0))};
    moveVolumeWindow(windowPoint);

    LOG()<<"[info] show 音量设置...";
    volume->show();
}

///
/// \brief PlayerPage::onPlaySpeedBtnClicked
///
void PlayerPage::onPlaySpeedBtnClicked()
{
    QPoint windowPoint{mapToGlobal(QPoint(0,0))};
    moveSpeedWindow(windowPoint);
    speedCtl->show();
}


void PlayerPage::moveVolumeWindow(const QPoint &point)
{
    // 设置好 音量的位置
    QPoint newPoint = point + QPoint(this->width() - volume->width()-13,533);
    volume->move(newPoint);
}

void PlayerPage::moveSpeedWindow(const QPoint &point)
{
    QPoint newPoint = point + QPoint(this->width() - speedCtl->width()-77,565);
    speedCtl->move(newPoint);
}


PlayerPage::~PlayerPage()
{
    delete ui;
}





