#pragma once
#include <QWidget>
#include "common/myLog.h"
#include "rolePageItem.h"
#include"editUserForAp.h"
#include "paginator.h"

namespace Ui {
class RolePageForAp;
}

//////////////////////////////
/// \brief The RolePageForAp class
/// Ap 就是 adminPage
class RolePageForAp : public QWidget
{
    Q_OBJECT

public:
    explicit RolePageForAp(QWidget *parent = nullptr);
    ~RolePageForAp();

private slots:
    void onResetBtnClicked();
    void onQueryBtnClicked();
    void onAddRoleBtnClicked();
    void onAddAdminDone();

private:
    void initStyle();
    void initConnect();
    void updataRolePage();
    void getAdminList(int page);
    void resetPaginator(int page_number);

private:
    int l_page = 1;
    Ui::RolePageForAp *ui;
    QMap<QString,QString> l_styleSheet;
    std::unique_ptr<Paginator> l_paginator;
    QMetaObject::Connection paginatorConnection;
};
//////////////////////////////

