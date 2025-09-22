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

#ifdef DE_TEST
    Login* login = new Login(this);
    // login->setWindowFlag(Qt::FramelessWindowHint,true);
    // login->exec(); // exec
    Toast::showMsg("用户点击了视频");

    Toast::showMsg("先登录...",login);
#endif
    // playerPage->show();
}
















