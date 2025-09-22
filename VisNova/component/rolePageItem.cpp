#include "rolePageItem.h"
#include "ui_rolePageItem.h"

RolePageItem::RolePageItem(QWidget *parent,int seqNumber)
    : QWidget(parent)
    , ui(new Ui::RolePageItem)
{
    ui->setupUi(this);
    updateUI(seqNumber);

    connect(ui->editBtn,&QPushButton::clicked,this,&RolePageItem::onEditBtnClicked);
}

RolePageItem::~RolePageItem()
{
    delete ui;
}

void RolePageItem::updateUI(int seqNumber)
{
    ui->idLabel->setText(QString::number(seqNumber));
}

void RolePageItem::onEditBtnClicked()
{
    LOG()<<"[info] 弹出编辑用户窗口...";
    EditUserForAp*  editUserForAp = new EditUserForAp(nullptr,"编辑用户信息");
    editUserForAp->exec();
    delete editUserForAp;
}











