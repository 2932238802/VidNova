#include "videoBox.h"
#include "ui_videoBox.h"



VideoBox::VideoBox(const model::VideoInfo&video_info, QWidget *parent)
    :QWidget(parent)
    , ui(new Ui::VideoBox),videoInfo(video_info)
{
    ui->setupUi(this);
    ui->delVideoBtn->hide(); // 隐藏删除按钮

    ui->imageBox->setStyleSheet("background-color: transparent");
    ui->videoTitle->setStyleSheet(VIDEO_TITLE_LABEL);
    ui->videoInfoBox->setStyleSheet(VIDEO_INFO_BOX);
    ui->imageBox->installEventFilter(this);
    ui->videoTitleBox->installEventFilter(this);

    ui->likeNum->setText(intToString(video_info.likeCount));
    ui->playNum->setText(intToString(video_info.playCount));
    ui->videoDuration->setText(stringToTime(video_info.videoDuration));


    setVideoImage(videoInfo.photoId);
    setUserAvatar(videoInfo.userAvatarId);

    updataVideoInfoUI();
    auto dataCenter = model::DataCenter::getInstance();

    dataCenter->isLikeBtnClickedAsync(videoInfo.videoId);

    connect(dataCenter,&model::DataCenter::_isLikeBtnClicked,this,&VideoBox::setLikeBtn);
    connect(dataCenter,&model::DataCenter::_downloadPhotoDone,this,&VideoBox::getVideoImage);
    connect(dataCenter,&model::DataCenter::_downloadPhotoDone,this,&VideoBox::onUserAvatarGeted);
    connect(ui->delVideoBtn,&QPushButton::clicked,this,&VideoBox::onMoreBtnClicked);
}


VideoBox::~VideoBox()
{

    delete ui;
}

// 事件 过滤器
bool VideoBox::eventFilter(QObject *watched, QEvent *event)
{
    // 只要是
    if(ui->imageBox == watched || ui->videoTitleBox == watched)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            // 显示 播放窗口
            emit _onPlayBtnClicked();
            return true;
        }
    }
    // 如果希望 完全拦截 可以返回 true
    return QObject::eventFilter(watched,event);
}



const QString &VideoBox::getVideoId() const
{
    return videoInfo.videoId;
}

void VideoBox::showMoreBtn(bool is_show)
{
    if(is_show)
    {
        ui->delVideoBtn->show();
    }
    else{
        ui->delVideoBtn->hide();
    }
}


void VideoBox::updataVideoInfoUI()
{
    //
    ui->videoTitle->setText(videoInfo.videoTitle);

#ifdef HOMEPAGECPT_TEST
    // LOG()<< "标题..." <<ui->videoTitle->text();
#endif

    ui->likeNum->setText(intToString(videoInfo.likeCount)); // 点赞数量

    ui->playNum->setText(intToString(videoInfo.playCount)); // 播放量

    ui->userNickName->setText(videoInfo.nickName);

    ui->loadupTime->setText(videoInfo.loadupTime);

    ui->videoDuration->setText(stringToTime(videoInfo.videoDuration));

}

////////////////////////
/// \brief VideoBox::getVideoImageDone
/// \param photoId
/// \param imageData
///
void VideoBox::getVideoImage(const QString &photoId, QByteArray imageData)
{
    if(photoId != videoInfo.photoId)
    {
        return;
    }



    if(imageData.isEmpty())
    {

#ifdef VIDEOBOX_TEST
        LOG() << "imageData内容为空...";
#endif

        return;
    }

    // 更新

    if(!videoCoverImage.loadFromData(imageData))
    {
        LOG()<<"imageData 加载失败...";
        return;
    }

    update();
}
////////////////////////



////////////////////////
/// \brief VideoBox::onUserAvatarGeted
/// \param photoId
/// \param imageData
///
void VideoBox::onUserAvatarGeted(const QString &avatar_id, QByteArray imageData)
{
    // 把用户头像 设置上去
    if(avatar_id != videoInfo.userAvatarId)
    {
        return;
    }

    //
    userAvatar =  makeIcon(imageData,(ui->userIcon->width()/2),(ui->userIcon->height()/2));
    ui->userIcon->setPixmap(userAvatar);
}
////////////////////////



////////////////////////
/// \brief VideoBox::onUpdateLikeNumber
/// \param like_number
///  更新点赞数量
void VideoBox::onUpdateLikeNumber(int64_t like_number)
{


    if(like_number > videoInfo.likeCount)
    {
        // 点了
        ui->likeImage->setStyleSheet(PLAYERPAGE_LIKEBTN_CLIECKED);
    }
    else{
        ui->likeImage->setStyleSheet(PLAYERPAGE_LIKEBTN_UNCLICKED);
    }

    videoInfo.likeCount = like_number;
    ui->likeNum->setText(intToString(like_number));
}

////////////////////////
/// \brief VideoBox::setLikeBtn
/// \param videoId
/// \param is_liked
///
void VideoBox::setLikeBtn(const QString &videoId, bool is_liked)
{
    if(is_liked)
    {
        ui->likeImage->setStyleSheet(PLAYERPAGE_LIKEBTN_CLIECKED);
    }
    else{
        ui->likeImage->setStyleSheet(PLAYERPAGE_LIKEBTN_UNCLICKED);
    }
}
////////////////////////



////////////////////////
/// \brief VideoBox::onMoreBtnClicked
///
void VideoBox::onMoreBtnClicked()
{
    // 创建一个菜单 项
    QMenu menu(this);
    menu.setStyleSheet(VIDEO_MENU);
    menu.setWindowFlags(menu.windowFlags()| Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

    menu.setAttribute(Qt::WA_TranslucentBackground);

    menu.addAction("删除");

    QPoint point = QCursor::pos();

    QAction* action = menu.exec(point);

    if (action != nullptr)
    {
        if (action->text() == "删除")
        {

            emit _deleteVideo(videoInfo.videoId);
        }
    }

}
////////////////////////






////////////////////////
/// \brief VideoBox::getUserAvatar
/// \return
///
QPixmap VideoBox::getUserAvatar() const
{
    return userAvatar;
}
////////////////////////









// 设置 视频封面
void VideoBox::setVideoImage(const QString &photoId)
{
    auto dataCenter = model::DataCenter::getInstance();
    dataCenter->downloadPhotoAsync(photoId);
}

void VideoBox::paintEvent(QPaintEvent *event)
{
    // 如果图片不相符
    // 需要对图片进行缩放
    // SmoothTransformation 平滑算法 更加好 质量
    // KeepAspectRatio 保持 原始宽高比

    // ui->imageBox->setAutoFillBackground(true);

    // QPalette qpale = ui->imageBox->palette(); // 这个是内置的调色板

    // videoCoverImage = videoCoverImage.scaled(ui->imageBox->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

    // QBrush brush(videoCoverImage);

    // qpale.setBrush(QPalette::Window,brush);

    // ui->imageBox->setPalette(qpale);
    QWidget::paintEvent(event); // 调用父类实现
    if (videoCoverImage.isNull()) {
        return;
    }
    QPainter painter(this);
    QRect targetRect = ui->imageBox->geometry();
    painter.drawPixmap(targetRect, videoCoverImage);
}


////////////////////////
/// \brief VideoBox::setUserAvatar
/// \param userAvatar
///
void VideoBox::setUserAvatar(const QString &user_avatar_id)
{
    if(user_avatar_id.isEmpty())
    {
        ui->userIcon->setStyleSheet(R"(
            border-image: url(":/image/txMan.png");
        )");
    }
    else{

        auto dataCenter = model::DataCenter::getInstance();
        dataCenter->downloadPhotoAsync(user_avatar_id);
    }
}
////////////////////////




















