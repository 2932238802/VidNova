#pragma once
#include <QString>

static const QString stringToTime(int64_t duration)
{
    QString timer_;

    if(duration / 3600 > 0 )
    {
        timer_ +=  QString::asprintf("%02lld:",duration%3600);
    }

    timer_  += QString::asprintf("%02lld:%02lld",duration/60,duration%60);

    return timer_;
}
