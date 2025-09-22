#include "rolePageForAp.h"
#include "ui_rolePageForAp.h"


RolePageForAp::RolePageForAp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RolePageForAp)
{
    ui->setupUi(this);
    initStyle();
    updataRolePage();
    ui->roleStatusCombox->addItem("全部分类");
    ui->roleStatusCombox->addItem("启用");
    ui->roleStatusCombox->addItem("停用");
    ui->roleStatusCombox->setCurrentIndex(0);

    // 分页器
    // 在堆上面 创建 空间 要手动删除一下
    paginator = new Paginator(10,ui->paginatorArea);
    paginator->move(0,15);
    paginator->show();

    QRegularExpression regulation("^1[0-9]{10}$");
    QValidator* validator = new QRegularExpressionValidator(regulation,this);
    ui->rolePhoneEdit->setValidator(validator);
    connect(ui->resetBtn,&QPushButton::clicked,this,&RolePageForAp::onResetBtnClicked);
    connect(ui->queryBtn,&QPushButton::clicked,this,&RolePageForAp::onQueryBtnClicked);
    connect(ui->addRoleBtn,&QPushButton::clicked,this,&RolePageForAp::onAddRoleBtnClicked);
}

RolePageForAp::~RolePageForAp()
{
    delete ui;
    delete paginator;
}

void RolePageForAp::initStyle()
{
    styleSheet.insert("选中",R"(
    background-color: #3ECEFE;
    border-radius: 5px;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #FFFFFF;
)");
    styleSheet.insert("未选中",R"(
    background-color: #FFFFFF;
    border-radius: 4px;
    border: 1px solid #DCDEE0;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #222222;
)");

}

void RolePageForAp::updataRolePage()
{
    for(int i =0 ; i < 10; i++)
    {
        RolePageItem* item = new RolePageItem(this);
        ui->layout->addWidget(item);
    }
}

void RolePageForAp::onResetBtnClicked()
{
    ui->resetBtn->setStyleSheet(styleSheet["选中"]);
    ui->queryBtn->setStyleSheet(styleSheet["未选中"]);
    ui->rolePhoneEdit->setText("");
    ui->roleStatusCombox->setCurrentIndex(0);
    LOG()<<"点击了重置按钮";
}

void RolePageForAp::onQueryBtnClicked()
{
    ui->resetBtn->setStyleSheet(styleSheet["未选中"]);
    ui->queryBtn->setStyleSheet(styleSheet["选中"]);
}

void RolePageForAp::onAddRoleBtnClicked()
{
    EditUserForAp* editUserForAp = new EditUserForAp(nullptr,"新增用户");
    editUserForAp->exec();

    delete editUserForAp;

}
