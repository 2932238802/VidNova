#include "rolePageItem.h"
#include "ui_rolePageItem.h"


////////////////////////////////
/// \brief RolePageItem::RolePageItem
/// \param admin_info
/// \param parent
/// \param seqNumber
///
RolePageItem::RolePageItem(const model::AdminInfo& admin_info,QWidget *parent,int seqNumber)
    : QWidget(parent)
    , ui(new Ui::RolePageItem),
    adminInfo(admin_info)
{
    ui->setupUi(this);
    updateUI(seqNumber);

    connect(ui->editBtn,&QPushButton::clicked,this,&RolePageItem::onEditBtnClicked);
}
////////////////////////////////


////////////////////////////////
/// \brief RolePageItem::~RolePageItem
///
RolePageItem::~RolePageItem()
{
    delete ui;
}
////////////////////////////////


////////////////////////////////
/// \brief RolePageItem::updateUI
/// \param seqNumber
///
void RolePageItem::updateUI(int seqNumber)
{
    ui->idLabel->setText(QString::number(seqNumber));

    // 用户角色
    // 手机号
    // 备注
    // 操作
    // 用户昵称
    // 状态

    if(model::RoleType::Admin == adminInfo.roleType)
    {
        // 普通管理员
        ui->roleLabel->setText("平台管理员");
        ui->delBtn->hide(); // 平台管理员 就不能删除 其它同事的 信息
        ui->editBtn->setText("--");
        ui->editBtn->move(1145,25);
        ui->editBtn->setEnabled(false);
        ui->stateBtn->setEnabled(false);
        ui->editBtn->setStyleSheet(EDITBTN);
    }
    else if(model::RoleType::SuperAdmin == adminInfo.roleType)
    {
        ui->roleLabel->setText("超级管理员");
        // 没有编辑和操作的按钮
        // 超级管理员
    }

    ui->emailLabel->setText(adminInfo.emailNumber);
    ui->nameLabel->setText(adminInfo.nickName);

    if(adminInfo.state == model::AdminState::Disable){
        ui->stateBtn->setText("启用");
        updateStateBtnStyle(StateBtn::Able);
    }
    else if(adminInfo.state == model::AdminState::Eable)
    {
        ui->stateBtn->setText("禁用");
        updateStateBtnStyle(StateBtn::Disable);
    }

    ui->stateBtn->setText(adminInfo.userMemo);
}
////////////////////////////////



////////////////////////////////
/// \brief RolePageItem::updateStateBtnStyle
/// \param state
///
void RolePageItem::updateStateBtnStyle(StateBtn state)
{
#ifdef ROLEPAGEFORAP_TEST
    LOG() << "RolePageItem::updateStateBtnStyle(StateBtn state)";
#endif

    if(state == StateBtn::Able)
    {

    }
    else if(state == StateBtn::Disable)
    {

    }

}
////////////////////////////////


////////////////////////////////
/// \brief RolePageItem::onEditBtnClicked
///
void RolePageItem::onEditBtnClicked()
{
    LOG()<<"[info] 弹出编辑用户窗口...";
    EditUserForAp*  editUserForAp = new EditUserForAp(nullptr,"编辑用户信息");
    editUserForAp->exec();
    delete editUserForAp;
}
////////////////////////////////










