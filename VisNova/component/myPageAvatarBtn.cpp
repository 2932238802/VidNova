#include "myPageAvatarBtn.h"

MyPageAvatarBtn::MyPageAvatarBtn(QWidget *parent)
    : QPushButton{parent},showMask(true)
{
    mask = new QLabel(this);
    mask->setObjectName("myPageMaskForAvatar");
    mask->setGeometry(0,0,60,60);
    mask->setStyleSheet(MYPAGE_MASK_FOR_AVATAR);
    mask->setText("修改头像");
    mask->hide();
    mask->setAlignment(Qt::AlignCenter);
    mask->setAttribute(Qt::WA_TransparentForMouseEvents); // 让点击的逻辑 直接传到后面去
}

void MyPageAvatarBtn::setMaskState(bool is_mask)
{
    this->showMask = is_mask;
}

void MyPageAvatarBtn::enterEvent(QEnterEvent *event)
{
    if(showMask)
    {
        mask->show();
    }
}

void MyPageAvatarBtn::leaveEvent(QEvent *event)
{
    mask->hide();
}



