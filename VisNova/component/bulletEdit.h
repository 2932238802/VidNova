#pragma once

#include <QWidget>
#include <QLineEdit>
#include "common/myLog.h"
#include "dataCenter/dataCenter.h"
#include "qpalette.h"
#include "login.h"

namespace Ui {
class BulletEdit;
}

class BulletEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit BulletEdit(QWidget *parent = nullptr);

    // 鼠标点击
    virtual void mousePressEvent(QMouseEvent* event) override;


    ~BulletEdit();

private slots:
    void onSendBtnClicked();

private:
    void initConnect();

signals:
    void sendBullet(const QString& str);


private:
    Ui::BulletEdit *ui;
};


