#pragma once
#include <QObject>
#include "videoInfoForLoad.h"
#include "myLog.h"

namespace model{

class VideoList{

public:
    VideoList();
    void setPageIndex(int page_index);
    int getPageIndex() const;

    int getVideoCount() const;
    void setVideoCount(int64_t count);

    int getVideoTotalCount() const;
    void setVideoTotalCount(int64_t count) ;
    void addVideoInfo(const VideoInfoForLoad& info);
    const QList<VideoInfoForLoad>& getVideoListOfVideoInfo() const;
    void clearVideoList(); // 清空一下任务列表
    void updateLikeNumber(const QString& videoId,int64_t likeCount);

public:
    QList<VideoInfoForLoad> videoInfoLists;
    int pageIndex;
    int64_t videoCount;
    int64_t videoTotalCount;
    const static int PAGE_COUNT = 20;  // 一页中的

};

};
