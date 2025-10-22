#pragma once
#include <QString>
#include <QList>

namespace model{
/////////////////////
/// \brief The VideoInfoForUpload class
/// 个人 上传视频的信息
class VideoInfoForUpload
{

public:
    VideoInfoForUpload();
    QString videoFileId;
    QString photoFileId;
    QString videoTitle;
    QString videoDesc;
    QString kind;
    QList<QString> tags;
    int64_t duration;

};
}

