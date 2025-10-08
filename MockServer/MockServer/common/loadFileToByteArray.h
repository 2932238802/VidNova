#pragma once
#include <QByteArray>
#include <QFile>
#include "common/mylog.h"

static inline QByteArray loadFileToByteArray(const QString& file_path)
{
    QFile file(file_path);

    bool ok = file.open(QIODevice::ReadOnly);

    if(!ok)
    {
        LOG()<<"[err]"<<"文件打开失败 "<<file_path;
        file.close();
        return QByteArray{};
    }

    QByteArray data = file.readAll();
    file.close();
    return data;
}
