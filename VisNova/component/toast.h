#pragma once
#include <QWidget>
#include <QDialog>
#include<QVBoxLayout>
#include<QLabel>
#include<QTimer>
#include<QApplication>
#include<QScreen>
#include "style.h"

class Toast : public QDialog
{
    Q_OBJECT
public:
    // 仅仅显示 文本
    Toast(const QString& msg);

    // 显示完 文本 显示窗口
    Toast(const QString&msg,QWidget* widget);
    static void showMsg(const QString& msg);
    static void showMsg(const QString& msg,QWidget* widget);

private:
    void initUi(const QString& msg);
};


