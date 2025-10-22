#include "videoList.h"

namespace model{

VideoList::VideoList()
{
    pageIndex = 1; // 初始化页码
}


void VideoList::setPageIndex(int page_index)
{
#ifdef VIDEOLIST_TEST
    LOG() << "VideoList::setPageIndex(int page_index)";
    LOG() << "page_index:" << page_index;
#endif

    this->pageIndex = page_index;
}


int VideoList::getPageIndex() const
{

#ifdef VIDEOLIST_TEST
    LOG() << "VideoList::getPageIndex()";
    LOG() << "pageIndex:" << pageIndex;
#endif
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
void VideoList::addVideoInfo(const VideoInfoForLoad &info)
{
    videoInfoLists.append(info);
}
//////////////////////////////


//////////////////////////////
/// \brief VideoList::getVideoListOfVideoInfo
/// \return
///
const QList<VideoInfoForLoad> &VideoList::getVideoListOfVideoInfo() const
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




};
