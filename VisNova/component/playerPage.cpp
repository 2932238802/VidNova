#include "playerPage.h"
#include "ui_playerPage.h"

/////////////////////////////////////////////////////////
/// \brief PlayerPage::PlayerPage
/// \param parent
///
PlayerPage::PlayerPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerPage)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    isPlaying = false;
    playTime = 0.0;
    totalTime = 0.0;
    videoPath = "";
    lastSecondsForBullet = 0;
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_ShowModal);
    volume = new Volume(this);
    speedCtl = new PlaySpeed(this);
    mpvPlayer = new MpvPlayer(ui->playerMid);
    shortCut = new QShortcut(ui->playBtn);
    QKeySequence keySequence(" ");
    shortCut->setKey(keySequence);
    initBullet();
    initConnect();
}
/////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////
/// \brief PlayerPage::initBullet
///
void PlayerPage::initBullet()
{
    if(bm==nullptr)
    {
        QPoint point = mapToGlobal(QPoint(0,0));
        bm = std::make_unique<BulletManage>(this,point.x(),point.y() + ui->playerHead->height());
    }
}
/////////////////////////////////////////////////////////



////////////////////////////////////////////////
void PlayerPage::mousePressEvent(QMouseEvent *event)
{
    // 获取位置 相对于 播放 界面的位置
    QPoint point = event->position().toPoint(); // 这个是相对内部的坐标
    if(ui->playerHead->geometry().contains(point))
    {
        if(event->button() == Qt::LeftButton)
        {
            // 鼠标左键
            // 计算 鼠标按下之后的全局坐标 和 左上角的距离
            //
            dragPos = event->globalPosition().toPoint()-geometry().topLeft();
            return;
        }
    }
    QWidget::mousePressEvent(event);
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::mouseMoveEvent
/// \param event
///
void PlayerPage::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->position().toPoint();

    if(ui->playerHead->geometry().contains(point))
    {
        if(event->buttons() & Qt::LeftButton)
        {
            // 点击(全) - 左上角(全) = dragPos
            // 移动到点击的位置就是 点击(全) - dragPos = 左上角(全)
            move(event->globalPosition().toPoint()-dragPos);

            // 移动弹幕的相关位置
            QPoint point = geometry().topLeft();
            point.setY(point.ry()+ui->playerHead->height());
            bm->move(point);
        }
    }
    QWidget::mouseMoveEvent(event);
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::onVolumeBtnClicked
/// 弹出 窗口 点其它地方 应该消失
void PlayerPage::onVolumeBtnClicked()
{
    // QPoint(0,0) 是相对于 组件来说的
    // mapToGlobal 转化到 全局
    QPoint windowPoint{mapToGlobal(QPoint(0,0))};
    moveVolumeWindow(windowPoint);

#ifdef PLAYERPAGE_TEST_FOR_BULLET
    LOG()<<"[info] show 音量设置...";
#endif

    volume->show();
}
////////////////////////////////////////////////


////////////////////////////////////////////////
/// \brief PlayerPage::onPlaySpeedBtnClicked
void PlayerPage::onPlaySpeedBtnClicked()
{
    QPoint windowPoint{mapToGlobal(QPoint(0,0))};
    moveSpeedWindow(windowPoint);
    speedCtl->show();
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::onPlayBtnClicked
/// 点击 播放 按钮
void PlayerPage::onPlayBtnClicked()
{
    isPlaying = !isPlaying;
    // 进入 循环 说明了 就是播放状态
    if(isPlaying)
    {
        mpvPlayer->play();
        bm->setBulletStateForHide(false); // 表示不隐藏
        ui->playBtn->setStyleSheet(PLAYER_BEGIN_STYLE);
    }
    else{
        mpvPlayer->pause();
        bm->setBulletStateForHide(true); // 表示不隐藏
        ui->playBtn->setStyleSheet(PLAYER_STOP_STYLE);
    }
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::onPlaySpeedChanged
/// \param speed
///
void PlayerPage::onPlaySpeedChanged(double speed)
{
    mpvPlayer->setSpeed(speed);
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::onVolumeChanged
/// \param volume
/// 音量改变
void PlayerPage::onVolumeChanged(int volume)
{
    mpvPlayer->setVolume(volume);
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::onPlayPositionChanged
/// \param playTime
void PlayerPage::onPlayPositionChanged(double play_time)
{
    if(totalTime <= 0) return;
    playTime = play_time;
    QString curTime = secondToTime(play_time);
    QString totalTimeStr = secondToTime(totalTime);
    ui->videoDuration->setText(curTime + "/" + totalTimeStr);
    double ratio = play_time / totalTime;
    ui->videoSlider->setPlayStepByTimeStep(ratio); // 设置进度条

    int curTimeSecond = static_cast<int>(play_time);
    if(curTimeSecond > lastSecondsForBullet)
    {
        bm->showBulletBySecond(curTimeSecond);
        lastSecondsForBullet = curTimeSecond;
    }

}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::onPlayPositionDraged
/// \param ratio
/// 拖拽进度条
void PlayerPage::onPlayPositionDraged(double ratio)
{
    QString totalTimeStr = secondToTime(totalTime);
    double curTime = ratio * totalTime;
    QString cutTimeToStr = secondToTime(curTime);
    mpvPlayer->setTimePos(curTime);
    ui->videoDuration->setText(cutTimeToStr + "/" + totalTimeStr);
    ui->videoSlider->setPlayStepByTimeStep(ratio);
}
////////////////////////////////////////////////



////////////////////////////////////////////////
void PlayerPage::onMedioLoaded(double total_time)
{
#ifdef PLAYERPAGE_TEST
    LOG()<<"总时长"<<total_time;
#endif
    totalTime = total_time;
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::onMedioFinished
///
void PlayerPage::onMedioFinished()
{
    // 结束了 首先是
    // mpvPlayer->startPlay(videoPath);
    // isPlaying = !isPlaying;
    isPlaying = false;
    // mpvPlayer->pause();
    ui->playBtn->setStyleSheet(PLAYER_STOP_STYLE);
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::onBulletScreenBtnClicked
///
void PlayerPage::onBulletScreenBtnClicked()
{
    // 一开始表示的 isShowBullet 就是true
    // 点击完 应该是 隐藏 所以这里 isShowBullet因为! 变成了 false
    isShowBullet = !isShowBullet;
    if(isShowBullet)
    {
        // 打开弹幕
        ui->bulletScreenBtn->setStyleSheet(BULLETBTN_SHOW);
        bm->setBulletStateForHide(false);
        bm->show();
    }
    else{
        // 关闭弹幕
        ui->bulletScreenBtn->setStyleSheet(BULLETBTN_CLOSE);
        bm->setBulletStateForHide(true);
        bm->hide();
    }
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::onAcceptSignalsByBulletEdit
/// \param str
void PlayerPage::onAcceptSignalsByBulletEdit(const QString& str)
{
    if(!isShowBullet){
        Toast::showMsg("请打开弹幕开关...");
        return ;
    }
    BulletItem* item = bm->buildBullet(BulletPosition::TOP);
    item->setText(str);

    item->startAnimation();
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::moveVolumeWindow
/// \param point
/// 移动音量
void PlayerPage::moveVolumeWindow(const QPoint &point)
{
    // 设置好 音量的位置
    QPoint newPoint = point + QPoint(this->width() - volume->width()-13,533);
    volume->move(newPoint);
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::moveSpeedWindow
/// \param point
/// 音量
void PlayerPage::moveSpeedWindow(const QPoint &point)
{
    QPoint newPoint = point + QPoint(this->width() - speedCtl->width()-77,565);
    speedCtl->move(newPoint);
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::secondToTime
/// 转化成时间
QString PlayerPage::secondToTime(double seconds)
{
    QString time;
    int seconds_int = static_cast<int>(seconds);
    int hour = seconds_int / 3600;
    int remain = seconds_int % 3600;
    int minute = remain/60;
    int second = remain % 60;

    if(hour)
    {
        time += QString::asprintf("%02d:",hour);
    }
    time += QString::asprintf("%02d:%02d",minute,second);
    return time;
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// 开始播放
/// \brief PlayerPage::startPlay
/// \param videoPath
void PlayerPage::startPlay(const QString &video_path)
{
#ifdef PLAYERPAGE_TEST_FOR_BULLET
    bm->buildBulletItems();
    LOG()<<"[inf] enter function startPlay";
#endif
    videoPath = video_path;
    mpvPlayer->startPlay(video_path);
    mpvPlayer->pause();
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::initConnect
/// 初始化 所有的连接
void PlayerPage::initConnect()
{
    connect(ui->minBtn,&QPushButton::clicked,this,&QWidget::showMinimized);
    connect(ui->quitBtn,&QPushButton::clicked,this,&QWidget::close);
    connect(ui->volumeBtn,&QPushButton::clicked,this,&PlayerPage::onVolumeBtnClicked);
    connect(ui->speedBtn,&QPushButton::clicked,this,&PlayerPage::onPlaySpeedBtnClicked);
    connect(ui->playBtn,&QPushButton::clicked,this,&PlayerPage::onPlayBtnClicked);
    connect(speedCtl,&PlaySpeed::speedSignals,this,&PlayerPage::onPlaySpeedChanged);
    connect(volume,&Volume::volumeSignals,this,&PlayerPage::onVolumeChanged);
    connect(mpvPlayer,&MpvPlayer::playPositionSignals,this,&PlayerPage::onPlayPositionChanged);
    connect(ui->videoSlider ,&PlayerSlider::onPlayTimeDrag,this , &PlayerPage::onPlayPositionDraged);
    connect(mpvPlayer,&MpvPlayer::medioLoaded,this,&PlayerPage::onMedioLoaded);
    connect(mpvPlayer,&MpvPlayer::medioFinished,this,&PlayerPage::onMedioFinished);
    connect(shortCut,&QShortcut::activated,this,&PlayerPage::onPlayBtnClicked);
    connect(ui->bulletScreenBtn,&QPushButton::clicked,this,&PlayerPage::onBulletScreenBtnClicked);
    connect(ui->bulletScreenText,&BulletEdit::sendBullet,this,&PlayerPage::onAcceptSignalsByBulletEdit);
}
////////////////////////////////////////////////



////////////////////////////////////////////////
/// \brief PlayerPage::~PlayerPage
/// 析构函数
PlayerPage::~PlayerPage()
{
    delete ui;
}
////////////////////////////////////////////////





