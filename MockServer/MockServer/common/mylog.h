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

