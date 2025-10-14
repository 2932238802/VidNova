#pragma once
#include"style.h"
#include <QDialog>
#include<QRegularExpression>
#include<QRegularExpressionValidator>
#include<QGraphicsDropShadowEffect>
#include "dataCenter/dataCenter.h"
#include "toast.h"

namespace Ui {
class Login;
}

///
/// \brief The Login class
/// 1. QDialog 对话框
class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    void initConnect(); // 连接 信号初始化
    void inputInit();
    void styleInit();

private slots:
    void onMsgWayClicked(); // 短线的方式登录的 ui设置
    void onPdWayClicked(); // 密码的方式登录的 ui设置
    void onLoginNowBtnClicked();
    void onRegisterNowBtnClicked();
    void onAuthCodeBtnClicked();
    void onGetCodeFromEmailDone(const QString& authCode);

    void onLoginOrRegisterBtnClicked();
    void onPdBtnClicked(); // 登录方式的 登录按钮 的点击 槽函数

    void onLrByAuthCodeFailed(const QString&msg);
    void onLrByAuthCodeSuc();

    void onLrByPdFailed(const QString&msg);
    void onLrByPdSuc();

signals:
    void _loginSuc();

private:
    Ui::Login *ui;
    QString authCode;
    QString codeId;
};


