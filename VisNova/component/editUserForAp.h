#pragma once
#include <QDialog>
#include <QPushButton>
#include "common/myLog.h"
#include"vidnovamain.h"
#include <QValidator>

///
/// EditUserForAp 主要就是 各种编辑信息
///
namespace Ui {
class EditUserForAp;
}

enum EditOrAdd{
    Edit = 1,
    Add
};


class EditUserForAp : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserForAp(EditOrAdd mode, model::AdminInfo &info, QWidget *parent = nullptr,const QString &titleName = "编辑用户");
    ~EditUserForAp();

    void setAdminInfo(model::AdminInfo& info);
    void setEmailEditReadOnly(bool isSure);
    bool isCommited() const;

private slots:
    void onCancelBtnClicked();
    void onSubmitBtnClicked();

private:
    void initUi(const QString& titleName,EditOrAdd mode);
    void initConnect();


private:
    bool l_isCommited = false;
    Ui::EditUserForAp *ui;
    model::AdminInfo& l_userInfo;
};





















