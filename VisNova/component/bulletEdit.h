#pragma once

#include <QWidget>
#include "common/myLog.h"

namespace Ui {
class BulletEdit;
}

class BulletEdit : public QWidget
{
    Q_OBJECT

public:
    explicit BulletEdit(QWidget *parent = nullptr);
    ~BulletEdit();

private slots:
    void onSendBtnClicked();


private:
    Ui::BulletEdit *ui;
};


