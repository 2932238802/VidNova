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

class EditUserForAp : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserForAp(QWidget *parent = nullptr,const QString &titleName = "新增用户");
    ~EditUserForAp();

private slots:
    void onCancelBtnClicked();
    void onSubmitBtnClicked();

private:
    Ui::EditUserForAp *ui;
};


