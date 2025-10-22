#pragma once

#include <QObject>
#include <QString>
#include <QHash>
#include <QList>
#include <QMap>

namespace model
{
class KindAndTags{
public:
    KindAndTags();
    const QList<QString> getAllKinds() const; // 获取所有的分类
    const QHash<QString,int> getAllLabels(const QString& kind) const; // 获取所有的标签
    int getKindId(const QString& kind_name) const;
    int getTagId(const QString& kind_name,const QString& tag_name) const;

private:
    // 分类 这个int 就是对应的 id 用于服务器
    QHash<QString,int> kinds;
    QHash<QString,QHash<QString,int>> tags;
    static int id;
};
};
