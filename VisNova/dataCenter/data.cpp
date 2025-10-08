#include"data.h"

namespace model{
int KindAndTags::id = 10000;

model::KindAndTags::KindAndTags()
    {
        // 初始化 种类
        QList<QString> kindsInit = {"历史","美食","音乐","游戏","其它","运动","科技","旅行","电影"};
        for(auto kind : kindsInit)
        {
            kinds.insert(kind,id++);
        }

        // 初始化 标签
        QMap<QString, QList<QString>> data;
        data["历史"] = {"中国历史", "世界历史", "历史人物", "近代史", "古代史"};
        data["美食"] = {"家常菜", "烘焙", "甜点", "地方小吃", "美食探店"};
        data["音乐"] = {"流行", "古典", "摇滚", "电子", "民谣", "说唱"};
        data["游戏"] = {"单机游戏", "网络游戏", "手游", "游戏攻略", "电竞"};
        data["其它"] = {};
        data["运动"] = {"健身", "篮球", "足球", "跑步", "瑜伽"};
        data["科技"] = {"数码产品", "人工智能", "编程", "互联网", "前沿科技"};
        data["旅行"] = {"国内游", "出境游", "旅游攻略", "穷游", "自驾游"};
        data["电影"] = {"科幻", "喜剧", "爱情", "悬疑", "纪录片", "经典电影"};

        for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
            const QString& kind_name = it.key();
            const QList<QString>& tag_names = it.value();
            this->kinds.insert(kind_name, id++);
            QHash<QString, int> tmp_tags;
            long long tagId = 1;
            for (const QString& tag_name : tag_names) {
                tmp_tags.insert(tag_name, tagId);
                tagId <<= 1;
            }
            this->tags.insert(kind_name, tmp_tags);
        }
    }

    const QList<QString> KindAndTags::getAllKinds() const
    {
        return kinds.keys();
    }

    const QHash<QString, int> KindAndTags::getAllLabels(const QString &kind) const
    {
        return tags[kind];
    }


    int KindAndTags::getKindId(const QString &kind_name) const
    {
        return kinds[kind_name];
    }


    int KindAndTags::getTagId(const QString &kind_name, const QString &tag_name) const
    {
        return tags[kind_name][tag_name];
    }





    VideoList::VideoList()
    {

    }


    void VideoList::setPageIndex(int page_index)
    {
        this->pageIndex = page_index;
    }


    int VideoList::getPageIndex() const
    {
        return pageIndex;

    }

    int VideoList::getVideoCount() const
    {
        return videoInfoLists.size();
    }

    void VideoList::setVideoCount(int64_t count)
    {
        videoCount = count;
    }

    int VideoList::getVideoTotalCount() const
    {
        return videoTotalCount;
    }


    void VideoList::setVideoTotalCount(int64_t count)
    {
        this->videoTotalCount = count;
    }


    //////////////////////////////
    /// \brief VideoList::addVideoInfo
    /// \param info
    /// 增加Video
    void VideoList::addVideoInfo(const VideoInfo &info)
    {
        videoInfoLists.append(info);
    }
    //////////////////////////////


    //////////////////////////////
    /// \brief VideoList::getVideoListOfVideoInfo
    /// \return
    ///
    const QList<VideoInfo> &VideoList::getVideoListOfVideoInfo() const
    {
        return videoInfoLists;
    }

    void VideoList::clearVideoList()
    {
        videoInfoLists.clear();
        pageIndex = 1;
        videoTotalCount = 0;
    }

    //////////////////
    /// \brief VideoList::updateLikeNumber
    /// \param videoId
    ///
    void VideoList::updateLikeNumber(const QString &video_id,int64_t likeCount )
    {
        for(auto & vi: videoInfoLists)
        {
            if(vi.videoId == video_id)
            {
                vi.likeCount = likeCount;
                return;
            }
        }

    }
    //////////////////


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


}
















