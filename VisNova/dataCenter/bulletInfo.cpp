#include "bulletInfo.h"

namespace model{

void model::BulletInfo::loadBarrageInfo(const QJsonObject &barrage_object_info)
{

    // QString barrageId; // 弹幕id
    // QString userId; // 用户id
    // double playTime; //
    // QString text;
    barrageId = barrage_object_info["barrageId"].toString();
    userId = barrage_object_info["userId"].toString();
    playTime = barrage_object_info["playTime"].toInteger();
    text = barrage_object_info["text"].toString();
}

};
