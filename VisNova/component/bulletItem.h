#pragma once
#include <QWidget>
#include <QFrame>
#include <QLabel>
#include<QHBoxLayout>
#include<QPropertyAnimation>
#include"style.h"


class BulletItem : public QFrame
{
    Q_OBJECT
public:
    explicit BulletItem(QWidget *parent = nullptr);
    void setText(const QString& text);
    void setIcon(const QPixmap& pixmap);
    void setAnimation(int xPos,int duration); // 给弹幕项 设置动画效果
    void startAnimation(); // 开启动画

private:
    QLabel* textLabel; // 文本 弹幕中
    QLabel* imageLabel; // 弹幕中用户头像
    QPropertyAnimation* animation; // 动画
};


