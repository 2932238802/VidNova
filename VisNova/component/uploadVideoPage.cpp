#include "uploadVideoPage.h"
#include "ui_uploadVideoPage.h"

UploadVideoPage::UploadVideoPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UploadVideoPage)
{

    ui->setupUi(this);

    // 初始化 标题和文本的输入最大值
    QString breifIntroduceNumber = ui->breifIntroduceNumber->text();
    maxContentLenth = breifIntroduceNumber.mid(breifIntroduceNumber.indexOf('/')+1).toInt();
    QString titleNumberText(ui->titleNumber->text());
    maxNumberLimit = titleNumberText.mid(titleNumberText.indexOf('/')+1).toInt();

    connect(ui->commitBtn,&QPushButton::clicked,this,&UploadVideoPage::onCommitBtnClicked);
    connect(ui->titleEdit,&QLineEdit::textChanged,this,&UploadVideoPage::onTitleEditTextNumberChanged);
    connect(ui->plainbriefIntroduceEdit,&QPlainTextEdit::textChanged,this,&UploadVideoPage::onPlainBriefIntroduceEditTextNumberChanged);
    connect(ui->changeBtn,&QPushButton::clicked,this,&UploadVideoPage::onChangeBtnClicked);
}

UploadVideoPage::~UploadVideoPage()
{
    delete ui;
}

void UploadVideoPage::onCommitBtnClicked()
{
    // TODO: 上传到服务器

    //
    emit returnMyPage(StackWidgetPage::MY_PAGE);

}

///
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




















