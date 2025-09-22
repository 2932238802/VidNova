#include "pageBtn.h"

PageBtn::PageBtn(int page_number,QWidget *parent)
    : QPushButton{parent},pageNumber(page_number)
{
    // 设置按钮的尺寸和图标的尺寸
    setFixedSize(32,32);
    setIconSize(QSize{16,16});


    // 设置按钮样式 根据是不是被折叠
    if(isFolded)
    {
        // 折叠
        setText("···");
    }
    else{
        setText(QString::number(pageNumber));
    }

    // setActive()
}


///
/// \brief PageBtn::setActive
/// \param is
/// 设置和获取状态
void PageBtn::setActive(bool is)
{
    isActived = is;

    if(isActived)
    {
        setStyleSheet(PAGE_BUTTON_FENYEQI_ACTIVED);
    }
    else{
        setStyleSheet(PAGE_BUTTON_FENYEQI_UNACTIVED);
    }
}

void PageBtn::setFolded(bool is)
{
    isFolded = is;
    if(isFolded)
    {
        setText("···");
    }
    else{
        setText(QString::number(pageNumber));
    }
}

void PageBtn::setPageNumber(int number)
{
    pageNumber = number;
    setText(QString::number(number));
}

int PageBtn::getPageNumber() const
{
    return pageNumber;
}

bool PageBtn::getFolded() const
{
    return isFolded;
}

bool PageBtn::getActived() const
{
    return isActived;
}


