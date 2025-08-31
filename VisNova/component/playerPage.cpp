#include "playerPage.h"
#include "ui_playerPage.h"

PlayerPage::PlayerPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerPage)
{
    ui->setupUi(this);
}

PlayerPage::~PlayerPage()
{
    delete ui;
}
