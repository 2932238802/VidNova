#include "modifyPd.h"
#include "ui_modifyPd.h"

ModifyPd::ModifyPd(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifyPd)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    connect(ui->cancelBtn,&QPushButton::clicked,this,&QDialog::close);
    connect(ui->newPdEdit,&QLineEdit::editingFinished,this,&ModifyPd::onEdittingFinished);
    connect(ui->newPdAgainEdit,&QLineEdit::editingFinished,this,&ModifyPd::onEdittingFinished);
    connect(ui->submitBtn,&QPushButton::clicked,this,&ModifyPd::onSubminBtnClicked);
}

const QString &ModifyPd::getPd() const
{
    return this->password;
}

ModifyPd::~ModifyPd()
{
    delete ui;
}

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

void ModifyPd::onEdittingFinished()
{
    check();
}

void ModifyPd::onSubminBtnClicked()
{
    if(check())
    {
        LOG()<<"修改成功...";
        password = ui->newPdEdit->text();
        close();
    }
}















