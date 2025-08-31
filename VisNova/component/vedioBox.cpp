#include "vedioBox.h"
#include "ui_vedioBox.h"
#include "common/myLog.h"

VedioBox::VedioBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VedioBox)
{
    ui->setupUi(this);
    ui->delVedioBtn->hide(); // 隐藏删除按钮

    ui->imageBox->installEventFilter(this);
    ui->vedioTitleBox->installEventFilter(this);
}

VedioBox::~VedioBox()
{
    delete ui;
}

// 事件 过滤器
bool VedioBox::eventFilter(QObject *watched, QEvent *event)
{
    if(ui->imageBox == watched || ui->vedioTitleBox == watched)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            // 显示 播放窗口
            LOG()<<"[suc] 播放视频...";
            return true;
        }
    }

    // 如果希望 完全拦截 可以返回 true
    return QObject::eventFilter(watched,event);
}
















