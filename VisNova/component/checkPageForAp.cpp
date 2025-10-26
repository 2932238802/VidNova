#include "checkPageForAp.h"
#include "ui_checkPageForAp.h"


////////////////////////
/// \brief CheckPageForAp::CheckPageForAp
/// \param parent
///
CheckPageForAp::CheckPageForAp(QWidget *parent):
    QWidget{parent},
    ui(new Ui::CheckPageForAp)
{

#ifdef CHECKPAGEFORAP_TEST
    LOG()<<"CheckPageForAp::CheckPageForAp(QWidget *parent)";
#endif

    ui->setupUi(this);
    ui->stateCombox->addItem("全部分类");
    ui->stateCombox->addItem("待审核");
    ui->stateCombox->addItem("审核通过");
    ui->stateCombox->addItem("审核驳回");
    ui->stateCombox->addItem("已下架");
    // ui->statusCombox->addItem("转码中");
    ui->stateCombox->setCurrentIndex(0);

    l_paginator = std::make_unique<Paginator>(0,ui->paginatorArea); // 分页器
    l_paginator->move(0,15);
    l_paginator->show();

    QRegularExpression reg("^[0-9a-f]{4}-[0-9a-f]{8}-[0-9a-f]{4}$");
    QValidator* validator = new QRegularExpressionValidator(reg);
    ui->idEdit->setValidator(validator);

    // updateCheckPage();

    initConnect();
}
////////////////////////



////////////////////////
/// \brief CheckPageForAp::~CheckPageForAp
///
CheckPageForAp::~CheckPageForAp()
{
    delete ui;

}
////////////////////////



////////////////////////
/// \brief CheckPageForAp::onQueryBtnClicked
/// 查询按钮 点击
void CheckPageForAp::onQueryBtnClicked()
{
#ifdef CHECKPAGEFORAP_TEST
    LOG()<<"CheckPageForAp::onQueryBtnClicked()";
    LOG()<<"点击了查询按钮";
#endif

    ui->queryBtn->setStyleSheet(R"(
    background-color: #3ECEFE;
    border-radius: 5px;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #FFFFFF;
)");
    ui->resetBtn->setStyleSheet(R"(
    background-color: #FFFFFF;
    border-radius: 4px;
    border: 1px solid #DCDEE0;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #222222;
)");

    if(checkState()) getVideoList(1);
    else{
        Toast::showMsg("对不起您现在被禁用了此项功能...");
    }
}
////////////////////////



////////////////////////
/// \brief CheckPageForAp::onResetBtnClicked
///
void CheckPageForAp::onResetBtnClicked()
{
#ifdef CHECKPAGEFORAP_TEST
    LOG() << "CheckPageForAp::onResetBtnClicked()";
    LOG()<<"点击了重置按钮";
#endif

    ui->resetBtn->setStyleSheet(R"(
    background-color: #3ECEFE;
    border-radius: 5px;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #FFFFFF;
)");
    ui->queryBtn->setStyleSheet(R"(
    background-color: #FFFFFF;
    border-radius: 4px;
    border: 1px solid #DCDEE0;
    font-family: '微软雅黑';
    font-size: 14px;
    color: #222222;
)");

    ui->idEdit->setText("");
    ui->stateCombox->setCurrentIndex(0);
    auto dataCenter = model::DataCenter::getInstance();
    auto manageVideoLists = dataCenter->getManageSearchVideoList();
    manageVideoLists->videoInfoLists.clear(); // 这个清空就可以了
    QLayoutItem* item = nullptr;
    while(nullptr != (item = ui->layout->takeAt(0)))
    {
        delete item->widget();
        delete item;
    }

    if(checkState()) getVideoList(1);
    else{
        Toast::showMsg("对不起您现在被禁用了此项功能...");
    }
}
////////////////////////



////////////////////////
/// \brief CheckPageForAp::onGetVideoListForMyselfOrOtherDone
/// \param userId
/// \param page
/// 视频 获取 完毕 加载..
// 在 checkPageForAp.cpp 中修改和实现
void CheckPageForAp::onGetVideoListForMyselfOrOtherDone(const QString &userId, model::GetVideoPage page)
{
    if (page != model::GetVideoPage::ManagePage) {
        return;
    }
#ifdef CHECKPAGEFORAP_TEST
    LOG() << "CheckPageForAp::onGetVideoListForMyselfOrOtherDone(const QString &userId, model::GetVideoPage page)";
#endif
    updateVideoListUI();
}
////////////////////////



////////////////////////
/// \brief CheckPageForAp::onGetVideoByStateDone
///
void CheckPageForAp::onGetVideoByStateDone()
{
#ifdef CHECKPAGEFORAP_TEST
    LOG() << "CheckPageForAp::onGetVideoByStateDone()";
#endif
    updateVideoListUI();
}
////////////////////////



////////////////////////
/// \brief CheckPageForAp::initConnect
/// 信号绑定
void CheckPageForAp::initConnect()
{
    auto dataCenter = model::DataCenter::getInstance();
    connect(ui->resetBtn,&QPushButton::clicked,this,&CheckPageForAp::onResetBtnClicked);
    connect(ui->queryBtn,&QPushButton::clicked,this,&CheckPageForAp::onQueryBtnClicked);
    connect(dataCenter,&model::DataCenter::_getVideoListForMyselfOrOtherDone,this,&CheckPageForAp::onGetVideoListForMyselfOrOtherDone);

    connect(dataCenter,&model::DataCenter::_getVideoByStateDone,this,&CheckPageForAp::onGetVideoByStateDone);

    connect(ui->stateCombox, &QComboBox::currentIndexChanged, this, [=](int index){
        ui->idEdit->clear();
    });

    connect(l_paginator.get(), &Paginator::_pageChanged, this, [=](int page){
        getVideoList(page);
    });
}
////////////////////////


// ////////////////////////
// /// \brief CheckPageForAp::updateCheckPage
// ///
// void CheckPageForAp::updateCheckPage()
// {
//     for(int i = 0 ;i < 10 ;i ++)
//     {
//         CheckPageItem * item = new CheckPageItem(this);
//         ui->layout->addWidget(item);
//     }
// }
// ////////////////////////



////////////////////////
/// \brief  CheckPageForAp::getVideoList
/// \param page
///
void CheckPageForAp::getVideoList(int page)
{
    // 日志输出
    // 如果 用户id不为空 优先使用 id 进行获取
    // 空的 再按照 视频状态

#ifdef CHECKPAGEFORAP_TEST
    LOG() << "CheckPageForAp::getVideoList(int page)";
#endif

    this->l_page = page;
    QString userId = ui->idEdit->text();
    auto dataCenter = model::DataCenter::getInstance();
    auto manageVideoLists = dataCenter->getManageSearchVideoList();
    manageVideoLists->videoInfoLists.clear(); // 这个清空就可以了

    if(!userId.isEmpty())
    {
#ifdef CHECKPAGEFORAP_TEST
        LOG() << "userId 不为空 进行userId 查询";
        LOG() << "userId : " << userId;
        LOG() << "执行 dataCenter->getVideoListForMyselfOrOtherAsync";
#endif
        dataCenter->getVideoListForMyselfOrOtherAsync(userId,page,model::GetVideoPage::ManagePage);
    }
    else{

        // 如果不为空
        // 直接调用 VideoList
        model::VideoState state = static_cast<model::VideoState>(ui->stateCombox->currentIndex());
        dataCenter->getVideoByStateAsync(state,page); // 发送请求
    }
}
////////////////////////


////////////////////////
/// \brief CheckPageForAp::checkState
/// \return
///
bool CheckPageForAp::checkState()
{
    auto dataCenter = model::DataCenter::getInstance();

    auto userInfo = dataCenter->getMyselfInfo();

    return userInfo->isAble();
}
////////////////////////



////////////////////////
/// \brief CheckPageForAp::resetPaginator
/// \param page_count
///
void CheckPageForAp::resetPaginator(int page_count)
{
    // 判断连接是不是存在
    if (paginatorConnection) {
        QObject::disconnect(paginatorConnection);
    }

    if (l_paginator) {
        l_paginator.reset();
    }

    l_paginator = std::make_unique<Paginator>(page_count, ui->paginatorArea);
    l_paginator->move(0, 15);
    l_paginator->show();

    paginatorConnection = connect(l_paginator.get(), &Paginator::_pageChanged, this, [=](int page){
        getVideoList(page);
    });
}
////////////////////////



////////////////////////
/// \brief CheckPageForAp::updateVideoListUI
///
void CheckPageForAp::updateVideoListUI()
{
    auto dataCenter = model::DataCenter::getInstance();
    auto videoListForManage = dataCenter->getManageSearchVideoList();

    QLayoutItem* item = nullptr;
    while(nullptr != (item = ui->layout->takeAt(0)))
    {
        delete item->widget();
        delete item;
    }

    if (videoListForManage == nullptr) {
        resetPaginator(0);
        return;
    }

    if (l_page == 1)
    {
        int videoCountPage = model::VideoList::PAGE_COUNT;
        int totalVideoCount = videoListForManage->getVideoTotalCount();
        int totalPages = (totalVideoCount + videoCountPage - 1) / videoCountPage;
        resetPaginator(totalPages);
    }

    auto videoList = videoListForManage->videoInfoLists;
    for (int i = 0; i < videoList.size(); i++)
    {
        CheckPageItem* newItem = new CheckPageItem(this, videoList[i]);
        ui->layout->addWidget(newItem);
    }
}
////////////////////////















