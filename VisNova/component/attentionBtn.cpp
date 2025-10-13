#include "attentionBtn.h"

AttentionBtn::AttentionBtn(QWidget  *parent)
    : QPushButton{parent}
{
    setEnabled(true);
    setAttention(false);
}

////////////////////
/// \brief AttentionBtn::isAttention
/// \return
///
bool AttentionBtn::isAttention()
{
    return isAttentioned;
}
////////////////////



////////////////////
/// \brief AttentionBtn::setAttention
/// \param b
///
void AttentionBtn::setAttention(bool b)
{
#ifdef ATTENTIONBTN_TEST
    LOG () << "setAttention(bool b)";
    LOG () << "b:" << b;
#endif

    isAttentioned = b;
    if(isAttentioned == true)
    {
        this->setText("已关注");
        this->setStyleSheet(MYPAGE_ATTENTIONED_BTN);
        // this->setIconSize(QSize(24,24));
    }
    else{
        this->setText("关注");
        this->setStyleSheet(MYPAGE_UNATTENTIONED_BTN);
    }
}
////////////////////
