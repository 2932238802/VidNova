#pragma once
#include <QWidget>

namespace Ui {
class CheckPageItem;
}

class CheckPageItem : public QWidget
{
    Q_OBJECT

public:
    explicit CheckPageItem(QWidget *parent = nullptr);
    ~CheckPageItem();

private:
    Ui::CheckPageItem *ui;
};


