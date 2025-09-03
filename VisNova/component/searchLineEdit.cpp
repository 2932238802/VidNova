#include "searchLineEdit.h"


SearchLineEdit::SearchLineEdit(QWidget *parent):
    QLineEdit{parent}
{
    this->setFixedSize(320,36);
    this->setPlaceholderText("请输入搜索的内容");
    setTextMargins(24,0,0,0);

    setStyleSheet(R"(
                  #search{
                  background-color: #FFFFFF;
                  border-radius: 15px;
                  border: 1px solid #3ECEFE;
                  font-family: '微软雅黑';
                  font-style: normal;
                  color: #000000;      })"
                  );

    // 图片设置
    QLabel* labelImage = new QLabel(this);
    // labelImage->setFixedSize(16,16);
    labelImage->setPixmap(QPixmap(":/image/search.png").scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    labelImage->setStyleSheet("background-color: transparent;");

    // 按钮
    QPushButton* searchBtn = new QPushButton(this);
    searchBtn->setText("搜索");
    searchBtn->setFixedSize(62,32);
    searchBtn->setStyleSheet("background-color: #3ECEFE;"
                              "border-radius: 16px;"
                              "font-family: '微软雅黑';"
                              "color: #FFFFFF;"
                              "font-style: normal;");

    // 水平布局其
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(labelImage);
    layout->addStretch(); // 空白区域 和 弹簧一样
    layout->addWidget(searchBtn);
    layout->setContentsMargins(11,0,2,0);

    // 绑定的效果和槽函数
    // 回车
    connect(searchBtn,&QPushButton::clicked,this,&SearchLineEdit::onSearchBrnClicked);
    connect(this,&QLineEdit::returnPressed,this,&SearchLineEdit::onSearchBrnClicked);




















}

void SearchLineEdit::onSearchBrnClicked()
{
    LOG()<<"[info] 搜索按钮点击";
}














