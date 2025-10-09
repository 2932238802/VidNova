#pragma once

#include <QWidget>
#include <QFileInfo>
#include <QFileDialog>
#include <QFileInfo>
#include "vidnovamain.h"
#include "common/myLog.h"
#include "videoBox.h"
#include "common/ReadLocalFile.h"
#include "modifySelfInfo.h"

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
    ~MyPage();

private:
    void initUi();
    void initConnect();
    void hideWidget(bool is_hide = true);


private slots:
    void onAvatarBtnClicked();
    void onModifyBtnClicked();
    void onUploadVideoBtnClicked();
    void onGetMyselfInfoDone();
    void getAvatarDone(const QString& file_id,const QByteArray& avatar_data);
    void uploadAvatarFileId(const QString& fileId);
    void uploadAvatarFileId2();

signals:
    void switchUploadVideoPage(int page_id);

private:
    Ui::MyPage *ui;
};

