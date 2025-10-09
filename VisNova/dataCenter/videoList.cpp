#include "videoList.h"

namespace model{

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


};
