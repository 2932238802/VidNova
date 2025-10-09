#include"videoInfo.h"

namespace model{
void VideoInfo::loadVideoInfoFromJson(const QJsonObject &videoInfoJson)
{

        videoId = videoInfoJson["videoId"].toString();
        userId = videoInfoJson["userId"].toString();
        userAvatarId= videoInfoJson["userAvatarId"].toString();
        videoFileId= videoInfoJson["videoFileId"].toString();
        photoId= videoInfoJson["photoId"].toString();
        nickName= videoInfoJson["nickname"].toString();
        likeCount= videoInfoJson["likeCount"].toInteger();
        playCount= videoInfoJson["playCount"].toInteger();
        videoSize= videoInfoJson["videoSize"].toInteger();
        videoDesc= videoInfoJson["videoDesc"].toString();
        videoTitle= videoInfoJson["videoTitle"].toString();
        videoDuration= videoInfoJson["videoDuration"].toInteger();
        loadupTime= videoInfoJson["loadupTime"].toString();

#ifdef VIDEOINFO_TEST
        QJsonDocument doc(videoInfoJson);
        QByteArray fromat = doc.toJson(QJsonDocument::Indented);
        LOG () << QString(fromat);
#endif
    }



}
















