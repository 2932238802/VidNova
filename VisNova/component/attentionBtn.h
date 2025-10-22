#pragma once
#include <QObject>
#include <QPushButton>
#include "style.h"
#include "myLog.h"

// 关注按钮的自定义类
class AttentionBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit AttentionBtn(QWidget  *parent = nullptr);

    bool isAttention(); //
    void setAttention(bool b);


private:
    bool isAttentioned = false; // 默认没有关注

};


