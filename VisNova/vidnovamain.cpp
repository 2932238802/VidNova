#include "vidnovamain.h"
#include "ui_vidnovamain.h"

VidNovaMain* VidNovaMain::instance = nullptr;

//////////////////////////////
/// \brief VidNovaMain::VidNovaMain
/// \param parent
/// 初始化 包括 调用一些 初始化的函数
VidNovaMain::VidNovaMain(QWidget *parent)
    : QWidget(parent),
    isDragging(false)
    , ui(new Ui::VidNovaMain)
{
    ui->setupUi(this);

    setStyleSheet("background-color:#FFFFFF");

    initUi();

    connectSignalAndSlot();
}
//////////////////////////////


//////////////////////////////
/// \brief VidNovaMain::initUi
/// 初始化 阴影 边框 一些图标
void VidNovaMain::initUi()
{
    // 去除 边框
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // 窗口的图标
    // 就是 任务栏的边框
    QIcon icon(":/image/logo.png");
    setWindowIcon(icon);

    // 设置阴影效果
    // 弄到对象树上面
    QGraphicsDropShadowEffect* dropShodow = new QGraphicsDropShadowEffect(this);
    dropShodow->setColor(Qt::black);
    dropShodow->setBlurRadius(5);
    dropShodow->setOffset(0,0);    // 因为 x和y 分别是上方和左边 所以 10 10 是右下角的偏移量
    ui->VidNovabg->setGraphicsEffect(dropShodow); // 添加阴影给ui层 效果

    ui->homePageBtn->setTextColor(BODY_LEFT_BUTTON_PRESS_FONT_COLOR);
    ui->homePageBtn->setImageAndText(
        ":/image/homePage.png",
        "首页",
        StackWidgetPage::HOME_PAGE
        );

    ui->myPageBtn->setTextColor(BODY_LEFT_BUTTON_UNPRESS_FONT_COLOR);
    ui->myPageBtn->setImageAndText(
        ":/image/myPage.png",
        "我的",
        StackWidgetPage::MY_PAGE
        );

    // 让字体 变成黑色
    ui->sysPageBtn->setTextColor(BODY_LEFT_BUTTON_UNPRESS_FONT_COLOR);
    ui->sysPageBtn->setImageAndText(
        ":/image/sysPage.png",
        "管理",
        StackWidgetPage::SYSTEM_PAGE
        );
}

///
/// \brief VidNovaMain::connectSignalAndSlot
/// 1. 绑定信号槽
void VidNovaMain::connectSignalAndSlot()
{
    // 第三个参数 是信号的接受者
    connect(ui->minBtn,&QPushButton::clicked,this,&QWidget::showMinimized);
    connect(ui->quitBtn,&QPushButton::clicked,this,&QWidget::close);

    connect(ui->homePageBtn,&PageSwitchBtn::switchPage,this,&VidNovaMain::onlySwitchPage);
    connect(ui->myPageBtn,&PageSwitchBtn::switchPage,this,&VidNovaMain::onSwitchPageAndUpdataUi);
    connect(ui->sysPageBtn,&PageSwitchBtn::switchPage,this,&VidNovaMain::onlySwitchPage);

    connect(ui->myPage,&MyPage::switchUploadVideoPage,this,&VidNovaMain::onlySwitchPage);

    connect(ui->uploadVedioPage,&UploadVideoPage::returnMyPage,this,&VidNovaMain::onlySwitchPage);
}



///
/// \brief VidNovaMain::resetSwitchButton
/// \param getPageId
/// 重置按钮颜色
void VidNovaMain::resetSwitchButton(int page_id)
{
    QList<PageSwitchBtn*> switch_buttons = findChildren<PageSwitchBtn*>();
    for(auto a: switch_buttons)
    {
        if(a->getPageId() != page_id)
        {
            a->setTextColor(BODY_LEFT_BUTTON_UNPRESS_FONT_COLOR); // 没有点击 设置成灰色
        }
        else{
            a->setTextColor(BODY_LEFT_BUTTON_PRESS_FONT_COLOR); // 000 是变色
        }
    }

    // 设置对应 图片
    if(page_id==StackWidgetPage::HOME_PAGE)
    {
        // 图片设置
        ui->homePageBtn->setImage(":/image/homePagexuan.png");
        ui->myPageBtn->setImage(":/image/myPage.png");
        ui->sysPageBtn->setImage(":/image/sysPage.png");
    }
    else if(page_id == StackWidgetPage::MY_PAGE)
    {
        ui->homePageBtn->setImage(":/image/homePage.png");
        ui->myPageBtn->setImage(":/image/myPagexuan.png");
        ui->sysPageBtn->setImage(":/image/sysPage.png");
    }
    else{
        ui->homePageBtn->setImage(":/image/homePage.png");
        ui->myPageBtn->setImage(":/image/myPage.png");
        ui->sysPageBtn->setImage(":/image/sysPagexuan.png");
    }
}

///
/// \brief VidNovaMain::mousePressEvent
/// \param event
/// 用于窗口拖拽
void VidNovaMain::mousePressEvent(QMouseEvent *event)
{

    // 因为 position 获得是 QPointf
    // 浮点数坐标转换成整数坐标 QPoint
    QPoint point = event->position().toPoint();
    if(event->button() == Qt::LeftButton && ui->head->geometry().contains(point))
    {
        // 表示在 head上面 进行点击
        dragPosition = point;
        isDragging = true;
        event->accept(); // 表示我自己处理 掉了
        return;
    }
    isDragging = false;
}

///
/// \brief VidNovaMain::mouseMoveEvent
/// \param event
/// 用于窗口拖拽
void VidNovaMain::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton && isDragging)
    {
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
        return;
    }
}

///
/// \brief VidNovaMain::mouseReleaseEvent
/// \param event
/// 鼠标松开
void VidNovaMain::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        isDragging = false;
    }
}



////////////////////////
/// \brief VidNovaMain::onSwitchPageAndUpdataUi
/// \param page_id
///
void VidNovaMain::onSwitchPageAndUpdataUi(int page_id)
{
#ifdef VIDNOVAMAIN_TEST
    LOG() << "进入VidNovaMain::onSwitchPageAndUpdataUi(int page_id)函数... " << "page_id是:" << page_id;
#endif

    ui->stackedWidget->setCurrentIndex(page_id);
    resetSwitchButton(page_id);
    if(page_id == StackWidgetPage::MY_PAGE)
    {
        ui->myPage->loadMyselfInfoAndVideo();
    }
}
////////////////////////



////////////////////////
/// \brief getInstance::~getInstance
/// 析构
VidNovaMain *VidNovaMain::getInstance()
{
    if(instance == nullptr)
    {
        instance = new VidNovaMain();
    }
    return instance;
}
////////////////////////



////////////////////////
/// \brief VidNovaMain::showSystemBtn
/// \param is_show
///
void VidNovaMain::showSystemBtn(bool is_show)
{
    if(is_show)
    {
        ui->sysBtn->show();
    }
    else{
        ui->sysBtn->hide();
    }
}
////////////////////////



////////////////////////
/// \brief VidNovaMain::switchMyPageForOtherUser
/// \param user_id
/// 更换到 个人界面 显示其它用户
void VidNovaMain::switchMyPageForOtherUser(const QString &user_id)
{
#ifdef VIDNOVAMAIN_TEST
    LOG() << "switchMyPageForOtherUser()";
    LOG() << "由于点击了视频播放中的 其它用户的头像 所以展示其它用户的个人信息:";
    LOG() << "user_id 是" << user_id;
#endif

    // 切换界面
    onlySwitchPage(StackWidgetPage::MY_PAGE);

    // 加载其它用户的个人信息
    ui->myPage->loadOtherUserInfoAndVideo(user_id);
}


////////////////////////
/// \brief VidNovaMain::onlySwitchPage
/// \param page_id
///
void VidNovaMain::onlySwitchPage(int page_id)
{
    ui->stackedWidget->setCurrentIndex(page_id);
    resetSwitchButton(page_id);
}
////////////////////////




