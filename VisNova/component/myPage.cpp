#include "myPage.h"
#include "ui_myPage.h"

MyPage::MyPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyPage)
{
    ui->setupUi(this);initUi();initConnect();
    ui->titleBar->setStyleSheet("background-color: rgb(172, 172, 172);");
}

void MyPage::getMyselfInfo()
{
    auto dataCenter = model::DataCenter::getInstance();

    auto myselfInfoPtr = dataCenter->getMyselfUserInfo();
    if(myselfInfoPtr == nullptr)
    {
        dataCenter->getMyselfInfoAsync();
    }else{
        onGetMyselfInfoDone();
    }
}

MyPage::~MyPage()
{
    delete ui;
}

void MyPage::initUi()
{
    ui->attentionBtn->hide();

#ifdef MY_PAGE_TEST
    for(int i = 0; i< 16;i++)
    {
        VideoBox* vedioBox = new VideoBox();
        ui->layout->addWidget(vedioBox,i/4,i%4,1,1);
    }
#endif


}

void MyPage::initConnect()
{
    auto dataCenter = model::DataCenter::getInstance();
    connect(ui->avatarBtn,&QPushButton::clicked,this,&MyPage::onAvatarBtnClicked);
    connect(ui->modifyBtn,&QPushButton::clicked,this,&MyPage::onModifyBtnClicked);
    connect(ui->uploadVedioBtn,&QPushButton::clicked,this,&MyPage::onUploadVideoBtnClicked);
    connect(dataCenter,&model::DataCenter::_getMyselfInfoDone,this,&MyPage::onGetMyselfInfoDone);

    // 获取个人头像
    connect(dataCenter,&model::DataCenter::_downloadPhotoDone,this,&MyPage::getAvatarDone);

    // 设置图片的信号槽
    connect(dataCenter,&model::DataCenter::_uploadPhotoDone,this,&MyPage::uploadAvatarFileId);

    connect(dataCenter,&model::DataCenter::_setAvatarDone,this,&MyPage::uploadAvatarFileId2);
}


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

        ui->uploadVedioBtn->hide();
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

        ui->uploadVedioBtn->show();
        ui->uploadLabel->show();

        ui->scrollArea->show();

    }
}
////////////////////////



////////////////////////
/// \brief MyPage::loadMyselfInfo
///
void MyPage::loadMyselfInfoAndVideo()
{
    // 获取 个人信息
    getMyselfInfo();


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

void MyPage::onModifyBtnClicked()
{
    ModifySelfInfo* modifySelfInfo = new ModifySelfInfo();
    // exec 是阻塞 调用进程的
    // 模态的方式展现
    // 手动删除 栈 对象
    modifySelfInfo->exec();
    delete modifySelfInfo;
}

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
        LOG()<<"视频大小 大于4G";
        return;
    }

    emit switchUploadVideoPage(StackWidgetPage::UPLOADVEDIO_PAGE);
}

void MyPage::onGetMyselfInfoDone()
{
    auto dataCenter = model::DataCenter::getInstance();
    auto myselfInfo = dataCenter->getMyselfUserInfo();

    // 根据 当前用户的类型 决定显示哪些内容
    if(myselfInfo->isTempUser())
    {
        hideWidget(true);

        ui->avatarBtn->setIcon(QIcon(":/image/defaultAvatar.png"));
        // 临时 用户 不能修改 头像
        ui->avatarBtn->setEnabled(false);

        ui->nickNameBtn->setText("请先登录...");

        ui->nickNameBtn->adjustSize(); // 自动进行调整

        ui->nickNameBtn->setEnabled(true);

        return;
    }else if(myselfInfo->isB()){
        // 系统登录的界面

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
    ui->attentionBtn->hide();
    ui->myVideoLabel->setText("我的视频");
    ui->avatarBtn->setEnabled(true);
}



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

























