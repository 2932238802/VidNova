#pragma once

#include <QDialog>
#include <QString>
#include "common/myLog.h"
#include "modifyPd.h"
#include "dataCenter/dataCenter.h"
#include "ui_modifySelfInfo.h"

namespace Ui {
class ModifySelfInfo;
}

class ModifySelfInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ModifySelfInfo(QWidget *parent = nullptr);
    ~ModifySelfInfo();

private:
    QString hideSomePhoneNumber(const QString& str);

private slots:
    void onCancelBtnClicked();
    void onModifyWdBtnClicked();
    void onSumbitBtnClicked();

private:
    Ui::ModifySelfInfo *ui;
};


