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
    connectInit();
    inputInit();
    ui->msgContain->show();
    ui->pdContain->hide(); // 密码登录
}

Login::~Login()
{
    delete ui;
}

void Login::connectInit()
{
    connect(ui->minBtn,&QPushButton::clicked,this,&QWidget::showMinimized);
    connect(ui->quitBtn,&QPushButton::clicked,this,&QWidget::close);
    connect(ui->msgBtn,&QPushButton::clicked,this,&Login::onMsgBtnClicked);
    connect(ui->pdBtn,&QPushButton::clicked,this,&Login::onPdBtnClicked);
}

///
/// \brief Login::inputInit
/// 输入框 限制一下
void Login::inputInit()
{
    QRegularExpression regularExpression("^1\\d{10}$"); // 从%^ 开始 $ 结束
    QValidator *validator = new QRegularExpressionValidator(regularExpression,this);
    ui->phoneEdit->setValidator(validator);

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

///
/// \brief Login::onMsgBtnClicked
/// 切换按钮
void Login::onMsgBtnClicked()
{
    ui->msgContain->show();
    ui->pdContain->hide(); // 密码登录
    ui->msgBtn->setStyleSheet(LOGIN_TOGGLE_BTNCHOOSED);
    ui->pdBtn->setStyleSheet(LOGIN_TOGGLE_BTNUNCHOOSED);
}

void Login::onPdBtnClicked()
{
    ui->msgContain->hide();
    ui->pdContain->show(); // 密码登录
    ui->msgBtn->setStyleSheet(LOGIN_TOGGLE_BTNUNCHOOSED);
    ui->pdBtn->setStyleSheet(LOGIN_TOGGLE_BTNCHOOSED);
}












