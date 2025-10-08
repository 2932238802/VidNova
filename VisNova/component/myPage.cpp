#include "myPage.h"
#include "ui_myPage.h"

MyPage::MyPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyPage)
{
    ui->setupUi(this);initUi();

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

    connect(ui->avatarBtn,&QPushButton::clicked,this,&MyPage::onAvatarBtnClicked);
    connect(ui->modifyBtn,&QPushButton::clicked,this,&MyPage::onModifyBtnClicked);
    connect(ui->uploadVedioBtn,&QPushButton::clicked,this,&MyPage::onUploadVedioBtnClicked);
}

///
/// \brief MyPage::onAvatarBtnClicked
///
void MyPage::onAvatarBtnClicked()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr,"修改头像","","jpg or png(*.jpg *.png)");

    if(filePath.isEmpty())
    {
        return;
    }
    LOG()<<"[suc]"<<"filePath: "<<filePath;

    QByteArray fileData(loadFileToByteArray(filePath));

    if(fileData.isEmpty())
    {
        LOG()<<"[err] 读取文件失败!";
        return;
    }

    ui->avatarBtn->setIcon(makeIcon(fileData,ui->avatarBtn->width(),ui->avatarBtn->height()));
    ui->avatarBtn->setStyleSheet(MYPAGE_AVATAR_CLEAR_STYLE);

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

void MyPage::onUploadVedioBtnClicked()
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

    emit switchUploadVedioPage(StackWidgetPage::UPLOADVEDIO_PAGE);
}






