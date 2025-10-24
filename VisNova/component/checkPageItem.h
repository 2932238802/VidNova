#pragma once
#include <QWidget>
#include "dataCenter/videoInfoForLoad.h"
#include "dataCenter/dataCenter.h"
#include "confirmDialog.h"
#include "playerPage.h"
#include "myLog.h"
#include "style.h"

namespace Ui {
class CheckPageItem;
}

// 待审核  通过和驳回
// 已审核  下架
// 已驳回
// 已下架  上架



class CheckPageItem : public QWidget
{
    Q_OBJECT

public:
    explicit CheckPageItem(QWidget *parent,const model::VideoInfoForLoad& videoInfo);
    ~CheckPageItem();

private slots:
    void onVideoBtnClicked();
    void onOpBtn1Clicked();
    void onOpBtn2Clicked();

private:
    void setCheckedStyle(); // 已审核
    void setRejectedStyle(); // 已驳回
    void setWaitingForCheckStyle(); // 待审核
    void setPutDownStyle();

private:
    model::VideoInfoForLoad l_videoInfo;

    Ui::CheckPageItem *ui;
    std::unique_ptr<PlayerPage> player;
    QPixmap userAvatar;
};


