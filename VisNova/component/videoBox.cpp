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

    playerPage->show();
    // 获取视频的路径

    QDir dir = QDir::current();
    // LOG()<<dir;
    dir.cdUp();
    dir.cdUp();
    QString videoPath = dir.absolutePath();
    videoPath+="/test/test1.mp4";
    playerPage->startPlay(videoPath);

    // Login* login = new Login(this);
    // // login->setWindowFlag(Qt::FramelessWindowHint,true);
    // // login->exec(); // exec
    // Toast::showMsg("用户点击了视频");

    // Toast::showMsg("先登录...",login);
#endif

}
















