#pragma once
#include <QString>

class BulletInfo{
public:
    QString userId;
    QString bulletId;
    int64_t playTime;
    QString text;

    ///////////////////
    /// \brief BulletInfo
    /// \param user_id
    /// \param play_time
    /// \param text_
    /// 默认构造
    BulletInfo(const QString& user_id = "",int64_t play_time = 0, const QString& text_ = ""):
        userId(user_id),
        playTime(play_time),
        text(text_){
    }
};
