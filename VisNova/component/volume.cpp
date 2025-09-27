#include "volume.h"
#include "ui_volume.h"

Volume::Volume(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Volume)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->volumeBg->installEventFilter(this); // 拦截器
}

/////////////////////////////////////////////////////////
/// \brief Volume::eventFilter
/// \param watched
/// \param event
/// \return
/// 拦截器
bool Volume::eventFilter(QObject *watched, QEvent *event)
{
    if(ui->volumeBg == watched)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            alter();
        }
        else if(event->type() == QEvent::MouseButtonRelease){

            emit volumeSignals(volume);

        }else if(event->type() == QEvent::MouseMove){
            alter();
            emit volumeSignals(volume);
        }
        return true;
    }

    return QObject::eventFilter(watched,event);
}
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
/// \brief Volume::alter
///
void Volume::alter()
{
    // 先获取 y 坐标
    // 将 全局坐标 转化为 窗口内部的坐标
    int y = ui->volumeBg->mapFromGlobal(QCursor().pos()).y();
    y = y < 5 ? 5:y;
    y = y > 150 ? 150 : y;
    ui->outLine->setGeometry(ui->outLine->x(),y,ui->outLine->width(),150 - y);

    int toY = ui->outLine->y()- ui->volumeBtn->height()/2;
    if(toY > 140)
    {
        toY = 140;
    }
    ui->volumeBtn->move(ui->volumeBtn->x(),toY);

    // 上面是把 距离更新了
    // 下面还要计算一下 音量大小
    volume = ui->outLine->height()/(double)145 * 100;
    LOG()<<"音量大小: "<<volume;
}
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
/// \brief Volume::~Volume
///
Volume::~Volume()
{
    delete ui;
}
/////////////////////////////////////////////////////////
