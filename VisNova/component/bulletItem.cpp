#include "bulletItem.h"


BulletInfo::BulletInfo(const QString &user_id, const QString &video_id, int64_t play_time, const QString text_out)
    : userId(user_id),videoId(video_id),playTime(play_time),text(text_out){}

BulletInfo::BulletInfo(const QString &user_id, int64_t play_time, const QString text_out)
: userId(user_id),playTime(play_time),text(text_out)
{}

BulletItem::BulletItem(QWidget *parent)
    : QFrame{parent}
{
    setObjectName("bulletItem");
    setFixedHeight(38);
    QHBoxLayout* layout= new QHBoxLayout(this);
    setLayout(layout);

    // 用户头像
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(30,30);
    imageLabel->setScaledContents(true); // 缩进
    imageLabel->hide();

    // 弹幕文本
    textLabel = new QLabel(this);
    textLabel->setStyleSheet(BULLET_TEXT);
    textLabel->adjustSize();
    layout->addWidget(imageLabel);
    layout->addWidget(textLabel);
    layout->setContentsMargins(10,4,19,4);
    layout->setSpacing(8);
}

/// \brief BulletItem::setText
/// \param text
/// 设置文本
void BulletItem::setText(const QString &text)
{
    textLabel->setText(text);
    textLabel->adjustSize();
}

/// \brief BulletItem::setIcon
/// \param pixmap
/// 设置头像
void BulletItem::setIcon(const QPixmap &pixmap)
{
    imageLabel->setPixmap(pixmap);
    imageLabel->show();
    this->setStyleSheet(BULLET);
}

void BulletItem::setAnimation(int xPos, int duration)
{
    // 第一个this 是 针对的对象 第二个this是父
    animation = new  QPropertyAnimation(this,"pos",this);
    animation->setDuration(duration);
    animation->setStartValue(QPoint(xPos,0));
    animation->setEndValue(QPoint(0-this->width(),0));

}

/// \brief BulletItem::startAnimation
/// 开启动画
void BulletItem::startAnimation()
{
    show();
    animation->start();

    // 确保元素被删除了
    connect(animation,&QPropertyAnimation::finished,this,&BulletItem::deleteLater);
}

















