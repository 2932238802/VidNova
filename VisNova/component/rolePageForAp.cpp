#include "rolePageForAp.h"
#include "ui_rolePageForAp.h"


///////////////////////////////////
/// \brief RolePageForAp::RolePageForAp
/// \param parent
///
RolePageForAp::RolePageForAp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RolePageForAp)
{
    ui->setupUi(this);
    initStyle();
    updataRolePage();
    ui->roleStateCombox->addItem("全部分类");
    ui->roleStateCombox->addItem("启用");
    ui->roleStateCombox->addItem("停用");
    ui->roleStateCombox->setCurrentIndex(0);
    ui->layout->setAlignment(Qt::AlignTop); // 靠上对齐

    // 分页器
    // 在堆上面 创建 空间 要手动删除一下
    l_paginator = std::make_unique<Paginator>(0,ui->paginatorArea);
    l_paginator->move(0,15);
    l_paginator->show();

    QRegularExpression regulation("^1[0-9]{10}$");
    QValidator* validator = new QRegularExpressionValidator(regulation,this);
    ui->roleEmailEdit->setValidator(validator);
    initConnect();
}
///////////////////////////////////





///////////////////////////////////
/// \brief RolePageForAp::~RolePageForAp
///
RolePageForAp::~RolePageForAp()
{
    delete ui;
}
///////////////////////////////////




///////////////////////////////////
/// \brief RolePageForAp::initStyle
///
void RolePageForAp::initStyle()
{
    l_styleSheet.insert("选中",R"(
    background-color: #3ECEFE;
    border-radius: 5px;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #FFFFFF;
)");
    l_styleSheet.insert("未选中",R"(
    background-color: #FFFFFF;
    border-radius: 4px;
    border: 1px solid #DCDEE0;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #222222;
)");
}
///////////////////////////////////



///////////////////////////////////
/// \brief RolePageForAp::initConnect
///
void RolePageForAp::initConnect()
{
    auto dataCenter = model::DataCenter::getInstance();
    connect(ui->resetBtn,&QPushButton::clicked,this,&RolePageForAp::onResetBtnClicked);
    connect(ui->queryBtn,&QPushButton::clicked,this,&RolePageForAp::onQueryBtnClicked);
    connect(ui->addRoleBtn,&QPushButton::clicked,this,&RolePageForAp::onAddRoleBtnClicked);
    connect(dataCenter,&model::DataCenter::_getAdminInfoByEmailDone,this,&RolePageForAp::updataRolePage);
    connect(dataCenter,&model::DataCenter::_getAdminInfoByStateDone,this,&RolePageForAp::updataRolePage);
    connect(dataCenter,&model::DataCenter::_addAdminDone,this,&RolePageForAp::onAddAdminDone);
    // connect(dataCenter,&model::DataCenter::_setAdminStateDone,[=](){
    //     getAdminList(l_page);
    // });

    // TODO 这个是要修改的
    connect(dataCenter,&model::DataCenter::_delAdminDone,[=](){
        getAdminList(1);
    });
}
///////////////////////////////////



///////////////////////////////////
/// \brief RolePageForAp::updataRolePage
/// 先清空原有的元素
void RolePageForAp::updataRolePage()
{
#ifdef ROLEPAGEFORAP_TEST
    LOG() << "RolePageForAp::updataRolePage()";
#endif

    QLayoutItem* item = nullptr;
    auto dataCenter = model::DataCenter::getInstance();
    auto adminListPtr = dataCenter -> getAdminList();
    auto adminList = adminListPtr->adminList;
    int countPage = model::AdminList::PAGE_COUNT;
    int totalCount = adminListPtr->totalCount;
    int seq = (l_page - 1) * countPage + 1;

    if(nullptr == adminListPtr)
    {
#ifdef ROLEPAGEFORAP_TEST
        LOG() << "adminList 是 空指针";
#endif
        return;
    }

    // 重置分页器
    if(l_page == 1)
    {
        resetPaginator((totalCount + countPage - 1)/countPage);
    }
    else{

    }


    // 清空页面元素
    while(nullptr != (item = ui->layout->takeAt(0)))
    {
        delete item->widget();
        delete item;
    }

    // 添加到 页面当中
    for(int i = 0; i < adminList.size(); i++)
    {
        RolePageItem* item  = new RolePageItem(adminList[i],this,seq++);
        ui->layout->addWidget(item);
    }
}
///////////////////////////////////



///////////////////////////////////
/// \brief RolePageForAp::getAdminList
/// \param page
///
void RolePageForAp::getAdminList(int page)
{
    auto dataCenter = model::DataCenter::getInstance();
    auto adminList = dataCenter->getAdminList();

    adminList->adminList.clear();

    l_page = page;


    QString phoneNumber = ui->roleEmailEdit->text();

    if(phoneNumber.isEmpty())
    {
        // 状态获取
        model::AdminState state = static_cast<model::AdminState>(ui->roleStateCombox->currentIndex());
        dataCenter->getAdminInfoByStateAsync(page,state);
    }
    else{
        dataCenter->getAdminInfoByEmailAsync(phoneNumber);
    }

}
///////////////////////////////////


///////////////////////////////////
/// \brief RolePageForAp::resetPaginator
/// \param page_number
/// 重置分页器
void RolePageForAp::resetPaginator(int page_number)
{
    // 判断连接是不是存在
    if (paginatorConnection) {
        QObject::disconnect(paginatorConnection);
    }

    if (l_paginator) {
        l_paginator.reset();
    }

    l_paginator = std::make_unique<Paginator>(page_number, ui->paginatorArea);
    l_paginator->move(0, 15);
    l_paginator->show();

    paginatorConnection = connect(l_paginator.get(), &Paginator::_pageChanged, this, [=](int page){
        getAdminList(page);
    });
}
///////////////////////////////////



///////////////////////////////////
/// \brief RolePageForAp::onResetBtnClicked
///
void RolePageForAp::onResetBtnClicked()
{
    ui->resetBtn->setStyleSheet(l_styleSheet["选中"]);
    ui->queryBtn->setStyleSheet(l_styleSheet["未选中"]);
    ui->roleEmailEdit->setText("");
    ui->roleStateCombox->setCurrentIndex(0);

    // 获取 管理员列表
    // 管理员状态有关 如果禁止了 就不行了
    if(!model::DataCenter::getInstance()->getMyselfInfo()->isAble())
    {
        Toast::showMsg("请联系相关人员 检查一下权限哦~");
        return;
    }
    else{
        getAdminList(1);
    }
}
///////////////////////////////////



///////////////////////////////////
/// \brief RolePageForAp::onQueryBtnClicked
///
void RolePageForAp::onQueryBtnClicked()
{
    ui->resetBtn->setStyleSheet(l_styleSheet["未选中"]);
    ui->queryBtn->setStyleSheet(l_styleSheet["选中"]);

    // 获取 管理员列表
    // 管理员状态有关 如果禁止了 就不行了
    if(!model::DataCenter::getInstance()->getMyselfInfo()->isAble())
    {
        Toast::showMsg("请联系相关人员 检查一下权限哦~");
        return;
    }
    else{
        getAdminList(1);
    }
}
///////////////////////////////////



///////////////////////////////////
/// \brief RolePageForAp::onAddRoleBtnClicked
///
void RolePageForAp::onAddRoleBtnClicked()
{
    model::AdminInfo userInfo;
    EditUserForAp* editUserForAp = new EditUserForAp(EditOrAdd::Add,userInfo,nullptr,"新增用户");
    editUserForAp->setEmailEditReadOnly(false);

    if(editUserForAp->isCommited())
    {
        // 新增管理员的请求
        model::DataCenter::getInstance()->addAdminAsync(userInfo);
    }

    editUserForAp->exec();
    delete editUserForAp;
}
///////////////////////////////////



///////////////////////////////////
/// \brief RolePageForAp::onAddAdminDone
///
void RolePageForAp::onAddAdminDone()
{
    getAdminList(1);
}
///////////////////////////////////








