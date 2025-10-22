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

    initConnect();
    startTimer();
}
void StartPage::startTimer()
{
    QTimer* timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, &QTimer::timeout, this, [=]{
        if (isLoadCompleted) // 只检查这一个标志位
        {
            LOG() << "加载流程完成，关闭启动页。";
            timer->stop();
            delete timer;
            emit _loginCompleted();
            close();
        }
    });

    timer->start(2000);
    auto dataCenter = model::DataCenter::getInstance();
    QString sessionId = dataCenter->getSessionId();


    dataCenter->loginBySessionAsync();

}

////////////////////////////////////
/// \brief StartPage::initConnect
///
void StartPage::initConnect()
{
#ifdef STARTPAGE_TEST
    LOG() << "StartPage::initConnect()... ";
#endif

    auto dataCenter = model::DataCenter::getInstance();

    connect(dataCenter, &model::DataCenter::_loginBySessionSuc, this, [=](bool isTempUser){
        if (isTempUser) {

#ifdef STARTPAGE_TEST
            LOG() << "是临时用户，直接完成。";
#endif

            isLoadCompleted = true;
            dataCenter->loadTempUserInfo();

            emit dataCenter->_getMyselfInfoDone();

        } else {

#ifdef STARTPAGE_TEST
            LOG() << "不是临时用户 获取信息中...";
#endif
            dataCenter->getMyselfInfoAsync();
        }
    });

    connect(dataCenter, &model::DataCenter::_loginBySessionFailed, this, [=](const QString& msg){
#ifdef STARTPAGE_TEST
        LOG() << "Session登录失败: " << msg;
#endif

        Toast::showMsg("自动登录失败，将以临时用户身份继续");
        dataCenter->loadTempUserInfo();
        emit dataCenter->_getMyselfInfoDone();
        isLoadCompleted = true;
    });


    connect(dataCenter, &model::DataCenter::_getMyselfInfoDone, this, [=](){

#ifdef STARTPAGE_TEST
        LOG() << "获取个人信息成功";
#endif
        isLoadCompleted = true;
    });
}

////////////////////////////////////




















