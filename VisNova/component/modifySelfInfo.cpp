#include "modifySelfInfo.h"


ModifySelfInfo::ModifySelfInfo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifySelfInfo)
{
    ui->setupUi(this);
    ui->newPassWdEdit->setEchoMode(QLineEdit::Password);
    setWindowFlag(Qt::FramelessWindowHint);

    auto dataCenter = model::DataCenter::getInstance();
    auto myselfInfo = dataCenter->getMyselfUserInfo();

    if(myselfInfo)
    {
        QString newPhoneNumber = hideSomePhoneNumber(myselfInfo->photoNumber);
        QString nickName = myselfInfo->nickName;
#ifdef MODIFYSELFINFO_TEST

        LOG() << "ModifySelfInfo::ModifySelfInfo(QWidget *parent)";
        LOG() << "newPhoneNumber " << newPhoneNumber;
        LOG() << "nickName " << nickName;
#endif
        ui->phoneLabel->setText("你好~ "+ newPhoneNumber);
        ui->nickNameEdit->setText(nickName);
    }

    connect(ui->submitBtn,&QPushButton::clicked,this,&ModifySelfInfo::onSumbitBtnClicked);
    connect(ui->cancelBtn,&QPushButton::clicked,this,&ModifySelfInfo::onCancelBtnClicked);
    connect(ui->modifyWdBtn,&QPushButton::clicked,this,&ModifySelfInfo::onModifyWdBtnClicked);
}

ModifySelfInfo::~ModifySelfInfo()
{
    delete ui;
}


///////////////////////////
QString ModifySelfInfo::hideSomePhoneNumber(const QString& str)
{
    if(str.size() != 11)
    {
#ifdef MODIFYSELFINFO_TEST
        LOG() << "输入的手机号码是有误的 所以加密号码失败...";
#endif
        return str;
    }
    QString newPhone = str;
    newPhone.replace(3,4,"****");
    return newPhone;
}
///////////////////////////



void ModifySelfInfo::onCancelBtnClicked()
{
    close();
}

void ModifySelfInfo::onModifyWdBtnClicked()
{
    ModifyPd* modifyWd = new ModifyPd();
    modifyWd->exec();

    const QString&pd(modifyWd->getPd());
    if(pd.isEmpty()) {
        LOG()<<"[info] 取消密码修改..."; return ;
    }
    ui->newPassWdEdit->text() = pd;
    LOG()<<"[suc] 新密码已经设置...";
    delete modifyWd;
}

void ModifySelfInfo::onSumbitBtnClicked()
{
#ifdef MODIFYSELFINFO_TEST
    LOG()<<"[suc] 提交修改信息成功";
#endif

    QString nickname = ui->nickNameEdit->text().trimmed();

    auto dataCenter = model::DataCenter::getInstance();
    auto myselfInfo = dataCenter->getMyselfUserInfo();
    if(myselfInfo)
    {
        if(nickname != myselfInfo->nickName)
        {
            dataCenter->setNicknameAsync(nickname);
        }
    }

    close();
}























