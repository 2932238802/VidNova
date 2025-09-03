#include "homePageCpt.h"
#include "ui_homePageCpt.h"
#include "videoBox.h"


homePageCpt::homePageCpt(QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::homePageCpt),
    tagsGp(nullptr)
{

    ui->setupUi(this);
    initKindAndTags(); //跳转到这个页面的时候的初始化
    initRefreshAndTopBtn();
    initVedios(); //初始化 视频
}

void homePageCpt::initKindAndTags()
{
    kinds = {"1","2","3"};
    kindTags = {
                {"1",{"1","2"}},
                {"2",{"1","2","3"}},
                {"3",{"1","2","3","4"}},
                };
    tagsGp = new QButtonGroup(this);
    tagsGp->setExclusive(false); // 可以多选标签
    QPushButton* kindBtn = buildBtn(ui->classifys,"#3ECEFF","分类");
    ui->classifyHLayout->addWidget(kindBtn); //添加到布局里里面
    QButtonGroup* qBtnGp = new QButtonGroup(this); // 绑在树上了
    qBtnGp->setExclusive(true); // 表示互斥 // 保证只有一个按钮被选中


    for(auto a:kinds)
    {
        QPushButton* btn = buildBtn(ui->classifys,"#666666",a);
        btn->setCheckable(true); // 设置成可以检查的 这样就会有 按下和松开两种状态
        ui->classifyHLayout->addWidget(btn);
        qBtnGp->addButton(btn);

        connect(btn,&QPushButton::toggled,this,[=](bool is_click){
            if(is_click)
            {
                btn->setStyleSheet("background-color: #F1FDFF; color:#3ECEFF;");
                resetTags(kindTags[a]);
            }
            else{
                btn->setStyleSheet("color: #666666; background-color: transparent;");
            }
        });

    }

    // qBtnGp->buttons() 本质是 列表
    qBtnGp->buttons().first()->setChecked(true);
    ui->classifyHLayout->setSpacing(8); // 设置间距
}


void homePageCpt::resetTags(const QList<QString> &tags_contain)
{
    clearLayoutAndBtn(ui->labelHLayout); // 先清空
    QPushButton* tag = buildBtn(ui->labels,"#3ECEFF","标签");
    ui->labelHLayout->addWidget(tag); // 添加 “分类” 标签

    for(auto& a:tags_contain)
    {
        QPushButton* tagItem = buildBtn(ui->labels,"#666666",a);
        tagItem->setCheckable(true);
        ui->labelHLayout->addWidget(tagItem);
        tagsGp->addButton(tagItem);
        connect(tagItem,&QPushButton::toggled,this,[=](bool is_check){
            if(is_check)
            {
                tagItem->setStyleSheet("background-color: #F1FDFF; color: #3ECEFF");
            }
            else{
                tagItem->setStyleSheet("background-color:transparent; color: #666666");
            }
        });
    }
    ui->labelHLayout->setSpacing(8);

}

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
};


QPushButton* homePageCpt::buildBtn(QWidget *parent, const QString &color, const QString &text)
{
    QPushButton* btn = new QPushButton(text,parent);
    btn->setStyleSheet("color:"+color);
    btn->setMinimumHeight(26); // 设置最小的高度
    btn->setFixedWidth(text.size()*16+18+18); //18 是左右边距
    return btn;
}

void homePageCpt::clearLayoutAndBtn(QLayout *layout)
{
    if(layout == nullptr)
    {
        LOG()<<"[wa] layout 内容为空";
    }
    for(auto a: tagsGp->buttons())
    {
        tagsGp->removeButton(a);
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
}

void homePageCpt::initVedios()
{
    for(int i  =0 ;i < 16 ;i++)
    {
        VideoBox* vedioBox = new VideoBox();

        // 一行显示四个
        ui->vedioGLayout->addWidget(vedioBox,i/4,i%4,1,1); // 行 列

    }

}

void homePageCpt::onTopBtnClicked()
{
    LOG()<<"[INFO] 置顶按钮点击";
}

void homePageCpt::onRefreshBtnClicked()
{
    LOG()<<"[INFO] 刷新按钮点击";
}

homePageCpt::~homePageCpt()
{
    delete ui;
}
