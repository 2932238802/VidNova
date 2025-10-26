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

#ifdef MYPAGE_DISCARD
    void getMyselfInfo();
#endif

    void loadMyselfInfoAndVideo();
    void loadOtherUserInfoAndVideo(const QString& user_id);

    ~MyPage();

private:
    void initConnect();
    void hideWidget(bool is_hide = true);
    void getUserVideoList(const QString& user_id,int page_index);
    void clearVideoList();
    void deleteVideo(const QString& video_id);

#ifdef MYPAGE_DISCARD
    void getOtherUserInfo(const QString& user_id);
#endif

private slots:
    void onAvatarBtnClicked();
    void onAddAttentionSuc();
    void onAttentionBtnClicked();
    void onDelAttentionSuc();
    void onDeleteVideoDone(const QString& video_id);
    void onExitBtnClicked();
    void onGetOtherUserInfoDone(); // 获取 其它用户信息 成功之后 调用的槽函数
    void onGetMyselfInfoDoneOrResetMypage();
    void onGetUserVideoListDone(const QString& user_id);
    void onGetAvatarDone(const QString& file_id,const QByteArray& avatar_data);
    void onLogoutDone();
    void onLoginSuc();
    void onModifyBtnClicked();
    void onNickNameBtnClicked();
    void onSetNicknameDone(const QString& nickName);
    void onScrollAreaValueChanged(int value);
    void onUploadVideoBtnClicked();
    void onUploadAvatarFileId(const QString& user_id,PhotoUploadPurpose pup);
    void onUploadAvatarFileId2();

signals:
    void switchUploadVideoPage(int page_id,const QString& filename);

private:
    std::unique_ptr<Login> login;
    Ui::MyPage *ui;
    QString user_id_cur = ""; // 当前的用户
    bool mutex_LoadingMore = false;
};

