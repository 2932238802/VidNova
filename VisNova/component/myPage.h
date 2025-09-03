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
    ~MyPage();

private:
    void initUi();

private slots:
    void onAvatarBtnClicked();
    void onModifyBtnClicked();
    void onUploadVedioBtnClicked();

signals:
    void switchUploadVedioPage(int page_id);

private:
    Ui::MyPage *ui;
};

