#pragma once

#include <QDialog>
#include <QRegularExpression>
#include "common/myLog.h"
#include "dataCenter/dataCenter.h"

namespace Ui {
class ModifyPd;
}

class ModifyPd : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyPd(QWidget *parent = nullptr);
    const QString& getPd() const;
    ~ModifyPd();


private:
    bool check();
    bool initConnect();

public slots:
    void onEdittingFinished();
    void onSubminBtnClicked();
    void setPasswordDone();

private:
    Ui::ModifyPd *ui;
    QString password;
};

