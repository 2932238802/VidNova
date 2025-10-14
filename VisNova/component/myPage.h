#pragma once

#include <QWidget>
#include <QFileInfo>
#include <QFileDialog>
#include <QFileInfo>
#include <QScrollBar>
#include "login.h"
#include "vidnovamain.h"
#include "myLog.h"
#include "videoBox.h"
#include "ReadLocalFile.h"
#include "modifySelfInfo.h"
#include "dataCenter/videoList.h"
#include "confirmDialog.h"

namespace Ui {
class MyPage;
}

class MyPage : public QWidget
{
    Q_OBJECT

public:
    explicit MyPage(QWidget *parent = nullptr);
    void getMyselfInfo();
    void loadMyselfInfoAndVideo();
    void loadOtherUserInfoAndVideo(const QString& user_id);
    void loadTempUserInfo();

    ~MyPage();

private:
    void initConnect();

    void hideWidget(bool is_hide = true);

    void getUserVideoList(const QString& user_id,int page_index);
    void clearVideoList();
    void deleteVideo(const QString& video_id);

    // 获取其它用户的个人信息
    void getOtherUserInfo(const QString& user_id);

private slots:
    void onAvatarBtnClicked();
    void onModifyBtnClicked();
    void onUploadVideoBtnClicked();
    void onAttentionBtnClicked();
    void onNickNameBtnClicked();
    void onExitBtnClicked();

    void onGetMyselfInfoDone();
    void getAvatarDone(const QString& file_id,const QByteArray& avatar_data);
    void uploadAvatarFileId(const QString& user_id);
    void uploadAvatarFileId2();

    void onGetUserVideoListDone(const QString& user_id);
    void onScrollAreaValueChanged(int value);

    void onAddAttentionSuc();
    void ondelAttentionSuc();
    void onLoginSuc();

    void deleteVideoDone(const QString& video_id);

    // 获取 其它用户信息 成功之后 调用的槽函数
    void getOtherUserInfoDone();

signals:
    void switchUploadVideoPage(int page_id);

private:
    std::unique_ptr<Login> login;
    Ui::MyPage *ui;
    QString user_id_cur = ""; // 当前的用户
    bool mutex_LoadingMore = false;
};

