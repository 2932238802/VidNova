#include "checkPageItem.h"
#include "ui_checkPageItem.h"

CheckPageItem::CheckPageItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CheckPageItem)
{
    ui->setupUi(this);
}

CheckPageItem::~CheckPageItem()
{
    delete ui;
}
