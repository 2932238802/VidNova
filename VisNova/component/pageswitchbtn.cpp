#include "pageswitchbtn.h"


///
/// \brief PageSwitchBtn::PageSwitchBtn
/// \param parent
/// 页面切换按钮
///
PageSwitchBtn::PageSwitchBtn(QWidget *parent):QPushButton{parent}
{
    // 设置按钮大小

    setFixedSize(48,46);
    icon = new QLabel(this);
    icon->setGeometry(12,0,24,24);
    icon->setAttribute(Qt::WA_TransparentForMouseEvents);

    text = new QLabel(this);
    text->setGeometry(0,30,48,16);
    text->setAttribute(Qt::WA_TransparentForMouseEvents);
}


///////////////////////////
/// \brief PageSwitchBtn::setImageAndText
/// \param imagePath
/// \param textContent
/// \param page_id
/// 设置图片和颜色
void PageSwitchBtn::setImageAndText(
    const QString &image_path,
    const QString &textContent,
    int page_id
    )
{
    icon->setPixmap(QPixmap(image_path));
    text->setText(textContent);
    icon->setScaledContents(true); // 让它比较好地填充
    text->setAlignment(Qt::AlignCenter); // 中心对齐
    this->pageId = page_id; // 索引给上
}

void PageSwitchBtn::mousePressEvent(QMouseEvent *event)
{
    // (void*)event;
    Q_UNUSED(event);
    // setTextColor("#000000"); // 高亮显示

#ifdef PAGESWITCHBTN_TEST
    LOG()<<"PageSwitchBtn::mousePressEvent(QMouseEvent *event)..." << "pageId 是" << pageId;
#endif
    emit switchPage(pageId);
}



///
/// \brief PageSwitchBtn::setTextColor
/// \param color
/// 内置颜色设置
void PageSwitchBtn::setTextColor(const QString &color)
{
    text->setStyleSheet("font-family: 微软雅黑;"
                            " font-size: 12px;"
                            "font-weight: bold;"
                        "color: " + color + ';');

}

///
/// \brief PageSwitchBtn::setImage
/// \param image_path
/// 设置图片
void PageSwitchBtn::setImage(const QString &image_path)
{
    icon->setPixmap(QPixmap(image_path));
}

int PageSwitchBtn::getPageId()
{
    return pageId;
}











