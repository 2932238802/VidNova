#include"videoInfoForLoad.h"

namespace model{
void VideoInfoForLoad::loadVideoInfoFromJson(const QJsonObject &videoInfoJson)
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

    videoStatus = videoInfoJson["videoStatus"].toInt(); // 视频状态

    checkerId = videoInfoJson["checkerId"].toString(); // 审核管理员的Id

    checkerName = videoInfoJson["checkerName"].toString(); // 审核管理员的名字

    checkAvatarId = videoInfoJson["checkAvatarId"].toString(); // 审核管理员的图像Id

#ifdef VIDEOINFO_TEST
        QJsonDocument doc(videoInfoJson);
        QByteArray fromat = doc.toJson(QJsonDocument::Indented);
        LOG () << QString(fromat);
#endif
    }



}
















