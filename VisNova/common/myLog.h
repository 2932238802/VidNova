#pragma once
#include<QString>
#include<QFileInfo>
#include<qDebug>

// 封装一个 日志
inline static QString getFileName(const QString& path)
{
    QFileInfo fileInfo(path);
    return fileInfo.fileName();
}
#define TAG QString("[%1,%2]").arg(getFileName(__FILE__),QString::number(__LINE__))
#define LOG() qDebug().noquote()<<TAG

#define DEBUG

#ifdef DEBUG

#define NETCLIENT_TEST

// #define MYPAGE_TEST

#define PLAYERPAGE_TEST
// #define PLAYERPAGE_TEST_FOR_VOLUMN
// #define PLAYERPAGE_TEST_FOR_BULLET

// #define MPVPLAYER_TEST

// #define HTTP_TEST

// #define PAGE_SLIDER_TEST

#define HOMEPAGECPT_TEST

// #define VIDEOINFO_TEST

// #define DATACENTER_TEST

#define VIDEOBOX_TEST //

#define NETCLIENT_TEST // 客户端界面

#define MYPAGE_TEST // 个人界面

#define DATACENTER_TEST // 数据中心

#define VIDNOVAMAIN_TEST // 主页面

#define PAGESWITCHBTN_TEST // 切换按钮

#define ATTENTIONBTN_TEST // 关注按钮

#define CONFIRM_DIALOG_TEST // 确定窗口

#define LOGIN_TEST // 登录 界面

#define USERINFO_TEST // 个人信息类 界面

#define TOAST_TEST // 弹窗界面

#define STARTPAGE_TEST // 开始界面

#define VIDEOLIST_TEST

#define BULLETEDIT_TEST

#define MODIFYSELFINFO_TEST

#define MODIFYPD_TEST

#define MPVPLAYER_TEST

#define UPLOADVIDEOPAGE_TEST

#define CHECKPAGEFORAP_TEST

#define CHECKPAGEFORITEM_TEST

#define ROLEPAGEFORAP_TEST

#endif

