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
    // 设置弹出窗口
    playerPage = new PlayerPage();
    connect(playerPage,&QWidget::destroyed,this,&VideoBox::onPlayerPageDestroyed);
}

VideoBox::~VideoBox()
{
    delete playerPage;
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
    // 还应该显示 视频的路径

#ifdef DE_TEST

    checkPlayPageIsNullptr();
    playerPage->show();
    QDir dir = QDir::current();
    dir.cdUp();
    dir.cdUp();
    QString videoPath = dir.absolutePath();
    videoPath+="/test/test1.mp4";
    playerPage->startPlay(videoPath);
#endif
}

void VideoBox::checkPlayPageIsNullptr()
{
    if(playerPage == nullptr)
    {
        LOG()<<"[err] playPage is nullptr and create a new one";
        playerPage = new PlayerPage();
        connect(playerPage,&QWidget::destroyed,this,&VideoBox::onPlayerPageDestroyed);
    }
}

void VideoBox::onPlayerPageDestroyed()
{
    playerPage = nullptr; // 把悬挂指针 置为 nullptr

}
















