#pragma once
#include <QObject>
#include <QDialog>
#include <QFrame>
#include <QWidget>
#include "common/myLog.h"
#include "bulletItem.h"

enum class BulletPosition{
    TOP = 0,
    MIDDLE,
    BOTTOM
};

class BulletManage : public QDialog
{
    Q_OBJECT
public:
    explicit BulletManage(QWidget *parent = nullptr,int x_parent = 0,int y_parent = 0);
    void buildBulletItems();
    void showBulletBySecond(int64_t second);
    void setBulletStateForHide(bool isHide);
    void pauseBullet(); // 暂停动画
    void resumeBullet(); // 恢复动画
    void openOrCloseBullet(); // 弹幕的隐藏和打开
    int getTopWidth() const;
    int getMiddleWidth() const;
    int getBottomWidth() const;
    int64_t getDefaultDuration();
    BulletItem* buildBullet(BulletPosition position);

private:
    bool isHide;
    QFrame* topBlt;
    QFrame* middleBlt;
    QFrame* bottomBlt;
    QMap<int64_t,QList<BulletInfo>> bulletItemInfoMap;

signals:

};


