#include "videoBox.h"
#include "ui_videoBox.h"


VideoBox::VideoBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoBox)
{
    ui->setupUi(this);
    ui->delVedioBtn->hide(); // 隐藏删除按钮
    ui->imageBox->installEventFilter(this);
    ui->vedioTitleBox->installEventFilter(this);

}

VideoBox::~VideoBox()
{

    delete ui;
}

// 事件 过滤器
bool VideoBox::eventFilter(QObject *watched, QEvent *event)
{
    // 只要是
    if(ui->imageBox == watched || ui->vedioTitleBox == watched)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            // 显示 播放窗口
            onPlayBtnClicked();
            return true;
        }
    }
    // 如果希望 完全拦截 可以返回 true
    return QObject::eventFilter(watched,event);
}

void VideoBox::onPlayBtnClicked()
{
    LOG()<<"[suc] 播放视频...";
    QDir dir = QDir::current();
    dir.cdUp();
    dir.cdUp();
    QString videoPath = dir.absolutePath();
    videoPath+="/test/test1.mp4";
    emit openPlayerPage(videoPath);
}
















