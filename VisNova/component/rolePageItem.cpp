#include "rolePageItem.h"
#include "ui_rolePageItem.h"


////////////////////////////////
/// \brief RolePageItem::RolePageItem
/// \param admin_info
/// \param parent
/// \param seqNumber
///
RolePageItem::RolePageItem(model::AdminInfo& admin_info,QWidget *parent,int seqNumber)
    : QWidget(parent)
    , ui(new Ui::RolePageItem),
    adminInfo(admin_info)
{
    ui->setupUi(this);
    updateUI(seqNumber);

    initConnect();
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
/// \brief RolePageItem::initConnect
///
void RolePageItem::initConnect()
{
    auto dataCenter = model::DataCenter::getInstance();

    //
    connect(ui->editBtn,&QPushButton::clicked,this,&RolePageItem::onEditBtnClicked);

    // 修改管理员的信息
    connect(dataCenter,&model::DataCenter::_setAdminDone,this,&RolePageItem::onSetAdminDone);

    // 状态按钮 设置
    connect(ui->stateBtn,&QPushButton::clicked,this,&RolePageItem::onStateBtnClicked);

    connect(ui->delBtn,&QPushButton::clicked,this,&RolePageItem::onDelBtnClicked);
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

    ui->emailLabel->setText(adminInfo.emailNumber); // 设置 邮箱密码
    ui->nameLabel->setText(adminInfo.nickName);

    if(adminInfo.state == model::AdminState::Disable){
        adminInfo.state = model::AdminState::Eable;
        ui->stateBtn->setText("启用");
        updateStateBtnStyle(StateBtn::Able);
    }
    else if(adminInfo.state == model::AdminState::Eable)
    {
        adminInfo.state = model::AdminState::Disable;
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
        ui->stateBtn->setStyleSheet(STATEBTN_ABLE);
    }
    else if(state == StateBtn::Disable)
    {
        ui->stateBtn->setStyleSheet(STATEBTN_DISABLE);
    }

}
////////////////////////////////


////////////////////////////////
/// \brief RolePageItem::onEditBtnClicked
/// 打开的时候 同时应该更新对应的用户信息
///
void RolePageItem::onEditBtnClicked()
{

#ifdef ROLEPAGEFORAP_TEST
    LOG()<<"[info] 弹出编辑用户窗口...";
#endif

    // TODO: 传入 对应的用户信息
    EditUserForAp*  editUserForAp = new EditUserForAp(EditOrAdd::Edit,adminInfo,nullptr,"编辑用户信息");

    editUserForAp->setEmailEditReadOnly(true);
    editUserForAp->exec();

    if(editUserForAp->isCommited())
    {
        model::DataCenter::getInstance()->setAdminAsync(adminInfo);
    }

    editUserForAp->deleteLater();
}
////////////////////////////////



////////////////////////////////
/// \brief RolePageItem::onSetAdminDone
/// 设置管理员 信息成功 更新界面的数据和信息
void RolePageItem::onSetAdminDone()
{
    ui->emailLabel->setText(adminInfo.emailNumber);
    ui->nameLabel->setText(adminInfo.nickName);
    ui->commentLabel->setText(adminInfo.userMemo);
    if(adminInfo.state == model::AdminState::Disable){
        adminInfo.state = model::AdminState::Eable;
        ui->stateBtn->setText("启用");
        updateStateBtnStyle(StateBtn::Able);
    }
    else if(adminInfo.state == model::AdminState::Eable)
    {
        adminInfo.state = model::AdminState::Disable; // 禁用
        ui->stateBtn->setText("禁用");
        updateStateBtnStyle(StateBtn::Disable);
    }
}
////////////////////////////////



////////////////////////////////
/// \brief RolePageItem::onStateBtnClicked
///
void RolePageItem::onStateBtnClicked()
{

    // 发送请求
    model::DataCenter::getInstance()->setAdminStateAsync(adminInfo.userId,adminInfo.state);

    if(adminInfo.state == model::AdminState::Disable){
        adminInfo.state = model::AdminState::Eable;
        ui->stateBtn->setText("启用");
        updateStateBtnStyle(StateBtn::Able);
    }
    else if(adminInfo.state == model::AdminState::Eable)
    {
        adminInfo.state = model::AdminState::Disable; // 禁用
        ui->stateBtn->setText("禁用");
        updateStateBtnStyle(StateBtn::Disable);
    }
    auto adminList = model::DataCenter::getInstance()->getAdminList();
    adminList->setAddStatus(adminInfo.userId,adminInfo.state);
}
////////////////////////////////



////////////////////////////////
/// \brief RolePageItem::onDelBtnClicked
///
void RolePageItem::onDelBtnClicked()
{
#ifdef ROLEPAGEFORAP_TEST
    LOG() << "RolePageItem::onDelBtnClicked()";
#endif
    model::DataCenter::getInstance()->delAdminAsync(adminInfo.userId);
}
////////////////////////////////










