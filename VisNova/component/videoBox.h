#pragma once
#include <QWidget>
#include <QDir>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QPainter>
#include <Qpixmap>
#include <QMenu>
#include "mpvPlayer.h"
#include "playerPage.h"
#include "common/myLog.h"
#include "common/ReadLocalFile.h"
#include"toast.h"
#include"lrPage/login.h"
#include "dataCenter/videoInfoForLoad.h"
#include "dataCenter/dataCenter.h"
#include "intToString.h"
#include "stringToTime.h"


namespace Ui {
class VideoBox;
}

class VideoBox : public QWidget
{
    Q_OBJECT

public:
    explicit VideoBox(const model::VideoInfoForLoad& videoInfo,QWidget *parent = nullptr);

    ~VideoBox();
    bool eventFilter(QObject *watched, QEvent *event) override;
    const QString& getVideoId() const;

    void showMoreBtn(bool is_show);
    QPixmap getUserAvatar() const ;

private:
    void setVideoImage(const QString& photoId);
    void paintEvent(QPaintEvent* event) override;
    void setUserAvatar(const QString& userAvatar);


signals:
    void _onPlayBtnClicked();
    void _deleteVideo(const QString& videoId);

public slots:

    void updataVideoInfoUI();
    void getVideoImage(const QString& photoId,QByteArray imageData);
    void onUserAvatarGeted(const QString& photoId,QByteArray imageData);
    void onUpdateLikeNumber(int64_t like_number); // 由 playpage 发出来的
    void setLikeBtn(const QString& videoId,bool is_liked);
    void onMoreBtnClicked();

private:
    QPixmap videoCoverImage; // 封面图
    QPixmap userAvatar; // 用户头像
    model::VideoInfoForLoad videoInfo; // 该视频的相关信息

    Ui::VideoBox *ui;
};

