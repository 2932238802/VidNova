#pragma once
#include <QWidget>
#include"editUserForAp.h"
#include"common/myLog.h"
#include"dataCenter/adminInfo.h"
// #include"dataCenter/adminInfo.h"

namespace Ui
{
    class RolePageItem;
}

enum StateBtn{
    Able = 0,
    Disable
};

class RolePageItem : public QWidget
{
    Q_OBJECT

public:
    explicit RolePageItem(model::AdminInfo& adminInfo,QWidget *parent = nullptr,int seqNumber = 1);
    ~RolePageItem();

private:
    void initConnect();
    void updateUI(int seqNumber);
    void updateStateBtnStyle(StateBtn state);

private slots:
    void onEditBtnClicked();
    void onSetAdminDone();
    void onStateBtnClicked();
    void onDelBtnClicked();

private:

    Ui::RolePageItem *ui;
    model::AdminInfo& adminInfo;
};
