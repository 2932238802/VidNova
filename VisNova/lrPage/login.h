#pragma once
#include"style.h"
#include <QDialog>
#include<QRegularExpression>
#include<QRegularExpressionValidator>
#include<QGraphicsDropShadowEffect>

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
    void connectInit(); // 连接 信号初始化
    void inputInit();
    void styleInit();

private slots:
    void onMsgBtnClicked();
    void onPdBtnClicked();

private:
    Ui::Login *ui;
};


