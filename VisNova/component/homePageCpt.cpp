#include "homePageCpt.h"
#include "ui_homePageCpt.h"


//////////////////////////////////////////////////////
/// \brief homePageCpt::homePageCpt
/// \param parent
///
homePageCpt::homePageCpt(QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::homePageCpt),
    tagsGp(nullptr)
{
    ui->setupUi(this);
    initKindAndTags(); //跳转到这个页面的时候的初始化
    initRefreshAndTopBtn();
    initConnect();
    initVideos(); //初始化 视频
}
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
void homePageCpt::initKindAndTags()
{
    auto dataCenter = model::DataCenter::getInstance();
    auto kindAndTags = dataCenter->getkatPtr();
    auto kinds = kindAndTags->getAllKinds();
    auto tags = kindAndTags->getAllLabels(kinds[0]).keys();

    tagsGp = new QButtonGroup(this);
    tagsGp->setExclusive(false); // 可以多选标签
    QPushButton* kindBtn = buildBtn(ui->classifys,"#3ECEFF","分类");
    ui->classifyHLayout->addWidget(kindBtn); //添加到布局里里面
    QButtonGroup* qBtnGp = new QButtonGroup(this); // 绑在树上了
    qBtnGp->setExclusive(true);


    for(auto a:kinds)
    {
        QPushButton* btn = buildBtn(ui->classifys,"#666666",a);
        btn->setCheckable(true); // 设置成可以检查的 这样就会有 按下和松开两种状态

        ui->classifyHLayout->addWidget(btn);

        qBtnGp->addButton(btn);

        auto tags = kindAndTags->getAllLabels(a).keys();
        connect(btn,&QPushButton::toggled,this,[=](bool is_click){
            if(is_click)
            {
                btn->setStyleSheet("background-color: #F1FDFF; color:#3ECEFF;");

                lastStyle = VideoListStyle::Kind;
                isAppend = false;

                curKindId = kindAndTags->getKindId(a);
                dataCenter->getVideoByKindAsync(curKindId);
                resetTags(a,tags);
            }
            else{
                btn->setStyleSheet("color: #666666; background-color: transparent;");

                lastStyle = VideoListStyle::All;
                isAppend = false;
                clearLayoutAndBtn(ui->videoGLayout);
                dataCenter->getAllVideoListAsync();
                resetTags(a,{});
            }
        });
    }
    ui->classifyHLayout->setSpacing(8); // 设置间距
}
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
/// \brief homePageCpt::initConnect
/// 绑定槽函数
void homePageCpt::initConnect()
{
    auto dataCenter = model::DataCenter::getInstance();
    connect(dataCenter,&model::DataCenter::_getAllVideoListDone,this,&homePageCpt::updataVideoList);
    connect(dataCenter,&model::DataCenter::_getVideoByKindDone,this,&homePageCpt::updataVideoList);
    connect(dataCenter,&model::DataCenter::_getVideoByTagDone,this,&homePageCpt::updataVideoList);
    connect(ui->search,&SearchLineEdit::_searchVideos,this,&homePageCpt::onSearchVideosBtnClicked);
    connect(dataCenter,&model::DataCenter::_getVideoBySearchTextDone,this,&homePageCpt::updataVideoList);
    connect(ui->videoScroll->verticalScrollBar(),&QScrollBar::valueChanged,this,&homePageCpt::onScrollBarValueChanged);
};
//////////////////////////////////////////////////////



///////////////////////////////////////////////////
/// \brief homePageCpt::resetTags
/// \param tags_contain
/// 重置视频
void homePageCpt::resetTags(const QString& kind,const QList<QString> &tags_contain)
{
    clearLayoutAndBtn(ui->labelHLayout);
    clearLayoutAndBtn(ui->videoGLayout); // 先清空

    QPushButton* tag = buildBtn(ui->labels,"#3ECEFF","标签");
    ui->labelHLayout->addWidget(tag); // 添加 “分类” 标签
    auto dataCenter = model::DataCenter::getInstance();
    auto tags = dataCenter->getkatPtr();
    for(auto& a:tags_contain)
    {
        QPushButton* tagItem = buildBtn(ui->labels,"#666666",a);
        tagItem->setCheckable(true);
        ui->labelHLayout->addWidget(tagItem);
        tagsGp->addButton(tagItem);
        connect(tagItem, &QPushButton::toggled, this, [=](bool is_check){
            if (is_check) {
                tagItem->setStyleSheet("background-color: #F1FDFF; color: #3ECEFF");
            } else {
                clearLayoutAndBtn(ui->videoGLayout);
                tagItem->setStyleSheet("background-color:transparent; color: #666666");
            }

            combinedTagId = 0;
            for (auto* btn : tagsGp->buttons()) {
                if (btn->isChecked()) {
                    int id = tags->getTagId(kind, btn->text());
                    combinedTagId |= id;
                }
            }
            if (combinedTagId != 0) {

#ifdef HOMEPAGECPT_TEST
                LOG() << "combinedTagId" << combinedTagId;
#endif

                lastStyle = VideoListStyle::Tag;
                isAppend = false;
                dataCenter->setMode(isAppend);
                dataCenter->getVideoByTagAsync(combinedTagId);

            } else {
                LOG() << "no tags";

                lastStyle = VideoListStyle::Kind;
                isAppend = false;
                dataCenter->setMode(isAppend);

                dataCenter->getVideoByKindAsync(tags->getKindId(kind));
            }
        });
    }
    ui->labelHLayout->setSpacing(8);
}
///////////////////////////////////////////////////



///////////////////////////////////////////////////
/// \brief homePageCpt::initRefreshAndTopBtn
/// 刷新和顶置的视频
void homePageCpt::initRefreshAndTopBtn()
{
    // 刷新 顶置和刷新按钮
    QWidget* refreshTopBtn = new QWidget(this);
    refreshTopBtn->setFixedSize(42,94);
    refreshTopBtn->setObjectName("los_refreshTopBtn");

    refreshTopBtn->setStyleSheet(R"(
    #los_refreshTopBtn{
        background-color: transparent;
    }
    QPushButton{
        border-radius: 16px;
        border: none;
        background-color: transparent;
    }

    QPushButton:hover{
        border: none;
        background-color: #666666;

    }
)");

    // 设置布局
    QVBoxLayout* layout = new QVBoxLayout(refreshTopBtn);


    // 创建按钮
    QPushButton* topBtn = new QPushButton(refreshTopBtn);
    QPushButton* refreshBtn = new QPushButton(refreshTopBtn);

    topBtn->setFixedSize(42,42);
    refreshBtn->setFixedSize(42,42);

    topBtn->setStyleSheet(R"(
        border: none;
        border-image: url(":/image/toTop.png");
)");
    refreshBtn->setStyleSheet(R"(
        border: none;
        border-image: url(":/image/refresh.png");
)");

    layout->addWidget(topBtn);
    layout->addWidget(refreshBtn);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(10);
    refreshTopBtn->move(1278,618);

    // 点击 触发
    connect(topBtn,&QPushButton::clicked,this,&homePageCpt::onTopBtnClicked);
    connect(refreshBtn,&QPushButton::clicked,this,&homePageCpt::onRefreshBtnClicked);
}
///////////////////////////////////////////////////



//////////////////////////////////////////////////////
/// \brief homePageCpt::buildBtn
/// \param parent
/// \param color
/// \param text
/// \return
///
QPushButton* homePageCpt::buildBtn(QWidget *parent, const QString &color, const QString &text)
{
    QPushButton* btn = new QPushButton(text,parent);
    btn->setStyleSheet("color:"+color);
    btn->setMinimumHeight(26); // 设置最小的高度
    btn->setFixedWidth(text.size()*16+18+18); //18 是左右边距
    return btn;
}
//////////////////////////////////////////////////////




//////////////////////////////////////////////////////
void homePageCpt::clearLayoutAndBtn(QLayout *layout)
{
    if(layout == nullptr )
    {
        LOG()<<"[wa] layout 内容为空";
        return;
    }

    QLayoutItem* item = nullptr;
    while((item = layout->takeAt(0))!=nullptr)
    {
        if(QWidget* isWidget = item->widget())
        {
            isWidget->setParent(nullptr);
            delete isWidget;
        }
        delete item;
    }

    ui->videoScroll->verticalScrollBar()->setValue(0);

}
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
/// \brief homePageCpt::initVideos
///
void homePageCpt::initVideos()
{
    // 坐上对齐
    ui->videoGLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->videoScroll->verticalScrollBar()->setValue(0);
    auto dataCenter = model::DataCenter::getInstance();
    dataCenter->getAllVideoListAsync();
    lastStyle = VideoListStyle::All;
}
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
/// \brief homePageCpt::openPlayerPage
/// \param path
///
void homePageCpt::openPlayerPage(const model::VideoInfo& video_info)
{

}
//////////////////////////////////////////////////////




//////////////////////////////////////////////////////
/// \brief homePageCpt::onTopBtnClicked
void homePageCpt::onTopBtnClicked()
{

    ui->videoScroll->verticalScrollBar()->setValue(0);
}
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
/// \brief homePageCpt::onRefreshBtnClicked
///
void homePageCpt::onRefreshBtnClicked()
{
    // 旧的视频 清空
    clearLayoutAndBtn(ui->videoGLayout);

    auto dataCenter = model::DataCenter::getInstance();


    switch(lastStyle)
    {
    case(VideoListStyle::All):
    {
        dataCenter ->getAllVideoListAsync();

#ifdef HOMEPAGECPT_TEST
        LOG()<<"上一次获取视频的方式是 全部获取...";
#endif


        break;
    }
    case VideoListStyle::Kind:{
        dataCenter->getVideoByKindAsync(curKindId);

#ifdef HOMEPAGECPT_TEST
        LOG()<<"上一次获取视频的方式是 按照标签进行获取...";
#endif

        break;
    }
    case VideoListStyle::Search:
    {
        dataCenter->getAllVideoListSearchTextAsync(ui->search->text());

#ifdef HOMEPAGECPT_TEST
        LOG()<<"上一次获取视频的方式是 按照搜索框...";
#endif

        break;
    }
    case VideoListStyle::Tag:{
        dataCenter->getVideoByTagAsync(combinedTagId);

#ifdef HOMEPAGECPT_TEST
        LOG()<<"上一次获取视频的方式是 按照标签...";
#endif

        break;
    }
    default:
    {
        break;
    }
    }
}
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
/// \brief homePageCpt::updataVideoList
/// 槽函数
void homePageCpt::updataVideoList()
{
    // 清空视频信息

    auto dataCenter = model::DataCenter::getInstance();

    if(!isAppend)
    {
#ifdef HOMEPAGECPT_TEST
        LOG()<<"不追加...";
#endif
        clearLayoutAndBtn(ui->videoGLayout);
    }

    auto videoList = dataCenter->getVideoList()->getVideoListOfVideoInfo();

    // 获取视频信息

    int index = 0;


#ifdef HOMEPAGECPT_TEST
    LOG()<<"从服务器上 获取下"<<videoList.size() << "个视频";
#endif


    for(int i = ui->videoGLayout->count() ; i < videoList.size(); i ++)
    {
        // 从视频列表 开始

        VideoBox* videoBox = new VideoBox(videoList[i]);

        connect(videoBox,&VideoBox::_onPlayBtnClicked,this,[=](){
            PlayerPage* page = new PlayerPage(videoList[i]);
            connect(page,&PlayerPage::_updateLikeNumber,videoBox,&VideoBox::onUpdateLikeNumber);
            page->setUserAvatar(std::move(videoBox->getUserAvatar()));
            page->show();
            page->startPlay();
        });
        ui->videoGLayout->addWidget(videoBox,i/4,i%4); // 行和列
    }


    isAppend = false;
}
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
/// \brief homePageCpt::onSearchVideos
/// \param text
///
void homePageCpt::onSearchVideosBtnClicked(const QString &text)
{
    clearLayoutAndBtn(ui->videoGLayout);
    auto dataCenter = model::DataCenter::getInstance();

    isAppend = false;
    dataCenter->setMode(isAppend);

    if(text.size() == 0)
    {
        lastStyle = VideoListStyle::All;



        dataCenter->getAllVideoListAsync();
        return ;
    }

    lastStyle = VideoListStyle::Search;
    dataCenter->getAllVideoListSearchTextAsync(text);
}
//////////////////////////////////////////////////////



//////////////////////////////////////////////////////
/// \brief homePageCpt::onScrollBarValueChanged
/// \param value
///
void homePageCpt::onScrollBarValueChanged(int value)
{
    // 检测滚动条是不是最大值

#ifdef HOMEPAGECPT_TEST
    LOG()<<"onScrollBarValueChanged...";
#endif


    auto dataCenter = model::DataCenter::getInstance();
    auto videoPtr = dataCenter->getVideoList();

    if(videoPtr->getVideoCount() == videoPtr->getVideoTotalCount())
    {

#ifdef HOMEPAGECPT_TEST
        LOG()<<"视频内容获取完毕... videoPtr->getVideoCount():"<<videoPtr->getVideoCount()<<"   videoPtr->getVideoTotalCount():" <<videoPtr->getVideoTotalCount();
#endif

        return;
    }

    if(value == ui->videoScroll->verticalScrollBar()->maximum())
    {
        isAppend = true;
        dataCenter->setMode(isAppend);

        switch(lastStyle)
        {
        case(VideoListStyle::All):
        {
            dataCenter ->getAllVideoListAsync();

#ifdef HOMEPAGECPT_TEST
            LOG()<<"上一次获取视频的方式是 全部获取...";
#endif


            break;
        }
        case VideoListStyle::Kind:{
            dataCenter->getVideoByKindAsync(curKindId);

#ifdef HOMEPAGECPT_TEST
            LOG()<<"上一次获取视频的方式是 按照标签进行获取...";
#endif

            break;
        }
        case VideoListStyle::Search:
        {
            dataCenter->getAllVideoListSearchTextAsync(ui->search->text());

#ifdef HOMEPAGECPT_TEST
            LOG()<<"上一次获取视频的方式是 按照搜索框...";
#endif

            break;
        }
        case VideoListStyle::Tag:{
            dataCenter->getVideoByTagAsync(combinedTagId);

#ifdef HOMEPAGECPT_TEST
            LOG()<<"上一次获取视频的方式是 按照标签...";
#endif

            break;
        }
        default:
        {

        }
        }
    }
}
//////////////////////////////////////////////////////




//////////////////////////////////////////////////////
/// \brief homePageCpt::~homePageCpt
/// 析构
homePageCpt::~homePageCpt()
{
    delete ui;
}
//////////////////////////////////////////////////////
