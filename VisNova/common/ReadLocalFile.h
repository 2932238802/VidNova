#pragma once
#include <QString>
#include <QFile>
#include <QPixmap>
#include <QIcon>
#include "common/myLog.h"
#include <QPainter>
#include <QPainterPath>

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


static inline void writeByteArrayToFile(const QString& file_path,const QByteArray& data)
{
    QFile file(file_path);
    bool ok = file.open(QIODevice::ReadWrite);
    if(!ok)
    {
        LOG()<<"[err]"<<"文件打开失败 "<<file_path;
        file.close();
        return;
    }
    file.write(data);
    file.flush();
    file.close();
}


static inline QIcon makeIcon(const QByteArray& data,int width , int height)
{
    QPixmap qpixMap;
    qpixMap.loadFromData(data);

    if(qpixMap.isNull())
    {
        return QIcon{};
    }

    // IgnoreAspectRatio 忽略 图片的比率
    qpixMap = qpixMap.scaled(width,height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    // 画布
    QPixmap canvas(qpixMap.size());
    canvas.fill(Qt::transparent);
    QPainter pen(&canvas);
    pen.setRenderHint(QPainter::Antialiasing);

    // 创建一个 圆形的部件
    QPainterPath path;
    path.addEllipse(0,0,width,height);
    pen.setClipPath(path);
    pen.drawPixmap(0,0,qpixMap);
    return  QIcon(canvas);
}










