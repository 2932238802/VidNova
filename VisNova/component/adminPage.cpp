#include "adminPage.h"
#include "ui_adminPage.h"

AdminPage::AdminPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminPage)
{
    ui->setupUi(this);

    connect(ui->checkBtnAp,&QPushButton::clicked,this,&AdminPage::onCheckBtnClicked);
    connect(ui->roleBtnAp,&QPushButton::clicked,this,&AdminPage::onRoleBtnClicked);

}

AdminPage::~AdminPage()
{
    delete ui;
}

void AdminPage::onCheckBtnClicked()
{
    ui->checkBtnAp->setStyleSheet(SYSTEMPAGE_ACTIVED_BUTTON);
    ui->roleBtnAp->setStyleSheet(SYSTEMPAGE_UNACTIVED_BUTTON);
    ui->checkAp->show();
    ui->roleAp->hide();
}

void AdminPage::onRoleBtnClicked()
{
    ui->checkBtnAp->setStyleSheet(SYSTEMPAGE_UNACTIVED_BUTTON);
    ui->roleBtnAp->setStyleSheet(SYSTEMPAGE_ACTIVED_BUTTON);
    ui->roleAp->show();
    ui->checkAp->hide();
}
