#pragma once

#include <QWidget>
#include <QComboBox>
#include "common/myLog.h"
#include "checkPageItem.h"
#include "paginator.h"
#include "dataCenter/dataCenter.h"
#include "toast.h"

// 注意视频的状态
// enum VideoState{
//     NoStatus = 0,
//     WaitForChecking, // 待审核
//     PutAway, // 审核通过
//     Reject,
//     Discard, // 下架了 之前是上架的
// };

namespace Ui {
class CheckPageForAp;
}

class CheckPageForAp : public QWidget
{
    Q_OBJECT

public:
    explicit CheckPageForAp(QWidget *parent = nullptr);
    ~CheckPageForAp();

private slots:
    void onQueryBtnClicked();
    void onResetBtnClicked();
    void onGetVideoListForMyselfOrOtherDone(const QString& userId,model::GetVideoPage page);
    void onGetVideoByStateDone();
private:
    void initConnect();
    // void updateCheckPage();
    void getVideoList(int page);

    bool checkState();

    void resetPaginator(int page_count);

    void updateVideoListUI();

private:
    Ui::CheckPageForAp *ui;

    int l_page = 1;
    std::unique_ptr<Paginator> l_paginator;

    QMetaObject::Connection paginatorConnection;
};


