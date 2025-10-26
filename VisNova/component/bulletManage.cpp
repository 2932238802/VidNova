#include "bulletManage.h"

BulletManage::BulletManage(QWidget *parent,int x_parent,int y_parent)
    : QDialog{parent},isHide(false)
{
    this ->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMinimumSize(parent->width(),38*3);

    QVBoxLayout* layout = new QVBoxLayout(this);
    this->setLayout(layout);

    topBlt = new QFrame(this);
    topBlt->setFixedSize(parent->width(),38);

    middleBlt = new QFrame(this);
    middleBlt->setFixedSize(parent->width(),38);

    bottomBlt = new QFrame(this);
    bottomBlt->setFixedSize(parent->width(),38);

#ifdef PLAYERPAGE_TEST_FOR_BULLET
    // topBlt->setStyleSheet(PLAYERPAGE_TEST_BACKGROUND_FOR_TOP);
    // middleBlt->setStyleSheet(PLAYERPAGE_TEST_BACKGROUND_FOR_MIDDLE);
    // bottomBlt->setStyleSheet(PLAYERPAGE_TEST_BACKGROUND_FOR_BOTTOM);
#endif

    layout->addWidget(topBlt);
    layout->addWidget(middleBlt);
    layout->addWidget(bottomBlt);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    QPoint point({x_parent,y_parent});
    this->move(point);
    this->show();
}

void BulletManage::buildBulletItems(const QString& video_id)
{
    auto dataCenter = model::DataCenter::getInstance();
    dataCenter->getBulletsAsync(video_id); // 这个要发送一个信号

    // QList<model::BulletInfo> bulletItems;

    // for(int i =0 ; i < 3; i++)
    // {
    //     model::BulletInfo bsItem("100",i,"我是弹幕" + QString::number(i));
    //     bulletItems.append(bsItem);
    //     bulletItemInfoMap.insert(bsItem.playTime,bulletItems);
    //     bulletItems.clear();
    // }
    // for(int i = 0; i < 4; i++)
    // {
    //     model::BulletInfo bsItem("100" , 5 , "我是弹幕" + QString::number(i));
    //     bulletItems.append(bsItem);
    // }
    // bulletItemInfoMap.insert(5,bulletItems);
}

void BulletManage::showBulletBySecond(int64_t second)
{
    if(isHide) return; // true 就返回 意思是说 true就表示隐藏

    QList<model::BulletInfo> bullets = bulletItemInfoMap.value(second);
    // 弹幕显示出来
    BulletItem* item = nullptr;
    int xTop; int xMid; int xBtm;
    xTop = xMid = xBtm = topBlt->width();
    for(int i= 0; i<bullets.size(); i++)
    {
        model::BulletInfo& info = bullets[i];
        if(i%3 == 0)
        {
            int duration = 10000* xTop /(double)(topBlt->width()+30*18);
            // 第一行
            item = new BulletItem(topBlt);
            item->setText(info.text);
            item->setAnimation(xTop,duration);
            // 四个字符 每个字符 18 像素
            xTop+= item->width()+4*18;

        }else if(i%3 == 1){
            int duration = 10000* xMid /(double)(middleBlt->width()+30*18);
            item = new BulletItem(middleBlt);
            item->setText(info.text);
            item->setAnimation(xMid,duration);
            // 四个字符 每个字符 18 像素
            xMid+= item->width()+4*18;

        }else{
            int duration = 10000* xBtm /(double)(bottomBlt->width()+30*18);
            item = new BulletItem(bottomBlt);
            item->setText(info.text);
            item->setAnimation(xBtm,duration);
            // 四个字符 每个字符 18 像素
            xBtm+= item->width()+4*18;
        }
        item->startAnimation(); // 开始运动
    }
}

void BulletManage::setBulletStateForHide(bool is_hide)
{
    isHide = is_hide;
}


///////////////////////////////////////
/// \brief BulletManage::pauseBullet
/// 弹幕的暂停
void BulletManage::pauseBullet()
{

}
///////////////////////////////////////



///////////////////////////////////////
/// \brief BulletManage::resumeBullet
/// 弹幕的开始
void BulletManage::resumeBullet()
{

}
///////////////////////////////////////


///////////////////////////////////////
/// \brief BulletManage::openOrCloseBullet
///
void BulletManage::openOrCloseBullet()
{

}
///////////////////////////////////////



///////////////////////////////////////
/// \brief BulletManage::getTopWidth
/// \return
///
int BulletManage::getTopWidth() const
{
    return topBlt->width();
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief BulletManage::getDefaultDuration
/// \return
///
int64_t BulletManage::getDefaultDuration()
{
    return 10000* topBlt->width() / (double)(topBlt->width() + 30 * 18);
}
///////////////////////////////////////


///////////////////////////////////////
/// \brief BulletManage::buildBullet
/// \param position
/// \return
///
BulletItem *BulletManage::buildBullet(BulletPosition position)
{
    BulletItem* item = nullptr;
    if(position == BulletPosition::TOP)
    {
        item = new BulletItem(topBlt);
    }
    else if(position == BulletPosition::MIDDLE)
    {
        item = new BulletItem(middleBlt);
    }
    else if(position == BulletPosition::BOTTOM)
    {
        item = new BulletItem(bottomBlt);
    }
    else{
        item = new BulletItem(topBlt);
    }
    QPixmap pixmap{":/image/txMan.png"};
    item->setIcon(pixmap);
    item->setAnimation(getTopWidth(),getDefaultDuration());

    return item;
}
///////////////////////////////////////



///////////////////////////////////////
/// \brief BulletManage::getVideoBulletSuccess
/// \param videoId
///
void BulletManage::getVideoBulletSuccess(const QString &videoId)
{
    auto dataCenter = model::DataCenter::getInstance();
    bulletItemInfoMap = dataCenter->getBullets();
}
///////////////////////////////////////












