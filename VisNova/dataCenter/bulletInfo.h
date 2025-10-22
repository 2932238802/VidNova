#pragma once
#include <QObject>
#include <QJsonObject>

namespace model{

class BulletInfo{
public:
    QString barrageId; // 弹幕id
    QString userId; // 用户id
    int64_t playTime; //
    QString text;

public:
    void loadBarrageInfo(const QJsonObject& barrage_object_info);
};

}
