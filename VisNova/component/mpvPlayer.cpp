#include "mpvPlayer.h"

static void wakeUp(void * ctx)
{


}


///
/// \brief MpvPlayer::MpvPlayer
/// \param parent
/// \param videoRenderWnd
/// 构造
MpvPlayer::MpvPlayer(QObject *parent,QWidget* videoRenderWnd)
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
    int64_t wid_handle = videoRenderWnd->winId();
    mpv_set_option(mpv,"wid",MPV_FORMAT_INT64,&wid_handle);

    // 设置 mpv 事件触发的回调函数
    mpv_set_wakeup_callback(mpv,wakeUp,this);

}

///
/// \brief MpvPlayer::~MpvPlayer
/// 析构函数
MpvPlayer::~MpvPlayer()
{


}

void MpvPlayer::onMpvEvents()
{

}




