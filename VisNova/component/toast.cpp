#include "toast.h"


Toast::Toast(const QString &msg)
{
    initUi(msg);
    // 两秒之后 关闭定时器
    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        timer->stop(); // 关闭时间
        this->close();
        this->deleteLater();
    });

    timer->start(2000);
}

Toast::Toast(const QString &msg, QWidget *widget)
{
    initUi(msg);
    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        timer->stop(); // 关闭时间
        this->close();
        this->deleteLater();
        if(widget)
        {
            widget->show();
        }
    });

    timer->start(2000);
}

void Toast::showMsg(const QString &msg)
{
    Toast* toast = new Toast(msg);
    toast->show();
}

void Toast::showMsg(const QString &msg, QWidget *widget)
{
    Toast* toast = new Toast(msg,widget);
    toast->show();
}

void Toast::initUi(const QString &msg)
{
    // 去除 窗口标题
    // Qt::Tool 这个是 浮动的
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    // 设置透明
    setAttribute(Qt::WA_TranslucentBackground);
    // 添加一个背景
    QWidget* toastBg = new QWidget(this);
    toastBg->setFixedSize(800,60);
    toastBg->setStyleSheet(TOAST_BG);

    // 垂直 布局
    QVBoxLayout* layout = new QVBoxLayout(toastBg); // toastBg 是父元素
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    // 设置到 布局
    toastBg->setLayout(layout);

    // 创建 QLabel 显示文本
    QLabel* label = new QLabel(toastBg);
    label->setText(msg);
    label->setAlignment(Qt::AlignCenter); // 水平和垂直 都居中
    label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding); // 大小策略
    label->setStyleSheet(TOAST_LABEL);
    layout->addWidget(label);
    QScreen* screen = QApplication::primaryScreen();
    int width = screen->size().width();
    int height = screen->size().height();
    int x = (width - this->width())/2;
    int y = height - this->height() - 100; // 减法 是往上走一点
    this->move(x,y);
}







