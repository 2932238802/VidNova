#pragma once

#include <QDialog>
#include <QRegularExpression>
#include "common/myLog.h"

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

private slots:
    void onEdittingFinished();
    void onSubminBtnClicked();

private:
    Ui::ModifyPd *ui;
    QString password;
};

