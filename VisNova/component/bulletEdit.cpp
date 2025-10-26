#include "bulletEdit.h"
 #include "ui_bulletEdit.h"

BulletEdit::BulletEdit(QWidget *parent)
    : QLineEdit(parent)
    , ui(new Ui::BulletEdit)
{
    ui->setupUi(this);
    ui->bulletTextEdit->setMaxLength(30);
    connect(ui->sendBtn,&QPushButton::clicked,this,&BulletEdit::onSendBtnClicked);
}

/////////////////////
/// \brief BulletEdit::mousePressEvent
/// \param event
///
void BulletEdit::mousePressEvent(QMouseEvent *event)
{
#ifdef BULLETEDIT_TEST
    LOG () << "BulletEdit::mousePressEvent(QMouseEvent *event)";
#endif

    auto dataCenter = model::DataCenter::getInstance();
    auto myselfInfo = dataCenter->getMyselfInfo();

    if(myselfInfo && myselfInfo->isTempUser())
    {
        if(placeholderText() != "请先登录和注册...")
        {
            setPlaceholderText("请先登录和注册...");
            ui->sendBtn->setText("登录");
        }
        else{
            Login * login = new Login(this);
            Toast::showMsg("请先登录或注册",login);
        }
    }
}



BulletEdit::~BulletEdit()
{
    delete ui;
}

void BulletEdit::onSendBtnClicked()
{

#ifdef BULLETEDIT_TEST
    LOG() << "BulletEdit::onSendBtnClicked()";
#endif

    if(ui->sendBtn->text() == "登录")
    {
        Login * login = new Login(this);

        connect(login,&Login::_loginSuc,this,[=](){

#ifdef BULLETEDIT_TEST
            LOG() << "登录成功... 修改ui...";
#endif
            ui->sendBtn->setText("发送");
            setPlaceholderText("说点什么吧~");
        });

        Toast::showMsg("请先登录或注册",login);
    }else{
        QString bulletText = text();
        if(bulletText.isEmpty())
        {
            Toast::showMsg("弹幕内容不为空哦~");
        }
    }

    emit sendBullet(ui->bulletTextEdit->text());
}


















