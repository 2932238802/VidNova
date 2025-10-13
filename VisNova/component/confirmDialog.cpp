#include "confirmDialog.h"

ConfirmDialog::ConfirmDialog(QWidget *parent)
    : QDialog{parent}
{
    setWindowFlag(Qt::FramelessWindowHint); // 没有默认边框
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(1450,880);


    VidNovaMain* vid =  VidNovaMain::getInstance();
    // QPoint point = vid->mapToGlobal(QPoint(0,0)); // 获取左上角的坐标
    this->setParent(vid);
    move(0,0); // 移动到 左上角坐标

    QWidget* bg = new QWidget(this);
    bg->setObjectName("bgForConfirmBackground");
    bg->setFixedSize(this->maximumSize());
    bg->setStyleSheet(BG_FOR_CONFIRMBACKGROUND);

    QFrame* frame = new QFrame(bg);
    frame->setObjectName("content");
    frame->setFixedSize(358,169);
    frame->move(546,346);

    frame->setStyleSheet(CONTENT_FOR_CONFIRMBACKGROUND);

    textLabel =new QLabel("确认",frame);
    textLabel->setStyleSheet(TEXT_LABEL_FOR_CONFIRMBACKGROUND);
    textLabel->move(115,40);

    QPushButton* confirmBtn = new QPushButton("确认",frame);
    QPushButton* cancelBtn = new QPushButton("取消",frame);

    confirmBtn->setStyleSheet(CONFIRM_BTN_FOR_CONFIRMBACKGROUND);
    cancelBtn->setStyleSheet(CANCEL_BTN_FOR_CONFIRMBACKGROUND);

    confirmBtn->setFixedSize(100,38);
    confirmBtn->move(194,111);

    cancelBtn->setFixedSize(100,38);
    cancelBtn->move(64,111);

    connect(confirmBtn,&QPushButton::clicked,this,[=](){
        isConfirm = true;
        close();

#ifdef CONFIRM_DIALOG_TEST
        LOG() << "ConfirmDialog(QWidget *parent)";
        LOG() << "用户点击了确定 ...";
#endif

    });

    connect(cancelBtn,&QPushButton::clicked,this,[=](){
        isConfirm = false;
        close();

#ifdef CONFIRM_DIALOG_TEST
        LOG() << "ConfirmDialog(QWidget *parent)";
        LOG() << "用户点击了取消 ...";
#endif

    });
}

/////////////////////
/// \brief ConfirmDialog::getConfirm
/// \return
///
bool ConfirmDialog::getConfirm() const
{
    return isConfirm;
}
/////////////////////



/////////////////////
/// \brief ConfirmDialog::setText
/// \param text
/// 设置文本
void ConfirmDialog::setText(const QString &text)
{
    if(textLabel)
    {
        textLabel->setText(text);
    }
}
/////////////////////



















