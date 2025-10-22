#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QScrollBar>

#include"dataCenter/videoInfoForLoad.h"
#include "dataCenter/dataCenter.h"
#include "common/myLog.h"
#include"style/style.h"
#include "videoBox.h"
#include "dataCenter/dataCenter.h"
#include "dataCenter/videoInfoForLoad.h"

namespace Ui {
    class homePageCpt;
}


// 向服务器 获取视频列表的方式
enum VideoListStyle{
    All = 0,
    Kind,
    Tag,
    Search
};


class homePageCpt : public QWidget
{
    Q_OBJECT

public:
    explicit homePageCpt(QWidget *parent = nullptr);

    void resetTags(const QString& kind ,const QList<QString>& tags_contain);

    ~homePageCpt();

private:
    QPushButton* buildBtn(QWidget* parent,const QString&color,const QString&text );
    void initVideos();
    void initRefreshAndTopBtn();
    void initConnect();
    void initKindAndTags();
    void openPlayerPage(const model::VideoInfoForLoad& video_info);
    void clearLayoutAndBtn(QLayout* layout);

private slots: // 槽函数 被调用函数
    void onTopBtnClicked();

    void onRefreshBtnClicked();

    void updataVideoList();

    void onSearchVideosBtnClicked(const QString& text );

    void onScrollBarValueChanged(int value);

private:
    Ui::homePageCpt *ui;
    QButtonGroup* tagsGp;
    VideoListStyle lastStyle;
    long long combinedTagId = 0;
    bool isAppend = false;
    int curKindId ;
};


