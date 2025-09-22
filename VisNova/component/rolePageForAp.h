#pragma once
#include <QWidget>
#include "common/myLog.h"
#include "rolePageItem.h"
#include"editUserForAp.h"
#include "paginator.h"

namespace Ui {
class RolePageForAp;
}

///
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

private:
    void initStyle();
    void updataRolePage();

private:
    Ui::RolePageForAp *ui;
    QMap<QString,QString> styleSheet;
    Paginator* paginator;
};


