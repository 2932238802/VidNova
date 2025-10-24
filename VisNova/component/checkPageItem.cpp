    #include "checkPageItem.h"
    #include "ui_checkPageItem.h"

//////////////////////////////
/// \brief CheckPageItem::CheckPageItem
/// \param parent
/// \param videoInfo
///
CheckPageItem::CheckPageItem(QWidget *parent, const model::VideoInfoForLoad &videoInfo)
    : QWidget(parent)
    ,ui(new Ui::CheckPageItem)
{
    ui->setupUi(this);
    l_videoInfo = videoInfo;

    ui->userId->setText(videoInfo.userId);
    ui->nickNameLabel->setText(videoInfo.nickName);
    ui->videoTitleLabel->setText(videoInfo.videoTitle);

    if(videoInfo.videoState == model::VideoState::WaitForChecking)
    {
        ui->checkerLabel->setText("--");
    }

    ui->opBtn2->hide();
    ui->opBtn1->move(1186,51);

    switch(videoInfo.videoState)
    {
    case model::VideoState::WaitForChecking:{

        setWaitingForCheckStyle(); // 待审核
        break;
    }
    case model::VideoState::PutOn:
    {
        setCheckedStyle(); // 已审核
        break;
    }
    case model::VideoState::Discard:{
        setPutDownStyle();
        break;
    }
    case model::VideoState::Reject:{
        setRejectedStyle();
        break;
    }
    default: {
#ifdef CHECKPAGEFORITEM_TEST
        LOG() << "未知状态" ;
#endif
        break;
    }

    }

    auto dataCenter = model::DataCenter::getInstance();

    connect(dataCenter,&model::DataCenter::_downloadPhotoDone,this,[=](const QString& photeId,QByteArray imageData){
        if(photeId == videoInfo.photoId)
        {
            QPixmap pixmap;
            if(!pixmap.loadFromData(imageData))
            {
#ifdef CHECKPAGEFORITEM_TEST
                LOG() << "图片获取失败 pixmap.loadFromData(imageData)";
#endif
                return;
            };

            QSize size = ui->videoBtn->size();

            QPixmap adjustPixmap = pixmap.scaled(
                                             size,
                                             Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation
                );

            ui->videoBtn->setIcon(QIcon(adjustPixmap));
            ui->videoBtn->setIconSize(size);
        }
        else{
            return;
        }
    });

    dataCenter->downloadPhotoAsync(videoInfo.photoId);

    if(l_videoInfo.userAvatarId.isEmpty())
    {
        // loadFromData 可以把二进制流 直接读进去
        userAvatar.loadFromData(loadFileToByteArray(":/image/defaultAvatar.png"));

    }
    else{
        auto dataCenter = model::DataCenter::getInstance();
        dataCenter->downloadPhotoAsync(l_videoInfo.userAvatarId);
        connect(dataCenter,&model::DataCenter::_downloadPhotoDone,this,[=](const QString& photeId,QByteArray imageData){
            if(photeId != l_videoInfo.userAvatarId)
            {
                return;
            }
            userAvatar.loadFromData(imageData);
            if(player)
                {
                    player->setUserAvatar(userAvatar); // 设置用户头像
            }
        });
    }


    connect(ui->videoBtn, &QPushButton::clicked, this, &CheckPageItem::onVideoBtnClicked);
    connect(ui->opBtn1,&QPushButton::clicked,this,&CheckPageItem::onOpBtn1Clicked);
    connect(ui->opBtn2,&QPushButton::clicked,this,&CheckPageItem::onOpBtn2Clicked);
}
//////////////////////////////


//////////////////////////////
/// \brief CheckPageItem::~CheckPageItem
///
CheckPageItem::~CheckPageItem()
{
    delete ui;
}
//////////////////////////////



//////////////////////////////
/// \brief CheckPageItem::onVideoBtnClicked
/// 视频的播放
/// 其实并不需要 点赞之类的 也不需要弹幕 因为是审核
/// 信息初始化的时候 就加载好了
void CheckPageItem::onVideoBtnClicked()
{
#ifdef CHECKPAGEFORITEM_TEST
    LOG() << "CheckPageItem::onVideoBtnClicked()";
#endif

    if(!player)
    {
        // nullptr setAttribute(Qt::WA_DeleteOnClose); 关闭之后 自动销毁
        player = std::make_unique<PlayerPage>(l_videoInfo,nullptr,PlayerMode::InView);

        if(!userAvatar.isNull())
        {
            player->setUserAvatar(userAvatar); // 设置头像
        }
    }


    player->show();
    player->startPlay();
}
//////////////////////////////



//////////////////////////////
/// \brief CheckPageItem::onOpBtn1Clicked
///
void CheckPageItem::onOpBtn1Clicked()
{
    auto dataCenter = model::DataCenter::getInstance();

    ConfirmDialog* confirm = new ConfirmDialog();

    QString videoId = l_videoInfo.videoId;

    switch(l_videoInfo.videoState)
    {
    case model::VideoState::Discard:{
        // 上架
#ifdef CHECKPAGEFORAP_TEST
        LOG() << "重新上架视频...";
#endif
        confirm->setText("确定重新上架视频嘛?");
        confirm->exec();
        if(confirm->getConfirm())
        {
            setCheckedStyle();
            dataCenter->putOnVideoAsync(videoId);
        }
        break;
    }

    case model::VideoState::PutOn:{
        // 下架
#ifdef CHECKPAGEFORAP_TEST
        LOG() << "下架视频...";
#endif
        confirm->setText("确定下架视频嘛?");
        confirm->exec();
        if(confirm->getConfirm())
        {
            setPutDownStyle();
            dataCenter->putDownVideoAsync(videoId);
        }
        break;
    }
    case model::VideoState::Reject:{
        // --
#ifdef CHECKPAGEFORAP_TEST
        LOG() << "已经驳回 按钮点击无效";
#endif
        break;

    }
    case model::VideoState::WaitForChecking:{
        // 待审核的状态 那么这个按钮就是显示 通过
#ifdef CHECKPAGEFORAP_TEST
        LOG() << "通过...";
#endif
        confirm->setText("确定审核通过嘛?");
        confirm->exec();
        if(confirm->getConfirm())
        {
            setCheckedStyle();
            dataCenter->checkVideoAsync(videoId,true);
        }
        break;
    }
    default:{

#ifdef CHECKPAGEFORAP_TEST
        LOG() << "未知状态";
#endif
        break;
    }
    }

    confirm->deleteLater();
}
//////////////////////////////



//////////////////////////////
/// \brief CheckPageItem::onOpBtn2Clicked
///
void CheckPageItem::onOpBtn2Clicked()
{
    auto dataCenter = model::DataCenter::getInstance();

    ConfirmDialog* confirm = new ConfirmDialog();

    QString videoId = l_videoInfo.videoId;

    confirm->setText("确定驳回视频吗?");

    confirm->exec();

    if(confirm->getConfirm())
    {
        setRejectedStyle();
        dataCenter->checkVideoAsync(videoId,false);
    }

    confirm->deleteLater();
}
//////////////////////////////



//////////////////////////////
/// \brief CheckPageItem::setCheckedStyle
/// 已审核
void CheckPageItem::setCheckedStyle()
{
    ui->stateBtn->setText("已审核");
    ui->opBtn1->setText("下架");

    ui->stateBtn->setStyleSheet(ALREADY_BTN_STYLE);
    ui->opBtn1->setStyleSheet(TAKEDOWN_BTN_STYLE);
}
//////////////////////////////



//////////////////////////////
/// \brief CheckPageItem::setRejectedStyle
/// 已驳回
void CheckPageItem::setRejectedStyle()
{
    ui->stateBtn->setText("已驳回");
    ui->opBtn1->setText("--");

    ui->stateBtn->setStyleSheet(ALREADY_REJECT_BTN_STYLE);
    ui->opBtn1->setStyleSheet(GANGGANG_BTN_STYLE);
}
//////////////////////////////


//////////////////////////////
/// \brief CheckPageItem::setWaitingForCheckStyle
/// 待审核
void CheckPageItem::setWaitingForCheckStyle()
{
    ui->stateBtn->setText("待审核");
    ui->opBtn1->setText("通过");
    ui->opBtn1->move(1156,50);
    ui->opBtn2->setText("驳回");
    ui->opBtn2->show();

    ui->stateBtn->setStyleSheet(WAITFORCHECKING_BTN_STYLE);
    ui->opBtn1->setStyleSheet(ACESS_BTN_STYLE);
    ui->opBtn2->setStyleSheet(REJECT_BTN_STYLE);
}
//////////////////////////////


//////////////////////////////
/// \brief CheckPageItem::setPutDownStyle
/// 已下架
void CheckPageItem::setPutDownStyle()
{
    ui->stateBtn->setText("已下架");
    ui->opBtn1->setText("上架");

    ui->stateBtn->setStyleSheet(ALREADY_TAKEDOWN_BTN_STYLE);
    ui->opBtn1->setStyleSheet(PUTON_BTN_STYLE);
}
//////////////////////////////















