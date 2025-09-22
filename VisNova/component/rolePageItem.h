#pragma once
#include <QWidget>
#include"editUserForAp.h"
#include"common/myLog.h"

namespace Ui
{
    class RolePageItem;
}

class RolePageItem : public QWidget
{
    Q_OBJECT

public:
    explicit RolePageItem(QWidget *parent = nullptr,int seqNumber = 1);
    ~RolePageItem();

private:
    void updateUI(int seqNumber);


private slots:
    void onEditBtnClicked();


private:
    Ui::RolePageItem *ui;
};
