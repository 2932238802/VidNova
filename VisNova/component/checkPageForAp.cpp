#include "checkPageForAp.h"
#include "ui_checkPageForAp.h"



CheckPageForAp::CheckPageForAp(QWidget *parent):
    QWidget{parent},
    ui(new Ui::CheckPageForAp)
{
    ui->setupUi(this);
    ui->statusCombox->addItem("全部分类");
    ui->statusCombox->addItem("待审核");
    ui->statusCombox->addItem("审核通过");
    ui->statusCombox->addItem("审核驳回");
    ui->statusCombox->addItem("已下架");
    ui->statusCombox->addItem("转码中");
    ui->statusCombox->setCurrentIndex(0);

    paginator = new Paginator(10,ui->paginatorArea);
    paginator->move(0,15);
    paginator->show();

    QRegularExpression reg("^[0-9a-f]{4}-[0-9a-f]{8}-[0-9a-f]{4}$");
    QValidator* validator = new QRegularExpressionValidator(reg);
    ui->idEdit->setValidator(validator);

    updateCheckPage();
    connect(ui->resetBtn,&QPushButton::click,this,&CheckPageForAp::onResetBtnClicked);
    connect(ui->queryBtn,&QPushButton::click,this,&CheckPageForAp::onQueryBtnClicked);
}

CheckPageForAp::~CheckPageForAp()
{
    delete ui;
    delete paginator;
}


///
/// \brief CheckPageForAp::onQueryBtnClicked
/// 查询按钮 点击
void CheckPageForAp::onQueryBtnClicked()
{
    ui->queryBtn->setStyleSheet(R"(
    background-color: #3ECEFE;
    border-radius: 5px;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #FFFFFF;
)");
    ui->resetBtn->setStyleSheet(R"(
    background-color: #FFFFFF;
    border-radius: 4px;
    border: 1px solid #DCDEE0;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #222222;
)");


    LOG()<<"点击了查询按钮";
}

void CheckPageForAp::onResetBtnClicked()
{
    ui->resetBtn->setStyleSheet(R"(
    background-color: #3ECEFE;
    border-radius: 5px;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #FFFFFF;
)");
    ui->queryBtn->setStyleSheet(R"(
    background-color: #FFFFFF;
    border-radius: 4px;
    border: 1px solid #DCDEE0;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #222222;
)");

    ui->idEdit->setText("");
    ui->statusCombox->setCurrentIndex(0);
    LOG()<<"点击了重置按钮";
}

void CheckPageForAp::updateCheckPage()
{
    for(int i = 0 ;i < 10 ;i ++)
    {
        CheckPageItem * item = new CheckPageItem(this);
        ui->layout->addWidget(item);


    }
}
