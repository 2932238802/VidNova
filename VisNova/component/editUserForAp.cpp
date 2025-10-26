#include "editUserForAp.h"
#include "ui_editUserForAp.h"


////////////////////////////////
/// \brief EditUserForAp::EditUserForAp
/// \param parent
/// \param titleName
///
EditUserForAp::EditUserForAp(EditOrAdd mode,model::AdminInfo &info,QWidget *parent,const QString&titleName) :
    QDialog(parent),
    ui(new Ui::EditUserForAp),
    l_userInfo(info)
{
    ui->setupUi(this);
    initUi(titleName,mode);
}
////////////////////////////////




////////////////////////////////
/// \brief EditUserForAp::~EditUserForAp
///
EditUserForAp::~EditUserForAp()
{
    delete ui;
}
////////////////////////////////



////////////////////////////////
/// \brief EditUserForAp::setEmailEditReadOnly
/// \param isSure
///
void EditUserForAp::setEmailEditReadOnly(bool isSure)
{
    ui->emailEdit->setReadOnly(isSure);
}
////////////////////////////////


////////////////////////////////
/// \brief EditUserForAp::isCommited
/// \return
///
bool EditUserForAp::isCommited() const
{
    return l_isCommited;
}
////////////////////////////////



////////////////////////////////
/// \brief EditUserForAp::onCancelBtnClicked
///
void EditUserForAp::onCancelBtnClicked()
{
    l_isCommited = false;
    close();
}
////////////////////////////////



////////////////////////////////
/// \brief AddUserForAp::onSubmitBtnClicked
/// 点击提交
void EditUserForAp::onSubmitBtnClicked()
{
#ifdef EDITUSERFORAP_TEST
    LOG() << "EditUserForAp::onSubmitBtnClicked()";
    LOG()<<"[suc] 提交编辑内容...";
#endif

    l_isCommited = true;

    l_userInfo.emailNumber = ui->emailEdit->text();

    // 角色
    l_userInfo.roleType = model::RoleType::Admin;

    // 昵称
    l_userInfo.nickName = ui->nickNameEdit->text()        ;


    // 状态
    model::AdminState state = model::AdminState::Eable;
    if(ui->stateCloseBtn->isChecked())
    {
        state = model::AdminState::Disable;
    }
    l_userInfo.state = state;


    l_userInfo.userMemo = ui->commentEdit->toPlainText();

    close();
}
////////////////////////////////



////////////////////////////////
/// \brief EditUserForAp::initUi
///
void EditUserForAp::initUi(const QString& titleName,EditOrAdd mode)
{

#ifdef EDITUSERFORAP_TEST
    LOG() << "EditUserForAp::initUi(const QString& titleName,EditOrAdd mode)" ;
#endif


    setWindowFlags(Qt::FramelessWindowHint); // 没有窗口
    setAttribute(Qt::WA_TranslucentBackground); // 就不会 给 window窗口 设置默认的颜色
    ui->titleLabel->setText(titleName); // 移动阴影

    VidNovaMain* mainWindow = VidNovaMain::getInstance();

    // 这个代码的逻辑 就是 这个 全局 0 0 对应这个主要屏幕的左上角位置是多少
    auto [x,y] = mainWindow->mapFromGlobal(QPoint(0,0));
    this->move(-x,-y);
    // 绑定按钮 和 槽函数

    // 编辑框 里面的手机号 进行限制
    QRegularExpression regExp("^1\\d{10}$");
    QValidator* validator = new QRegularExpressionValidator(regExp,this);
    ui->emailEdit->setValidator(validator);
    ui->roleComboBox->addItem("平台管理员");
    ui->roleComboBox->setCurrentIndex(0);


    if(mode == EditOrAdd::Add)
    {
        // 内容全部清空
        ui->nickNameEdit->setText(l_userInfo.nickName); // 昵称

        if(model::RoleType::Admin == l_userInfo.roleType)
        {
            ui->roleComboBox->setCurrentIndex(0);
        }

        if(model::AdminState::Eable == l_userInfo.state)
        {
            ui->stateStartBtn->setChecked(true);
        }
        else{
            ui->stateCloseBtn->setChecked(true);
        }
        ui->roleComboBox->setCurrentIndex(-1);
        ui->commentEdit->setPlainText(l_userInfo.userMemo);
        ui->emailEdit->setText(l_userInfo.emailNumber);
    }
    else if(mode == EditOrAdd::Edit)
    {
        // 用户信息初始化
        ui->nickNameEdit->setText("");
        ui->roleComboBox->setCurrentIndex(-1);
        ui->commentEdit->setPlainText("");
        ui->emailEdit->setText("");
    }
    else{
#ifdef EDITUSERFORAP_TEST
        LOG() << "未知模式" ;
#endif
    }
}
////////////////////////////////



////////////////////////////////
/// \brief EditUserForAp::initConnect
///
void EditUserForAp::initConnect()
{
    connect(ui->cancelBtn,&QPushButton::clicked,this,&EditUserForAp::onCancelBtnClicked);
    connect(ui->submitBtn,&QPushButton::clicked,this,&EditUserForAp::onSubmitBtnClicked);
    connect(ui->commentEdit,&QPlainTextEdit::textChanged,this,[=](){
        QString text = ui->commentEdit->toPlainText();
        int wordCount = text.length();
        if(wordCount<=10)
        {
            ui->wordCount->setText(QString::number(wordCount) + "//10");
        }
        else{
            ui->commentEdit->setPlainText(text.mid(0,10)); // 截取十个
            QTextCursor cursor =  ui->commentEdit->textCursor();
            cursor.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
            ui->commentEdit->setTextCursor(cursor);
        }
    });
}
////////////////////////////////
