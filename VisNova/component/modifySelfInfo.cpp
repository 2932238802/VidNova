#include "modifySelfInfo.h"
#include "component/ui_modifySelfInfo.h"
#include "ui_modifySelfInfo.h"

ModifySelfInfo::ModifySelfInfo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifySelfInfo)
{
    ui->setupUi(this);
    ui->newPassWdEdit->setEchoMode(QLineEdit::Password);
    setWindowFlag(Qt::FramelessWindowHint);

    connect(ui->submitBtn,&QPushButton::clicked,this,&ModifySelfInfo::onSumbitBtnClicked);
    connect(ui->cancelBtn,&QPushButton::clicked,this,&ModifySelfInfo::onCancelBtnClicked);
    connect(ui->modifyWdBtn,&QPushButton::clicked,this,&ModifySelfInfo::onModifyWdBtnClicked);
}

ModifySelfInfo::~ModifySelfInfo()
{
    delete ui;
}

void ModifySelfInfo::onCancelBtnClicked()
{
    close();
}

void ModifySelfInfo::onModifyWdBtnClicked()
{
    ModifyPd* modifyWd = new ModifyPd();
    modifyWd->exec();

    const QString&pd(modifyWd->getPd());
    if(pd.isEmpty()) {LOG()<<"[info] 取消密码修改..."; return ;}
    ui->newPassWdEdit->text() = pd;
    LOG()<<"[suc] 新密码已经设置...";
    delete modifyWd;
}

void ModifySelfInfo::onSumbitBtnClicked()
{
    LOG()<<"[suc] 提交修改信息成功";
}
