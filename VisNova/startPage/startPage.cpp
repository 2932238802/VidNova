#include "startPage.h"
#include <QDir>

StartPage::StartPage(QDialog *parent)
    : QDialog{parent}
{
    // 让窗口没有边框
    // setWindowFlags 可以设置 多个标签
    // Qt::Tool 这个表示是 工具窗口 就不会在任务栏 显示
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);

    // 图片
    setFixedSize(1450,860);
    setStyleSheet("background-color: #FFFFFF");
    QLabel* label = new QLabel(this);              // 挂载到父组件
    QPixmap logo(":/image/logo.png");

    if(logo.isNull())
    {
        qDebug()<<"[WA] 无法加载出图片!";
    }else{
        label->setPixmap(logo);
    }
    label->move(450,280);                           // 这个是窗口的位置

    // 文字
    QLabel* text = new QLabel(this);                // 项目名字设置
    text->setText(QString("VidNova!"));
    text->move(650,350);
    text->setStyleSheet("font-family: 'Microsoft YaHei', 'SimHei', Arial, sans-serif;"
                        "font-size: 48px;"
                        "font-weight: bold;"
                        "color: #2C3E50;"
                        "background-color: transparent;"
                        );


    startTimer();
}

void StartPage::startTimer()
{
    QTimer* timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer,&QTimer::timeout,this,[this,timer]{
        timer->stop();
        delete timer;
        close();
    });


    timer->start(2000);

    auto dataCenter = model::DataCenter::getInstance();
    dataCenter->tempLoginAsync();

    // 完成用户的自动登录 和 获取信息
    // TODO ...
}

////////////////////////////////////
/// \brief StartPage::initConnect
///
void StartPage::initConnect()
{
    auto dataCenter = model::DataCenter::getInstance();
    connect(dataCenter,&model::DataCenter::_loginSucDone,this,&StartPage::onTempLogin);

}
////////////////////////////////////



////////////////////////////////////
/// \brief StartPage::onTempLogin
///
void StartPage::onTempLogin()
{
    isLoginIn = true;
}
////////////////////////////////////
















