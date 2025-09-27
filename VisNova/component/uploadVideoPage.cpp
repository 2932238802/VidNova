#include "uploadVideoPage.h"
#include "ui_uploadVideoPage.h"

UploadVideoPage::UploadVideoPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UploadVideoPage)
{
    ui->setupUi(this);
    auto dataCenter = model::DataCenter::getInstance();
    auto kindAndTags = dataCenter->getkatPtr();
    ui->kinds->addItems(kindAndTags->getAllKinds()); // 获取所有的分类
    ui->kinds->setCurrentIndex(-1); // 没有进行任何的选择



    // 初始化 标题和文本的输入最大值
    QString breifIntroduceNumber = ui->breifIntroduceNumber->text();
    maxContentLenth = breifIntroduceNumber.mid(breifIntroduceNumber.indexOf('/')+1).toInt();
    QString titleNumberText(ui->titleNumber->text());
    maxNumberLimit = titleNumberText.mid(titleNumberText.indexOf('/')+1).toInt();
    connect(ui->commitBtn,&QPushButton::clicked,this,&UploadVideoPage::onCommitBtnClicked);
    connect(ui->titleEdit,&QLineEdit::textChanged,this,&UploadVideoPage::onTitleEditTextNumberChanged);
    connect(ui->plainbriefIntroduceEdit,&QPlainTextEdit::textChanged,this,&UploadVideoPage::onPlainBriefIntroduceEditTextNumberChanged);
    connect(ui->changeBtn,&QPushButton::clicked,this,&UploadVideoPage::onChangeBtnClicked);
    connect(ui->kinds,&QComboBox::currentTextChanged,this,&UploadVideoPage::onTagChanged);
}


////////////////////////////////////////////////////////////
/// \brief UploadVideoPage::onCommitBtnClicked
///
void UploadVideoPage::onCommitBtnClicked()
{
    // TODO: 上传到服务器
    emit returnMyPage(StackWidgetPage::MY_PAGE);
}
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
/// \brief UploadVedioPage::onLineEditTextNumberChanged
/// 动态变化数字
void UploadVideoPage::onTitleEditTextNumberChanged(const QString& words)
{
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
    else{
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
/// \brief UploadVideoPage::~UploadVideoPage
/// 析构函数
UploadVideoPage::~UploadVideoPage()
{
    delete ui;
}
////////////////////////////////////////////////////////////






