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

#define VIDEOBOX_TEST

#define NETCLIENT_TEST


