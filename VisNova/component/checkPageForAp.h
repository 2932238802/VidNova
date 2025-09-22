#pragma once

#include <QWidget>
#include "common/myLog.h"
#include "checkPageItem.h"
#include "paginator.h"
namespace Ui {
class CheckPageForAp;
}

class CheckPageForAp : public QWidget
{
    Q_OBJECT

public:
    explicit CheckPageForAp(QWidget *parent = nullptr);
    ~CheckPageForAp();

private slots:
    void onQueryBtnClicked();
    void onResetBtnClicked();
private:
    void updateCheckPage();

private:
    Ui::CheckPageForAp *ui;
    Paginator* paginator;
};


