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


signals:
    void sendBullet(const QString& str);


private:
    Ui::BulletEdit *ui;
};


