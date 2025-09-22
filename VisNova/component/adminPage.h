#pragma once
#include <QWidget>
#include "style.h"
#include"checkPageItem.h"

namespace Ui {
class AdminPage;
}

class AdminPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent = nullptr);
    ~AdminPage();

private slots:
    void onCheckBtnClicked();
    void onRoleBtnClicked();



private:
    Ui::AdminPage *ui;
};

