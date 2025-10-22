#pragma once
#include <QWidget>
#include <QFileDialog>
#include "vidnovamain.h"
#include "dataCenter/dataCenter.h"
#include "dataCenter/videoInfoForLoad.h"
#include "common/myLog.h"
#include "common/constants.h"
#include "mpvPlayer.h"
#include "style.h"



namespace Ui {
class UploadVideoPage;
}

class UploadVideoPage : public QWidget
{
    Q_OBJECT

public:
    explicit UploadVideoPage(QWidget *parent = nullptr);
    ~UploadVideoPage();

    void setTitleAndPath(const QString& video_path);
    void uploadPhoto(const QString& photo_path);

private slots:
    void onCommitBtnClicked();
    void onChangeBtnClicked();
    void onTagChanged(const QString &choosed_tag);
    void onTitleEditTextNumberChanged(const QString& words);
    void onPlainBriefIntroduceEditTextNumberChanged();
    void onUploadVideoDone(const QString& videoId);
    void onGetVideoDuraion(int64_t duration);
    void onGetVideoCoverDone(const QString& file_id,PhotoUploadPurpose pup);
    void onUploadVideoInfoForUploadDone();

private:
    void addTags(const QString& str);
    void initUi();
    void initConnect();
    void checkCommitBtnState();
    void reset();

signals:
    void returnMyPage(int page_id);
    void tagChanged(const QString &choosed_tag);

private:
    int maxContentLenth;
    int maxNumberLimit;
    int64_t videoDuration;
    bool isUploadVideoOk = false;
    bool isUploadPhotoOk = false;
    bool isGetVideoDurationOk = false;

    QString videoPath;
    QString videoFileId;
    QString videoCoverId;

    std::unique_ptr<MpvPlayer> mpvPlayer;
    Ui::UploadVideoPage *ui;

};


