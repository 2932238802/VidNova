#pragma once

#include <QDialog>
#include "common/myLog.h"
#include "modifyPd.h"

namespace Ui {
class ModifySelfInfo;
}

class ModifySelfInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ModifySelfInfo(QWidget *parent = nullptr);
    ~ModifySelfInfo();

private slots:
    void onCancelBtnClicked();
    void onModifyWdBtnClicked();
    void onSumbitBtnClicked();

private:
    Ui::ModifySelfInfo *ui;
};


