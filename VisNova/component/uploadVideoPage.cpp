#include "uploadVideoPage.h"
#include "ui_uploadVideoPage.h"

////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::UploadVideoPage
/// \param parent
///
UploadVideoPage::UploadVideoPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UploadVideoPage)
{
    ui->setupUi(this);
    mpvPlayer = std::make_unique<MpvPlayer>();
    initUi();
    initConnect();
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::onCommitBtnClicked
///
void UploadVideoPage::onCommitBtnClicked()
{
    model::VideoInfoForUpload videoInfo;
    videoInfo.videoFileId = videoFileId;
    videoInfo.photoFileId = videoCoverId;
    videoInfo.videoTitle = ui->titleEdit->text();
    videoInfo.videoDesc = ui->plainbriefIntroduceEdit->toPlainText();
    videoInfo.kind = ui->kinds->currentText();
    videoInfo.duration = videoDuration;

    QList<QPushButton*> tagBtns = ui->tagContent->findChildren<QPushButton*>();

    for(auto& tagBtn:tagBtns)
    {
        if(tagBtn->isChecked())
        {
            QString tagText = tagBtn->text();
            videoInfo.tags.append(tagText);
        }
    }

    auto dataCenter = model::DataCenter::getInstance();
    dataCenter->uploadVideoInfoForUploadAsync(videoInfo);


}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVedioPage::onLineEditTextNumberChanged
/// 动态变化数字
void UploadVideoPage::onTitleEditTextNumberChanged(const QString& words)
{
    checkCommitBtnState();

    QString titleNumberText(ui->titleNumber->text());
    int wordCount = words.length();
    if(wordCount <= maxNumberLimit)
    {
        // 自动更新最大值
        ui->titleNumber->setText(QString::number(wordCount) + '/' + QString::number(maxNumberLimit));
    }
    else{
        ui->titleEdit->setText(words.mid(0,maxNumberLimit));
    }
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::onPlainBriefIntroduceEditTextNumberChanged
/// 简介 字数变化 信号槽
void UploadVideoPage::onPlainBriefIntroduceEditTextNumberChanged()
{
    QString content = ui->plainbriefIntroduceEdit->toPlainText();
    int contentLenth = content.length();

    if(contentLenth <=maxContentLenth )
    {
        ui->breifIntroduceNumber->setText(QString::number(contentLenth) + '/' + QString::number(maxContentLenth));
    }
    else
    {
        ui->plainbriefIntroduceEdit->setPlainText(content.mid(0,maxContentLenth));

        // 注意设置滚动条
        // QTextCursor::MoveAnchor 不会创建任何的选取
        QTextCursor cursor =  ui->plainbriefIntroduceEdit->textCursor();
        cursor.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
        ui->plainbriefIntroduceEdit->setTextCursor(cursor);
    }
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::onUploadVideoDone
///
void UploadVideoPage::onUploadVideoDone(const QString& video_id)
{

#ifdef UPLOADVIDEOPAGE_TEST
    LOG() << "UploadVideoPage::onUploadVideoDone(const QString& video_id)";
#endif

    checkCommitBtnState();

    ui->downIcon->show();
    ui->loadProgress->setText("上传完成");

    isUploadVideoOk = true; // 上传

    videoFileId = video_id;
    QString firstFrame = MpvPlayer::getVideoFirstPage(videoPath);

    if(firstFrame.isEmpty())
    {

#ifdef UPLOADVIDEOPAGE_TEST
        LOG() << "获取首帧失败...";
#endif
        return ;
    }


    QPixmap pixmap(firstFrame);
    pixmap = pixmap.scaled(ui->imageBox->size(),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    ui->imageLabel->setPixmap(pixmap);
    uploadPhoto(firstFrame);
    QFile::remove(firstFrame);

    // 获取视频的总时长
    // videoPath 视频路径
    // setTitleAndPath 这个函数 设置

    mpvPlayer->startPlay(videoPath); // 播放 其实是加载
    mpvPlayer->pause();
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::onGetVideoDuraion
/// \param duration
///
void UploadVideoPage::onGetVideoDuraion(int64_t duration)
{
#ifdef UPLOADVIDEOPAGE_TEST
    LOG() << "UploadVideoPage::onGetVideoDuraion(int64_t duration)";
    LOG() << "视频的持续时间 duraion:" << duration;
#endif

    checkCommitBtnState();

    isGetVideoDurationOk = true;
    videoDuration = duration;
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::onGetVideoCoverDone
/// \param file_id
/// \param pup
///
void UploadVideoPage::onGetVideoCoverDone(const QString &file_id, PhotoUploadPurpose pup)
{
#ifdef UPLOADVIDEOPAGE_TEST
    LOG() << "UploadVideoPage::onGetVideoCoverDone(const QString &file_id, PhotoUploadPurpose pup)";
#endif

    checkCommitBtnState();

    if(pup!= PhotoUploadPurpose::VideoCover)
    {
        return;
    }

    videoCoverId = file_id;
    isUploadPhotoOk = true;

}
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::onUploadVideoInfoForUploadDone
void UploadVideoPage::onUploadVideoInfoForUploadDone()
{
#ifdef UPLOADVIDEOPAGE_TEST
    LOG() << "UploadVideoPage::onUploadVideoInfoForUploadDone()";
#endif

    reset();
    // TODO: 上传到服务器
    emit returnMyPage(StackWidgetPage::MY_PAGE);
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::onChangeBtnClicked
/// 选择视频封面
void UploadVideoPage::onChangeBtnClicked()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,"选择视频封面图","","Images(*.png *.jpg)");
    if(fileName.isEmpty())
    {
        LOG()<<"用户输入内容为空";
        return;
    }

    QPixmap pixMap(fileName);
    pixMap = pixMap.scaled(ui->imageLabel->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->imageLabel->setPixmap(pixMap);
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::onTagChanged
/// 标签变化
void UploadVideoPage::onTagChanged(const QString &choosed_tag)
{
    addTags(choosed_tag);
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::addTags
/// \param str
/// 选择完 种类之后 显示对应的标签
void UploadVideoPage::addTags(const QString &str)
{
    if(str.isEmpty())
    {
        return ;
    }
    QLayoutItem* item;
    while((item = ui->tagsLayout->takeAt(0)) != nullptr)
    {
        if(item->widget())
        {
            item->widget()->deleteLater();
        }
        // QLayoutItem 没有什么 信号槽的机制 可以直接删除
        delete item;
    }

    auto dataCenter = model::DataCenter::getInstance();
    auto kat = dataCenter->getkatPtr();
    auto tags = kat->getAllLabels(str).keys();

    for(auto& tag : tags)
    {
        QPushButton* btn = new QPushButton();
        btn->setFixedSize(90,45);
        btn->setText(tag);
        btn->setCheckable(true);
        btn->setStyleSheet(UPLOADPA_TAG);
        ui->tagsLayout->addWidget(btn); // 加入水平
    }

    ui->tagsLayout->insertSpacing(tags.size(),ui->tags->width()-(90+20)*tags.size());
    ui->tagsLayout->setSpacing(20);
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::initUi
///
void UploadVideoPage::initUi()
{

    auto dataCenter = model::DataCenter::getInstance();
    auto kindAndTags = dataCenter->getkatPtr();
    ui->kinds->addItems(kindAndTags->getAllKinds()); // 获取所有的分类
    ui->kinds->setCurrentIndex(-1); // 没有进行任何的选择

    // 初始化 标题和文本的输入最大值
    QString breifIntroduceNumber = ui->breifIntroduceNumber->text();
    maxContentLenth = breifIntroduceNumber.mid(breifIntroduceNumber.indexOf('/')+1).toInt();
    QString titleNumberText(ui->titleNumber->text());
    maxNumberLimit = titleNumberText.mid(titleNumberText.indexOf('/')+1).toInt();

    // 默认情况下面隐藏
    ui->downIcon->hide();
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::initConnect
///
void UploadVideoPage::initConnect()
{
    auto dataCenter = model::DataCenter::getInstance();
    connect(ui->commitBtn,&QPushButton::clicked,this,&UploadVideoPage::onCommitBtnClicked);
    connect(ui->titleEdit,&QLineEdit::textChanged,this,&UploadVideoPage::onTitleEditTextNumberChanged);
    connect(ui->plainbriefIntroduceEdit,&QPlainTextEdit::textChanged,this,&UploadVideoPage::onPlainBriefIntroduceEditTextNumberChanged);
    connect(ui->changeBtn,&QPushButton::clicked,this,&UploadVideoPage::onChangeBtnClicked);
    connect(ui->kinds,&QComboBox::currentTextChanged,this,&UploadVideoPage::onTagChanged);
    connect(dataCenter,&model::DataCenter::_uploadVideoDone,this,&UploadVideoPage::onUploadVideoDone);
    connect(mpvPlayer.get(),&MpvPlayer::_duration,this,&UploadVideoPage::onGetVideoDuraion);
    connect(dataCenter,&model::DataCenter::_uploadPhotoDone,this,&UploadVideoPage::onGetVideoCoverDone);

    connect(dataCenter,&model::DataCenter::_uploadVideoInfoForUpload,this,&UploadVideoPage::onUploadVideoInfoForUploadDone) ;
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::checkCommitBtnState
///
void UploadVideoPage::checkCommitBtnState()
{
#ifdef UPLOADVIDEOPAGE_TEST
    LOG() << "checkCommitBtnState()";
    LOG() << "检查一下 提交按钮的状态";
#endif

    bool isready = isUploadVideoOk && isUploadPhotoOk && isGetVideoDurationOk && !ui->titleEdit->text().isEmpty();
    ui->commitBtn->setEnabled(isready);
}
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::reset
///
void UploadVideoPage::reset()
{
    ui->fileName->setText("这里是文件名");
    ui->loadProgress->setText("上传中...");
    ui->downIcon->hide();

    ui->titleEdit->setText("");
    ui->plainbriefIntroduceEdit->setPlainText("");
    ui->imageLabel->setStyleSheet(UPLOADVIDEOPAGE_IMAGELABEL);


    ui->kinds->setCurrentIndex(-1);
    addTags("");

    isUploadPhotoOk = false;
    isUploadVideoOk = false;
    isGetVideoDurationOk = false;

    videoFileId = "";
    videoCoverId = "";
    videoDuration = 0;
    videoPath = "";

}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::uploadPhoto
///
void UploadVideoPage::uploadPhoto(const QString& photo_path)
{
    QByteArray imageData = loadFileToByteArray(photo_path);
    if(imageData.isEmpty())
    {
#ifdef UPLOADVIDEOPAGE_TEST
        LOG() << "读取封面图 失败...";
#endif
        return;
    }

    auto dataCenter = model::DataCenter::getInstance();

    dataCenter->uploadPhotoAsync(imageData,PhotoUploadPurpose::VideoCover);
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::~UploadVideoPage
/// 析构函数
UploadVideoPage::~UploadVideoPage()
{
    delete ui;
}
////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::setTitleAndPath
/// \param video_path
///
void UploadVideoPage::setTitleAndPath(const QString &video_path)
{

#ifdef UPLOADVIDEOPAGE_TEST
    LOG() << "UploadVideoPage::setTitleAndPath(const QString &video_path)";
    LOG() << "video_path: " << video_path;
#endif

    videoPath = video_path;

    auto pos = video_path.lastIndexOf('/') + 1;

    QString videoTitle = video_path.mid(pos).trimmed();

    ui->fileName->setText(videoTitle);

    ui->titleEdit->setText(videoTitle);


}
////////////////////////////////////////////////////////////


























