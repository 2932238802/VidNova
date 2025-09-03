#pragma once
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>
#include "style.h"

class MyPageAvatarBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPageAvatarBtn(QWidget *parent = nullptr);
    void setMaskState(bool is_mask);

private:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

signals:

private:
    bool showMask;
    QLabel* mask;
};

