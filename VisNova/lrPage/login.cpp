#include "login.h"
#include "ui_login.h"


Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    // 不需要 手动设置
    // setAttribute(Qt::WA_ShowModal,true); // 没有意义了
    // setAttribute(Qt::FramelessWindowHint);
    // setWindowFlags(Qt::FramelessWindowHint);
    initConnect();
    inputInit();
    ui->msgContain->show();
    ui->pdContain->hide(); // 密码登录
}

Login::~Login()
{
    delete ui;
}

void Login::initConnect()
{
    auto dataCenter = model::DataCenter::getInstance();
    connect(ui->minBtn,&QPushButton::clicked,this,&QWidget::showMinimized);
    connect(ui->quitBtn,&QPushButton::clicked,this,&QWidget::close);
    connect(ui->msgBtn,&QPushButton::clicked,this,&Login::onMsgWayClicked);
    connect(ui->pdBtn,&QPushButton::clicked,this,&Login::onPdWayClicked);

    connect(ui->authCodeBtn,&QPushButton::clicked,this,&Login::onAuthCodeBtnClicked);
    connect(dataCenter,&model::DataCenter::_getCodeFromEmailDone,this,&Login::onGetCodeFromEmailDone);

    connect(ui->loginOrRegister,&QPushButton::clicked,this,&Login::onLoginOrRegisterBtnClicked);



    connect(dataCenter,&model::DataCenter::_lrByAuthCodeFailed,this,&Login::onLrByAuthCodeFailed);
    connect(dataCenter,&model::DataCenter::_lrByAuthCodeSuc,this,&Login::onLrByAuthCodeSuc);
    connect(dataCenter,&model::DataCenter::_lrByPdFailed,this,&Login::onLrByPdFailed);
    connect(dataCenter,&model::DataCenter::_lrByPdSuc,this,&Login::onLrByPdSuc);

    connect(ui->registerNowForpd,&QPushButton::clicked,this,&Login::onRegisterNowBtnClicked);
    connect(ui->loginNowForpd,&QPushButton::clicked,this,&Login::onLoginNowBtnClicked);

}

///
/// \brief Login::inputInit
/// 输入框 限制一下
void Login::inputInit()
{
    QRegularExpression regularExpression("^1\\d{10}$"); // 从%^ 开始 $ 结束
    QValidator *validator = new QRegularExpressionValidator(regularExpression,this);
    ui->emailEdit->setValidator(validator);

    // 验证码设置
    QIntValidator * qIntValidator = new QIntValidator(0,999999,ui->autoCodeEdit);
    ui->autoCodeEdit->setValidator(qIntValidator);
    ui->autoCodeEdit->setMaxLength(6);

}

///
/// \brief Login::styleInit
/// 窗口初始化设置
void Login::styleInit()
{
    // 设置一个阴影
    setAttribute(Qt::WA_TranslucentBackground); // 让阴影能够被看到
    // QGraphicsDropShadowEffect 主要是为了 投影的效果
    QGraphicsDropShadowEffect* dropShadow = new QGraphicsDropShadowEffect(this); //  这个设置内存管理
    dropShadow->setColor(Qt::black);
    dropShadow->setBlurRadius(3);
    // dx dy 左右偏移量
    dropShadow->setOffset(0,0);
    ui->loginBg->setGraphicsEffect(dropShadow);
}

////////////////////////
/// \brief Login::onMsgWayClicked
/// 切换按钮
void Login::onMsgWayClicked()
{
    ui->msgContain->show();
    ui->pdContain->hide(); // 密码登录
    ui->msgBtn->setStyleSheet(LOGIN_TOGGLE_BTNCHOOSED);
    ui->pdBtn->setStyleSheet(LOGIN_TOGGLE_BTNUNCHOOSED);
}
////////////////////////



////////////////////////
/// \brief Login::onPdWayClicked
///
void Login::onPdWayClicked()
{
    ui->msgContain->hide();
    ui->pdContain->show(); // 密码登录
    ui->msgBtn->setStyleSheet(LOGIN_TOGGLE_BTNUNCHOOSED);
    ui->pdBtn->setStyleSheet(LOGIN_TOGGLE_BTNCHOOSED);
}
////////////////////////


////////////////////////
/// \brief Login::onLoginNowBtnClicked
/// 登录按钮的点击
void Login::onLoginNowBtnClicked()
{
#ifdef LOGIN_TEST
    LOG() << "Login::onLoginNowBtnClicked()";

#endif
    auto dataCenter = model::DataCenter::getInstance();

    QString at = ui->atEdit->text();
    QString pd = ui->pdEdit->text();

#ifdef LOGIN_TEST
    LOG() << "用户点击了 (密码登录) 登录按钮";
    LOG() << "at:" << at;
    LOG() << "pd:" << pd;
#endif

    dataCenter->lrByPdAsync(at,pd);
}
////////////////////////



////////////////////////
/// \brief Login::onRegisterNowBtnClicked
/// 注册按钮的点击
void Login::onRegisterNowBtnClicked()
{
#ifdef LOGIN_TEST
    LOG() << "Login::onRegisterNowBtnClicked()";
    LOG() << "用户点击了 (密码注册) 注册按钮";
#endif
    auto dataCenter = model::DataCenter::getInstance();

    QString at = ui->atEdit->text();
    QString pd = ui->pdEdit->text();

    // dataCenter->lrByPdAsync(at,pd);
}
////////////////////////




////////////////////////
/// \brief Login::onAuthCodeBtnClicked
///
void Login::onAuthCodeBtnClicked()
{
    QString email = ui->emailEdit->text();
    auto dataCenter = model::DataCenter::getInstance();
    dataCenter->getCodeFromEmailAsync(email);
}
////////////////////////

////////////////////////
/// \brief Login::onGetCodeFromEmailDone
/// \param authCode
/// 获取验证码 成功
void Login::onGetCodeFromEmailDone(const QString &auth_code)
{
    authCode = auth_code;

    Toast::showMsg("获得的验证码是: "+auth_code);

#ifdef LOGIN_TEST
    LOG() << "Login::onGetCodeFromEmailDone(const QString &authCode)";
    LOG() << "验证码是" << auth_code;
#endif

}

////////////////////////
/// \brief Login::onLoginOrRegisterBtnClicked
///
void Login::onLoginOrRegisterBtnClicked()
{
    QString email = ui->emailEdit->text();

#ifdef LOGIN_TEST
    LOG() << "Login::onLoginOrRegisterBtnClicked()";
    LOG() << "邮箱是: " << email;
#endif

    auto dataCenter = model::DataCenter::getInstance();
    dataCenter->lrByAuthCodeAsync(email,authCode,codeId);
}
////////////////////////


////////////////////////
/// \brief Login::onPdBtnClicked
///
void Login::onPdBtnClicked()
{


}
////////////////////////


////////////////////////
/// \brief Login::onLrByAuthCodeFailed
/// \param msg
///
void Login::onLrByAuthCodeFailed(const QString &msg)
{
    Toast::showMsg("msg");

}
////////////////////////



////////////////////////
/// \brief Login::onLrByAuthCodeSuc
///
void Login::onLrByAuthCodeSuc()
{
    emit _loginSuc();
    close();
}
////////////////////////


////////////////////////
/// \brief Login::onLrByPdFailed
/// \param msg
///
void Login::onLrByPdFailed(const QString &msg)
{
    Toast::showMsg("登录失败..." + msg);
}
////////////////////////


////////////////////////
void Login::onLrByPdSuc()
{
    Toast::showMsg("登录成功...");
    emit _loginSuc();
    close();
}
////////////////////////




















