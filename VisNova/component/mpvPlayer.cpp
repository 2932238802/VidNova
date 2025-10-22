#include "mpvPlayer.h"

///
/// \brief wakeUp
/// \param ctx
/// 必须是静态函数 作为回调函数
static void wakeUp(void * ctx)
{
    MpvPlayer* mpv = (MpvPlayer*)ctx;
    emit mpv->mpvEvents();
}


/// \brief MpvPlayer::MpvPlayer
/// \param parent
/// \param videoRenderWnd
/// 构造
MpvPlayer::MpvPlayer(QWidget* videoRenderWnd,QObject *parent)
    : QObject{parent}
{
    std::setlocale(LC_NUMERIC,"c"); // 使用C标准

    // 创建 mpv 实例
    mpv = mpv_create();
    if(nullptr == mpv)
    {
        LOG()<<"[err] mpv 实例创建失败";
    }

    // 设置 视频的渲染窗口
    // 将 窗口的id 给 mpv
    // 本质是一个 句柄 在windows
    if(videoRenderWnd)
    {
        int64_t wid_handle = videoRenderWnd->winId();
        mpv_set_option(mpv,"wid",MPV_FORMAT_INT64,&wid_handle);
    }else{
        // 不需要 播放视频
        // 禁止视频画面输出
        // 音频的输出
        mpv_set_option_string(mpv,"vo","null");
        mpv_set_option_string(mpv,"ao","null");
    }


    // 订阅time-pos属性
    //  调用libmpv核心函数 订阅一个属性
    // 在time_pos 这个属性发生任何变化的时候 通知我
    mpv_observe_property(mpv,0,"time-pos",MPV_FORMAT_DOUBLE);
    mpv_observe_property(mpv,0,"duration",MPV_FORMAT_DOUBLE);


    // 设置 mpv 事件触发的回调函数
    mpv_set_wakeup_callback(mpv,wakeUp,this);

    // 槽函数绑定
    connect(this,&MpvPlayer::mpvEvents,this,&MpvPlayer::onMpvEvents);

    if(mpv_initialize(mpv) < 0)
    {
        LOG()<<"[err] mpv 初始化失败...";
        mpv_terminate_destroy(mpv);
        mpv = nullptr;
        return;

    }

}


void MpvPlayer::startPlay(const QString &videoPath)
{

    LOG()<<"[inf] videoPath" << videoPath;
    // 发送加载视频地命令 然后播放视频
    // 因为 QString 内部实现的细节是 UTF-16
    const QByteArray fileName = videoPath.toUtf8();
    // c语言的工作 支持 NULL 但是 C++的规范 更适合的是 nullptr
    // data() 是返回一个 const char* 的指针
    const char *args[] = {"loadfile",fileName.data(),nullptr};

    // 这里异步处理 会有个 问题 就是 args 里面的 data 可能指向一个空
    mpv_command(mpv,args);

}

void MpvPlayer::setSpeed(double speed)
{
    mpv_set_property(mpv,"speed",MPV_FORMAT_DOUBLE,&speed);
}

void MpvPlayer::play()
{
    // 0 是开始 0一般是关 关掉暂停状态 就是 开始 ~
    int flag = 0;
    mpv_set_property(mpv,"pause",MPV_FORMAT_FLAG,&flag);
}

void MpvPlayer::pause()
{
    int flag = 1;
    mpv_set_property(mpv, "pause", MPV_FORMAT_FLAG,&flag);
}

void MpvPlayer::mute(bool isMute)
{
    int flag = isMute? 1:0;
    mpv_set_property(mpv,"mute",MPV_FORMAT_FLAG,&flag);
}

/// \brief MpvPlayer::setVolume
/// \param volume
/// 音量调节
/// volume 就是一个 音量的大小
void MpvPlayer::setVolume(int64_t volume)
{
    mpv_set_property(mpv,"volume",MPV_FORMAT_INT64,&volume);
}

/// \brief MpvPlayer::setTimePos
/// \param timePos
/// 设置时间位置
void MpvPlayer::setTimePos(double timePos)
{
    if(!mpv)
    {
#ifdef MPVPLAYER_TEST
        LOG()<<"[inf] mpv是空";
#endif
        return;
    }
    QString timeStr = QString::number(timePos);
    const char* cmd[] = {"seek",qPrintable(timeStr),"absolute",nullptr};
    mpv_command(mpv,cmd);
}

double MpvPlayer::getPlayTotalTime() const
{
    if(!mpv)
    {
#ifdef MPVPLAYER_TEST
        LOG()<<"[inf] mpv是空";
#endif
        return 0.0;
    }
    double duration = 0.0;
    mpv_get_property(mpv,"duration",MPV_FORMAT_DOUBLE,&duration);
    return duration;
}
////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
/// \brief MpvPlayer::getVideoFirstPage
/// \param video_path
/// \return
///
QString MpvPlayer::getVideoFirstPage(const QString &video_path)
{
    QString curPath = QDir::currentPath();
    QDir dir(QDir::currentPath());
    dir.cdUp();
    dir.cdUp();
    QString ffmpegPath = dir.path() + "/ffmpeg/ffmpeg.exe";

    QString filePath = curPath += "/firstFrame.png" ;

    QStringList cmds;
    cmds << "-y"
         << "-ss"
         << "00:00:00"
         << "-i"
         << video_path
         <<"-vframes"
         << "1"
         << filePath;

    // 创建进程
    QProcess ffmpegProgress;
    ffmpegProgress.start(ffmpegPath,cmds);

    // -1 就是无限等待
    if(ffmpegProgress.waitForFinished(-1))
    {
        if(ffmpegProgress.exitCode() == 0)
        {
#ifdef MPVPLAYER_TEST
            LOG()<<"成功生成截图";
            return filePath;
#endif
        } else {

#ifdef MPVPLAYER_TEST
            LOG() << "ffmpeg 进程执行失败，退出码: " << ffmpegProgress.exitCode();
            LOG() << "错误详情: " << ffmpegProgress.readAllStandardError();
#endif
            return "";
        }
#ifdef MPVPLAYER_TEST
        LOG()<<"进程执行失败...";
        return "";
#endif
    }else {

#ifdef MPVPLAYER_TEST
        LOG() << "等待 ffmpeg 进程时出错: " << ffmpegProgress.errorString();
#endif

        return "";
    }
}
////////////////////////////////////////////////////////





////////////////////////////////////////////////////////
/// \brief MpvPlayer::handleMpvEvent
/// \param event
void MpvPlayer::handleMpvEvent(mpv_event *event)
{
    switch (event->event_id)
    {
        case MPV_EVENT_PROPERTY_CHANGE:
        {
            mpv_event_property* eventProperty = (mpv_event_property*)event->data;
            if(eventProperty->data == nullptr)
            {
                break;
            }
            if(0 == strcmp(eventProperty->name,"time-pos"))
            {
                // time-pos 属性: 播放时间发生改变
                double seconds = *((double*)eventProperty->data);
                // 发生信号 通知界面更新 当前时间

                emit playPositionSignals(seconds);
            }
            else if(0 == strcmp(eventProperty->name,"duration"))
            {
                double durationSeconds = *((double*)eventProperty->data);
                int durationInt = static_cast<int>(durationSeconds);
                emit _duration(durationInt);
            }
            break;
        }
        case MPV_EVENT_SHUTDOWN: // 关闭信号
        {
            mpv_terminate_destroy(mpv);
            mpv = nullptr;
            break;
        }
        default:
        {
            break;
        }
    }
}
////////////////////////////////////////////////////////




////////////////////////////////////////////////////////
/// \brief MpvPlayer::onMpvEvents
///
void MpvPlayer::onMpvEvents()
{
    while(mpv)
    {
        // 循环处理 所有地
        mpv_event* mpvEvent =  mpv_wait_event(mpv,0);

        if(mpvEvent->event_id == MPV_EVENT_NONE)
        {
            // 表示没有任何地事件
            break;
        }
        else if(mpvEvent->event_id == MPV_EVENT_FILE_LOADED)
        {
            emit medioLoaded(getPlayTotalTime());
        }
        else if(mpvEvent->event_id == MPV_EVENT_END_FILE)
        {
            emit medioFinished();
        }
        handleMpvEvent(mpvEvent);
    }
}
////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
/// \brief MpvPlayer::~MpvPlayer
/// 析构函数
MpvPlayer::~MpvPlayer()
{
    if(mpv)
    {
        mpv_terminate_destroy(mpv);
    }
}
////////////////////////////////////////////////////////

