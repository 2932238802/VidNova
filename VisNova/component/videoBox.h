#pragma once
#include <QWidget>
#include <QDir>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QPainter>
#include <Qpixmap>
#include "mpvPlayer.h"
#include "playerPage.h"
#include "common/myLog.h"
#include "common/ReadLocalFile.h"
#include"toast.h"
#include"lrPage/login.h"
#include "dataCenter/videoInfo.h"
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
    explicit VideoBox(const model::VideoInfo& videoInfo,QWidget *parent = nullptr);

    ~VideoBox();

    ///
    /// \brief eventFilter
    /// \param watched
    /// \param event
    /// \return
    /// 虚函数重写
    bool eventFilter(QObject *watched, QEvent *event) override;
    const QString& getVideoId() const;
    QPixmap getUserAvatar() const ;

private:
    void setVideoImage(const QString& photoId);
    void paintEvent(QPaintEvent* event) override;
    void setUserAvatar(const QString& userAvatar);


signals:
    void _onPlayBtnClicked();

public slots:
    // void onPlayBtnClicked(); // 视频播放按钮
    // void initBullet();
    void updataVideoInfoUI();
    void getVideoImage(const QString& photoId,QByteArray imageData);
    void onUserAvatarGeted(const QString& photoId,QByteArray imageData);
    void onUpdateLikeNumber(int64_t like_number); // 由 playpage 发出来的
    void setLikeBtn(const QString& videoId,bool is_liked);


private:
    QPixmap videoCoverImage;
    QPixmap userAvatar;
    Ui::VideoBox *ui;
    model::VideoInfo videoInfo;

};

