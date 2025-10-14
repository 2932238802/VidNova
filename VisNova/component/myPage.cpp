#include "myPage.h"
#include "ui_myPage.h"

///////////////////////////
/// \brief MyPage::MyPage
/// \param parent
///
MyPage::MyPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyPage)
{


    login = std::make_unique<Login>();

    ui->setupUi(this);initConnect();

    ui->titleBar->setStyleSheet("background-color: rgb(172, 172, 172);");
}
///////////////////////////



///////////////////////////
/// \brief MyPage::~MyPage
///
MyPage::~MyPage()
{
    delete ui;
}
///////////////////////////



///////////////////////////
/// \brief MyPage::getMyselfInfo
/// 切换到 我的界面的时候 调用的函数
/// 获取个人信息
///
void MyPage::getMyselfInfo()
{
    auto dataCenter = model::DataCenter::getInstance();
    auto myselfInfoPtr = dataCenter->getMyselfUserInfo();

    if(myselfInfoPtr == nullptr)
    {

#ifdef MYPAGE_TEST
        LOG() << "myselfInfoPtr 的信息为空 这个来自dataCenter->getMyselfUserInfo()";
        LOG() << "开始调用 dataCenter->getMyselfInfoAsync()";
#endif
        dataCenter->getMyselfInfoAsync();
    }
    else{
#ifdef MYPAGE_TEST
        LOG()<<"myselfInfoPtr 不为空 直接调用 onGetMyselfInfoDone 函数...";
#endif

        // _getMyselfInfoDone 这个信号 也会调用下面这个函数
        onGetMyselfInfoDone();
    }
}
////////////////////////





///////////////////////////
/// \brief MyPage::initConnect
///
void MyPage::initConnect()
{
    auto dataCenter = model::DataCenter::getInstance();
    connect(ui->avatarBtn,&QPushButton::clicked,this,&MyPage::onAvatarBtnClicked);
    connect(ui->modifyBtn,&QPushButton::clicked,this,&MyPage::onModifyBtnClicked);
    connect(ui->uploadVideoBtn,&QPushButton::clicked,this,&MyPage::onUploadVideoBtnClicked);
    connect(ui->attentionBtn,&QPushButton::clicked,this,&MyPage::onAttentionBtnClicked);
    connect(ui->exitBtn,&QPushButton::clicked,this,&MyPage::onExitBtnClicked);
    connect(ui->nickNameBtn,&QPushButton::clicked,this,&MyPage::onNickNameBtnClicked);

    connect(dataCenter,&model::DataCenter::_getMyselfInfoDone,this,&MyPage::onGetMyselfInfoDone);

    // 获取个人头像
    connect(dataCenter,&model::DataCenter::_downloadPhotoDone,this,&MyPage::getAvatarDone);

    // 设置图片的信号槽
    connect(dataCenter,&model::DataCenter::_uploadPhotoDone,this,&MyPage::uploadAvatarFileId);
    connect(dataCenter,&model::DataCenter::_setAvatarDone,this,&MyPage  ::uploadAvatarFileId2);
    //
    connect(dataCenter,&model::DataCenter::_getVideoListForMyselfOrOtherDone,this,&MyPage::onGetUserVideoListDone);

    // 移动滚动条 重新加载的 槽函数绑定
    connect(ui->scrollArea->verticalScrollBar(),&QScrollBar::valueChanged,this,&MyPage::onScrollAreaValueChanged);

    // 删除视频的槽函数绑定
    connect(dataCenter,&model::DataCenter::_deleteVideoDone,this,&MyPage::deleteVideoDone);

    // 其它用户信息 获取 成功的槽函数绑定
    connect(dataCenter,&model::DataCenter::_getOtherInfoDone,this,&MyPage::getOtherUserInfoDone);
    connect(dataCenter,&model::DataCenter::_addAttention,this,&MyPage::onAddAttentionSuc);
    connect(dataCenter,&model::DataCenter::_delAttention,this,&MyPage::ondelAttentionSuc);

    connect(login.get(),&Login::_loginSuc,this,&MyPage::onLoginSuc);

}
////////////////////////



////////////////////////
/// \brief MyPage::hideWidget
/// \param is_hide
///
void MyPage::hideWidget(bool is_hide)
{
    if(is_hide == true)
    {
        ui->attentionBtn->hide();
        ui->attentionCtLabel->hide();
        ui->attentionLabel->hide();

        ui->fansCtLabel->hide();
        ui->fansLabel->hide();

        ui->likeCtLabel->hide();
        ui->likeLabel->hide();

        ui->playCtLabel->hide();
        ui->playLabel->hide();

        ui->modifyBtn->hide();
        ui->myVideoLabel->hide();

        ui->exitBtn->hide();

        ui->uploadVideoBtn->hide();
        ui->uploadLabel->hide();

        ui->scrollArea->hide();

    }else{

        ui->attentionBtn->show();
        ui->attentionCtLabel->show();
        ui->attentionLabel->show();

        ui->fansCtLabel->show();
        ui->fansLabel->show();

        ui->likeCtLabel->show();
        ui->likeLabel->show();

        ui->playCtLabel->show();
        ui->playLabel->show();

        ui->modifyBtn->show();
        ui->myVideoLabel->show();

        ui->exitBtn->show();

        ui->uploadVideoBtn->show();
        ui->uploadLabel->show();

        ui->scrollArea->show();
    }
}
////////////////////////



////////////////////////
/// \brief MyPage::getUserVideoList
/// \param user_id
/// \param page_index
/// 获取用户信息列表
void MyPage::getUserVideoList(const QString &user_id, int page_index)
{

#ifdef MYPAGE_TEST

    LOG() << "MyPage::getUserVideoList(const QString &user_id, int page_index)...";
    LOG() << "准备获取用户视频...";
    LOG() << "page_index:" << page_index;
    LOG() << "user_id:" << user_id;
#endif

    auto dataCenter = model::DataCenter::getInstance();

    if(dataCenter->getMyselfUserInfo()->isTempUser())
    {
#ifdef MYPAGE_TEST
        LOG() << "MyPage::getUserVideoList(const QString &user_id, int page_index)...";
        LOG() << "是临时用户..." << page_index;

#endif
        return; // 临时用户 就不获取视频了
    }

    auto userVideoList = dataCenter->getUserVideoList();
    if(userVideoList == nullptr)
    {

#ifdef MYPAGE_TEST
        LOG() << "MyPage::getUserVideoList(const QString &user_id, int page_index)...";
        LOG() << "userVideoList 空指针" ;
#endif
        dataCenter->getVideoListForMyselfOrOtherAsync(user_id,1);

        return;
    }

    if(1 == page_index)
    {
        // 清空
        clearVideoList();
        userVideoList->clearVideoList();
#ifdef MYPAGE_TEST
        LOG() << "MyPage::getUserVideoList(const QString &user_id, int page_index)...";
        LOG() << "清空ui列表 和 数据列表" << page_index;
#endif
    }

    dataCenter->getVideoListForMyselfOrOtherAsync(user_id,1);
    userVideoList->setPageIndex(page_index+1);

}
////////////////////////



////////////////////////
/// \brief MyPage::clearVideoList
///
void MyPage::clearVideoList()
{
    QLayoutItem* item = nullptr;
    while(nullptr != (item = ui->layout->takeAt(0)))
    {
        delete item->widget();
        delete item;
    }
}
////////////////////////




////////////////////////
/// \brief MyPage::loadMyselfInfo
/// 切换按钮的时候 触发的函数 就是从其它的界面 切换到我的界面的时候触发的函数
///
void MyPage::loadMyselfInfoAndVideo()
{
#ifdef MYPAGE_TEST
    LOG () <<"进入MyPage loadMyselfInfoAndVideo函数...";
#endif

    user_id_cur = "";

    // 获取 个人信息
    getMyselfInfo();

    // 获取视频列表
    getUserVideoList(model::DataCenter::getInstance()->getUserId(),1);

    ui->avatarBtn->setMaskState(true);
    ui->avatarBtn->setEnabled(true);
}
////////////////////////



////////////////////////
/// \brief MyPage::onAvatarBtnClicked
///
void MyPage::onAvatarBtnClicked()
{
    auto dataCenter = model::DataCenter::getInstance();

    // 检测是不是临时用户
    if(dataCenter->getMyselfUserInfo()->isTempUser())
    {
        Toast::showMsg("请先登录...");
        return;
    }

    QString filePath = QFileDialog::getOpenFileName(nullptr,"修改头像","","jpg or png(*.jpg *.png)");

    if(filePath.isEmpty())
    {
        return;
    }

    QByteArray fileData(loadFileToByteArray(filePath));
    if(fileData.isEmpty())
    {
        LOG()<<"[err] 读取文件失败!";
        return;
    }
    dataCenter->uploadPhotoAsync(fileData);
}




////////////////////////
/// \brief MyPage::onModifyBtnClicked
///
void MyPage::onModifyBtnClicked()
{
    ModifySelfInfo* modifySelfInfo = new ModifySelfInfo();
    // exec 是阻塞 调用进程的
    // 模态的方式展现
    // 手动删除 栈 对象
    modifySelfInfo->exec();
    delete modifySelfInfo;
}
////////////////////////



////////////////////////
/// \brief MyPage::onUploadVideoBtnClicked
///
void MyPage::onUploadVideoBtnClicked()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr,"上传视频","",tr("vedios(*.mp4 *.rmvb *avi *.mov)"));

    if(filePath.isEmpty())
    {
        LOG()<<"[info] "<<"用户取消了上传文件";
        return;
    }
    LOG()<<"[suc]"<<"filePath: "<<filePath;

    // 检测视频的大小
    QFileInfo fileInfo(filePath);
    int64_t fileSize = fileInfo.size();

    if(fileSize > 1024 * 1024 * 1024 * 4LL)
    {

#ifdef MYPAGE_TEST
        LOG()<<"视频大小 大于4G";
#endif

        return;
    }
    emit switchUploadVideoPage(StackWidgetPage::UPLOADVEDIO_PAGE);
}
////////////////////////


////////////////////////
/// \brief MyPage::onAttentionBtnClicked
/// 用户点击
void MyPage::onAttentionBtnClicked()
{
    auto dataCenter = model::DataCenter::getInstance();
    auto myselfInfo = dataCenter->getMyselfUserInfo();

    if(nullptr == myselfInfo)
    {
#ifdef MYPAGE_TEST
        LOG() << "onAttentionBtnClicked()";
        LOG() << "myselfInfo 是空指针的";
#endif
        connect(dataCenter,&model::DataCenter::_getMyselfInfoDone,this,&MyPage::onAttentionBtnClicked,Qt::SingleShotConnection);

        //
        dataCenter->getMyselfInfoAsync();
        return;
    }


    if(myselfInfo->isTempUser())
    {
#ifdef MYPAGE_TEST
        LOG() << "onAttentionBtnClicked()";
        LOG() << "是临时用户...";
#endif
        Toast::showMsg("请先登录哦...");
        login->show();
        return ;
    }


#ifdef MYPAGE_TEST
    LOG() << "onAttentionBtnClicked()";
    LOG() << "跟新关注状态...";
    LOG() << "更新的用户id是" << dataCenter->getOtherUserInfo()->userId;
#endif

    bool isAttentionStatus = ui->attentionBtn->isAttention();
    isAttentionStatus = !isAttentionStatus;

    auto otherUserInfo = dataCenter->getOtherUserInfo();

    if(otherUserInfo == nullptr)
    {
        Toast::showMsg("被关注的用户不存在...");
        return;
    }

    if(isAttentionStatus)
    {
        dataCenter->addAttentionAsync(otherUserInfo->userId);

#ifdef MYPAGE_TEST
        LOG() << "onAttentionBtnClicked()";
        LOG() << "新增关注 关注状态...";
        LOG() << "更新的用户id是" << dataCenter->getOtherUserInfo()->userId;
#endif

    }
    else{
        dataCenter->delAttentionAsync(otherUserInfo->userId);

#ifdef MYPAGE_TEST
        LOG() << "onAttentionBtnClicked()";
        LOG() << "取消关注 关注状态...";
        LOG() << "更新的用户id是" << dataCenter->getOtherUserInfo()->userId;
#endif
    }

    ui->attentionBtn->setAttention(isAttentionStatus);

    // 通知 服务器 修改 关注信息
    dataCenter->alterAttentionAsync(dataCenter->getOtherUserInfo()->userId);
}
////////////////////////


////////////////////////
/// \brief MyPage::onNickNameBtnClicked
///
void MyPage::onNickNameBtnClicked()
{
    auto dataCenter = model::DataCenter::getInstance();
    auto userInfo = dataCenter->getMyselfUserInfo();

    if(userInfo->isTempUser())
    {
        if(login == nullptr)
        {
            login = std::make_unique<Login>();
        }

        login->show();
#ifdef MYPAGE_TEST
        LOG() << "onNickNameBtnClicked()";
        LOG() << "是临时用户 请先登录...";
#endif

        Toast::showMsg("请先登录...");
    }

}
////////////////////////


////////////////////////
/// \brief MyPage::onExitBtnClicked
///
void MyPage::onExitBtnClicked()
{

    ConfirmDialog dialog;
    dialog.setText("确认退出登录嘛...");
    dialog.exec();

    if(dialog.getConfirm())
    {

#ifdef MYPAGE_TEST
        LOG() << "onExitBtnClicked()";
        LOG() << "退出登录...";
#endif
    }

}
////////////////////////





////////////////////////
/// \brief MyPage::onGetMyselfInfoDone
/// 服务器 表示 用户信息 保存成功的槽函数
void MyPage::onGetMyselfInfoDone()
{

#ifdef MYPAGE_TEST
    LOG() << "MyPage::onGetMyselfInfoDone()...";
#endif

    hideWidget(false);

    // 如果不为空 那么就是 查看其它用户
    if(!user_id_cur.isEmpty())
    {
#ifdef MYPAGE_TEST
        LOG() << "正在查看其它用户 不更新 页面信息";
#endif
        return;
    }

    auto dataCenter = model::DataCenter::getInstance();
    auto myselfInfo = dataCenter->getMyselfUserInfo();

    // 根据 当前用户的类型 决定显示哪些内容
    if(myselfInfo->isTempUser())
    {

#ifdef MYPAGE_TEST
        LOG() << "确定是临时 用户 开始设置临时用户的信息...";
#endif

        hideWidget(true);

        ui->avatarBtn->setIcon(QIcon(":/image/defaultAvatar.png"));
        // 临时 用户 不能修改 头像
        ui->avatarBtn->setEnabled(false);

        ui->nickNameBtn->setText("请先登录...");

        ui->nickNameBtn->setEnabled(true);

        ui->nickNameBtn->adjustSize(); // 自动进行调整

        ui->nickNameBtn->setEnabled(true);

        return;

    }else if(myselfInfo->isB()){


#ifdef MYPAGE_TEST
        LOG()<< "确定是B端用户 开始 显示 系统按钮...";
#endif

        VidNovaMain* vid = VidNovaMain::getInstance();
        vid->showSystemBtn(true);
    }

    hideWidget(false);
    ui->nickNameBtn->setText(myselfInfo->nickName);
    ui->nickNameBtn->adjustSize();
    ui->nickNameBtn->setEnabled(false);

    QRect rect = ui->nickNameBtn->geometry();
    ui->modifyBtn->move(rect.x() + rect.width() + 8,ui->modifyBtn->geometry().y());

    ui->attentionCtLabel->setText(intToString_2(myselfInfo->followCount)); // 关注
    ui->fansCtLabel->setText(intToString_2(myselfInfo->fansCount));
    ui->likeCtLabel->setText(intToString_2(myselfInfo->likeCount));
    ui->playCtLabel->setText(intToString_2(myselfInfo->playCount));

    // 用户头像
    if(myselfInfo->avatarFileId.isEmpty())
    {
        ui->avatarBtn->setIcon(QIcon(":/image/defaultAvatar.png"));
    }
    else
    {
        dataCenter->downloadPhotoAsync(myselfInfo->avatarFileId);
    }

    // 隐藏关注的按钮
#ifdef MYPAGE_TEST
    LOG()<< "attentionBtn按钮打隐藏...";
    LOG()<< "exitBtn按钮打开...";
    ui->attentionBtn->hide();
    ui->exitBtn->show();
#endif



    ui->myVideoLabel->setText("我的视频");
    ui->avatarBtn->setEnabled(true);
}
///////////////////////////



////////////////////////
/// \brief MyPage::getAvatarDone
/// \param file_id
/// \param avatar_data
///
void MyPage::getAvatarDone(const QString &file_id,const QByteArray& avatar_data)
{
    auto myselfInfo = model::DataCenter::getInstance()->getMyselfUserInfo();
    if(myselfInfo!=nullptr && file_id == myselfInfo->avatarFileId)
    {
        ui->avatarBtn->setIcon(makeIcon(avatar_data,ui->avatarBtn->width()/2,ui->avatarBtn->width()/2));
    }

    // 设置其它用户的头像
    auto otherUserInfo = model::DataCenter::getInstance()->getOtherUserInfo();

    if(otherUserInfo!=nullptr && file_id == otherUserInfo->avatarFileId)
    {
        ui->avatarBtn->setIcon(makeIcon(avatar_data,ui->avatarBtn->width()/2,ui->avatarBtn->width()/2));
    }
}
////////////////////////



////////////////////////
/// \brief MyPage::uploadAvatarFileId
///
void MyPage::uploadAvatarFileId(const QString& fileId)
{
    // 使用 fileId 修改服务器
    auto dataCenter = model::DataCenter::getInstance();
    dataCenter->setAvatarAsync(fileId);
}
////////////////////////



////////////////////////
/// \brief MyPage::uploadAvatarFileId2
///
void MyPage::uploadAvatarFileId2()
{
    auto dataCenter = model::DataCenter::getInstance();
    auto myselfInfo = dataCenter->getMyselfUserInfo();
    dataCenter->downloadPhotoAsync(myselfInfo->avatarFileId);
}
////////////////////////



////////////////////////
/// \brief MyPage::onGetUserVideoListDone
/// \param user_id
/// 显示 个人 用户信息的 videoBox
void MyPage::onGetUserVideoListDone(const QString &user_id)
{
    // 显示到界面上


#ifdef MYPAGE_TEST
    LOG() << "onGetUserVideoList()";
    LOG() << "user_id " << user_id;
#endif

    auto dataCenter = model::DataCenter::getInstance();
    auto userVideoList = dataCenter->getUserVideoList();
    const int rowCount = 4;
    for(int i = ui->layout->count();i < userVideoList->getVideoCount();i++)
    {
        int row = i / 4;
        int col = i % 4;
        VideoBox* videoBox = new VideoBox(userVideoList->videoInfoLists[i]);
        ui->layout->addWidget(videoBox,row,col);
        connect(videoBox,&VideoBox::_onPlayBtnClicked,this,[=](){
            PlayerPage* page = new PlayerPage(userVideoList->videoInfoLists[i]);
            connect(page,&PlayerPage::_updateLikeNumber,videoBox,&VideoBox::onUpdateLikeNumber);
            page->setUserAvatar(std::move(videoBox->getUserAvatar()));
            page->show();
            page->startPlay();
        });

        if(user_id.isEmpty())
        {
            videoBox->showMoreBtn(true);
            connect(videoBox, &VideoBox::_deleteVideo,this,&MyPage::deleteVideo);
        }
    }
}
////////////////////////



////////////////////////
/// \brief MyPage::onScrollAreaValueChanged
/// \param value
///
void MyPage::onScrollAreaValueChanged(int value)
{
#ifdef MYPAGE_TEST
    LOG()<<"onScrollAreaValueChanged()";
    LOG()<<"value " << value;
#endif

    if(value == 0)
    {
        return ;
    }


    if(value == ui->scrollArea->verticalScrollBar()->maximum())
    {
        // 获取下一页 视频

        auto dataCenter = model::DataCenter::getInstance();
        auto userVideoList = dataCenter->getUserVideoList();

        int pageIndex = userVideoList->getPageIndex();

#ifdef MYPAGE_TEST
        LOG()<<"onScrollAreaValueChanged()";
        LOG()<<"pageIndex:" << pageIndex;
#endif

        dataCenter->getVideoListForMyselfOrOtherAsync(user_id_cur,pageIndex);

        userVideoList->setPageIndex(pageIndex+1);
    }
}
////////////////////////


////////////////////////
/// \brief MyPage::onAddAttentionSuc
///
void MyPage::onAddAttentionSuc()
{
    auto dataCenter = model::DataCenter::getInstance();
    auto otherUserInfo = dataCenter->getOtherUserInfo();
    auto myUserInfo = dataCenter->getMyselfUserInfo();

    otherUserInfo->fansCount++;
    myUserInfo->followCount++;
    ui->fansCtLabel->setText(intToString_2(otherUserInfo->fansCount));
}
////////////////////////



////////////////////////
/// \brief MyPage::ondelAttentionSuc
///
void MyPage::ondelAttentionSuc()
{
    auto dataCenter = model::DataCenter::getInstance();
    auto otherUserInfo = dataCenter->getOtherUserInfo();
    auto myUserInfo = dataCenter->getMyselfUserInfo();

    otherUserInfo->fansCount--;
    myUserInfo->followCount--;

    ui->fansCtLabel->setText(intToString_2(otherUserInfo->fansCount));
}
////////////////////////



////////////////////////
/// \brief MyPage::onLoginSuc
/// 用户登录成功了
void MyPage::onLoginSuc()
{
#ifdef MYPAGE_TEST
    LOG() << "用户登录成功~ ";
#endif

    // 因为登录成功了 所以要重新获取一下 用户的信息
    auto dataCenter = model::DataCenter::getInstance();
    // dataCenter->getMyselfInfoAsync();

    loadMyselfInfoAndVideo();
}
////////////////////////




////////////////////////
/// \brief MyPage::deleteVideoDone
/// \param video_id
/// 删除完 视频 接受到信号 触发的槽函数
void MyPage::deleteVideoDone(const QString &video_id)
{
#ifdef MYPAGE_TEST
    LOG() << "MyPage::deleteVideo(const QString &video_id)";

    LOG() << "video_id " << video_id;
#endif

    getUserVideoList("",1);
}
////////////////////////



////////////////////////
/// \brief MyPage::deleteVideo
/// \param video_id
///
void MyPage::deleteVideo(const QString &video_id)
{
    auto dataCenter = model::DataCenter::getInstance();
    dataCenter->deleteVideoAsync(video_id);
}
////////////////////////



////////////////////////
/// \brief MyPage::loadOtherUser
/// \param user_id
///
void MyPage::loadOtherUserInfoAndVideo(const QString &user_id)
{
    user_id_cur = user_id;
    // 获取视频列表
    getUserVideoList(user_id,1);

    // 加载个人信息
    getOtherUserInfo(user_id);

    ui->avatarBtn->setMaskState(false);

    ui->avatarBtn->setEnabled(false);
}
////////////////////////



////////////////////////
/// \brief MyPage::loadTempUserInfo
///
///
void MyPage::loadTempUserInfo()
{
    auto dataCenter = model::DataCenter::getInstance();

    QJsonObject obj;

    obj["userId"] = "0";
    obj["photoNumber"] = "0";
    obj["nickName"] = "临时用户";

    QJsonArray arr;
    arr.append(4);

    obj["roleType"] = arr;

    obj["likeCount"] = 0;
    obj["playCount"] = 0;
    obj["fansCount"] = 0;

    obj["userState"] = 0;
    obj["isFollowed"] = 0;

    obj["userMemo"] = "作为临时用户...";
    obj["userCreateTime"] = "";
    obj["avatarFileId"] = "";

    dataCenter->setMyselfInfo(obj);
}
////////////////////////





////////////////////////
/// \brief MyPage::getOtherUserInfoDone
/// 获取其它个人信息 完毕
void MyPage::getOtherUserInfoDone()
{
#ifdef MYPAGE_TEST
    LOG()<<"MyPage::getOtherUserInfoDone()...";
#endif

    hideWidget(false);

    ui->modifyBtn->hide();
    ui->exitBtn->hide();
    ui->uploadVideoBtn->hide();
    ui->uploadLabel->hide();

    ui->avatarBtn->setEnabled(false);
    ui->nickNameBtn->setEnabled(false);

    auto dataCenter = model::DataCenter::getInstance();
    auto otherUserInfo = dataCenter->getOtherUserInfo();

    ui->nickNameBtn->setText(otherUserInfo->nickName);
    ui->attentionCtLabel->setText(intToString_2(otherUserInfo->followCount));
    ui->fansCtLabel->setText(intToString_2(otherUserInfo->fansCount));
    ui->playCtLabel->setText(intToString_2(otherUserInfo->playCount));
    ui->likeCtLabel->setText(intToString_2(otherUserInfo->likeCount));

    // 初始化 关注信息
    ui->attentionBtn->setAttention(otherUserInfo->isFollowed == 1);

    ui->myVideoLabel->setText("Ta的视频");
    if(otherUserInfo->avatarFileId.isEmpty())
    {
        // 默认
        ui->avatarBtn->setIcon(QIcon(":/image/defaultAvatar.png"));
    }
    else{
        dataCenter->downloadPhotoAsync(otherUserInfo->avatarFileId);
    }



}
////////////////////////




////////////////////////
/// \brief MyPage::getOtherUserInfo
/// \param user_id
/// 获取其它个人信息
void MyPage::getOtherUserInfo(const QString &user_id)
{
#ifdef MYPAGE_TEST
    LOG()<<"MyPage::getOtherUserInfo(const QString &user_id)";
#endif

    auto dataCenter = model::DataCenter::getInstance();
    dataCenter->getOtherInfoAsync(user_id);
}
////////////////////////

































