#include "modifyPd.h"
#include "ui_modifyPd.h"


////////////////////////
/// \brief ModifyPd::ModifyPd
/// \param parent
///
ModifyPd::ModifyPd(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifyPd)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    connect(ui->cancelBtn,&QPushButton::clicked,this,&QDialog::close);
    connect(ui->newPdEdit,&QLineEdit::editingFinished,this,&ModifyPd::onEdittingFinished);
    connect(ui->newPdAgainEdit,&QLineEdit::editingFinished,this,&ModifyPd::onEdittingFinished);

    // 提交按钮的点击
    connect(ui->submitBtn,&QPushButton::clicked,this,&ModifyPd::onSubminBtnClicked);
}
////////////////////////



////////////////////////
/// \brief ModifyPd::getPd
/// \return
///
const QString &ModifyPd::getPd() const
{
    return this->password;
}
////////////////////////



////////////////////////
/// \brief ModifyPd::~ModifyPd
///
ModifyPd::~ModifyPd()
{
    delete ui;
}
////////////////////////



////////////////////////
/// \brief ModifyPd::check
/// \return
///
bool ModifyPd::check()
{
    if(ui->newPdEdit->text().isEmpty() || ui->newPdAgainEdit->text().isEmpty())
    {
        ui->messageLabel->setText("内容不能为空！");

        return false;
    }

    //
    QRegularExpression re("^[a-zA-Z0-9_]{8,16}$");
    if(!re.match(ui->newPdEdit->text()).hasMatch())
    {
        ui->messageLabel->setText("密码包含字母数字或者下划线组成8~16位");
    }
    if(ui->newPdEdit->text() != ui->newPdAgainEdit->text())
    {
        ui->messageLabel->setText("重新输入的密码要保持一致");
        return false;
    }
    ui->messageLabel->setText("");
    return true;
}

bool ModifyPd::initConnect()
{
    auto dataCenter = model::DataCenter::getInstance();
    connect(dataCenter,&model::DataCenter::_setPasswordDone,this,&ModifyPd::setPasswordDone);
}
////////////////////////



////////////////////////
void ModifyPd::onEdittingFinished()
{
    check();
}
////////////////////////



////////////////////////
void ModifyPd::onSubminBtnClicked()
{
    if(check())
    {
        LOG()<<"修改成功...";

        // 新密码的设置
        password = ui->newPdEdit->text();

        // 密码
        model::DataCenter::getInstance()->setNewPasswordAsync(password);

        close();
    }
}
////////////////////////



////////////////////////
/// \brief ModifyPd::setPasswordDone
///
void ModifyPd::setPasswordDone()
{
#ifdef MODIFYPD_TEST
    LOG() << "ModifyPd::setPasswordDone()...";
    LOG() << "设置新密码成功，密码为:" << password;
#endif
}
////////////////////////















