#include "editUserForAp.h"
#include "ui_editUserForAp.h"


EditUserForAp::EditUserForAp(QWidget *parent,const QString&titleName) :
    QDialog(parent),
    ui(new Ui::EditUserForAp)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint); // 没有窗口
    setAttribute(Qt::WA_TranslucentBackground); // 就不会 给 window窗口 设置默认的颜色
    ui->titleLabel->setText(titleName); // 移动阴影

    VidNovaMain* mainWindow = VidNovaMain::getInstance();

    // 这个代码的逻辑 就是 这个 全局 0 0 对应这个主要屏幕的左上角位置是多少
    auto [x,y] = mainWindow->mapFromGlobal(QPoint(0,0));
    this->move(-x,-y);
    // 绑定按钮 和 槽函数

    // 编辑框 里面的手机号 进行限制
    QRegularExpression regExp("^1\\d{10}$");
    QValidator* validator = new QRegularExpressionValidator(regExp,this);
    ui->phoneEdit->setValidator(validator);
    ui->roleComboBox->addItem("平台管理员");
    ui->roleComboBox->setCurrentIndex(0);

    connect(ui->cancelBtn,&QPushButton::clicked,this,&EditUserForAp::onCancelBtnClicked);
    connect(ui->submitBtn,&QPushButton::clicked,this,&EditUserForAp::onSubmitBtnClicked);
    connect(ui->commentEdit,&QPlainTextEdit::textChanged,this,[=](){
        QString text = ui->commentEdit->toPlainText();
        int wordCount = text.length();
        if(wordCount<=10)
        {
            ui->wordCount->setText(QString::number(wordCount) + "//10");
        }
        else{
            ui->commentEdit->setPlainText(text.mid(0,10)); // 截取十个
            QTextCursor cursor =  ui->commentEdit->textCursor();
            cursor.movePosition(QTextCursor::End,QTextCursor::MoveAnchor);
            ui->commentEdit->setTextCursor(cursor);
        }
    });
}

EditUserForAp::~EditUserForAp()
{
    delete ui;
}

void EditUserForAp::onCancelBtnClicked()
{
    close();
}

///
/// \brief AddUserForAp::onSubmitBtnClicked
/// 点击提交
void EditUserForAp::onSubmitBtnClicked()
{
    LOG()<<"[suc] 提交编辑内容...";
}

