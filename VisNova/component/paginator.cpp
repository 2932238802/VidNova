#include "paginator.h"
#include "common/myLog.h"

Paginator::Paginator(int page_count ,QWidget *parent):
    QWidget{parent},
    pageCount(page_count),
    currentPage(1)
{
    // 分页器的初始化

    // 设置分页器的尺寸
    setMinimumSize(QSize(1270,32));

    // 水平布局
    QHBoxLayout * layout = new QHBoxLayout();

    // 设置到窗口上面去
    setLayout(layout);
    layout->setContentsMargins(0,0,3,0);
    layout->setSpacing(8);

    prevBtn = new QPushButton();
    prevBtn->setIcon(QIcon(":/image/left-unhover.png"));
    setBtnStyle(prevBtn);
    nextBtn = new QPushButton();
    nextBtn->setIcon(QIcon(":/image/right-unhover.png"));
    setBtnStyle(nextBtn);

    if(pageCount<=7)
    {
        // 不需要折叠
        for(int i = 0 ; i < pageCount ; i ++)
        {
            PageBtn* pageBtn = new PageBtn(i+1);
            if(i == 0)
            {
                pageBtn->setActive(true);
            }
            pageBtns.append(pageBtn);
        }
    }
    else{
        // 超过 7 个的话 前五个 显示
        // 默认显示第一个
        for(int i = 1; i <=5 ; i++)
        {
            PageBtn* pageBtn = new PageBtn(i);

            if(i == 1)
            {
                pageBtn->setActive(true);
            }
            pageBtns.append(pageBtn);
        }

        // 前五个按钮 处理好
        // 然后是折叠按钮的设置
        PageBtn* pageBtn = new PageBtn(0);
        pageBtn->setFolded(true);
        pageBtns.append(pageBtn);


        // 添加最后一页
        PageBtn* pageBtn2 = new PageBtn(pageCount);
        pageBtns.append(pageBtn2);
    }


    // 创建 QLineEdit
    pageNumberEdit = new QLineEdit();
    pageNumberEdit->setFixedSize(QSize(48,32));
    // pageNumberEdit->setAlignment(Qt::AlignLeft);
    pageNumberEdit->setAlignment(Qt::AlignCenter); // 水平居中AlignHCenter
    pageNumberEdit->setStyleSheet(PAGENUMBEREDIT);


    // 跳转的 Qlabel
    QLabel* jumpToPageLabel = new QLabel("跳至");
    QLabel* jumpToYeLabel = new QLabel("页");

    // 创建好了 样式 加入到 布局器里面


    // 前面有个空格 就是
    layout->addStretch();
    layout->addWidget(prevBtn);
    for(int i = 0 ; i < pageBtns.size(); i++)
    {
        layout->addWidget(pageBtns[i]);
    }
    layout->addWidget(nextBtn);
    layout->addWidget(jumpToPageLabel);
    layout->addWidget(pageNumberEdit);
    layout->addWidget(jumpToYeLabel);

    initSignalAndSlots();

}

void Paginator::setBtnStyle(btn_t btn)
{
    btn->setFixedSize(QSize{32,32});

    btn->setIconSize(QSize{32,32});

    btn->setStyleSheet(PAGINATOR_QPUSHBUTTON_DEFAULT_FOR_LEFT_AND_RIGHT);

}

void Paginator::initSignalAndSlots()
{
    // 绑定上一页 和 下一页的信号槽
    connect(prevBtn,&QPushButton::clicked,this,&Paginator::onPrevPageClick);
    connect(nextBtn,&QPushButton::clicked,this,&Paginator::onNextPageClick);

    for(auto *a:pageBtns)
    {
        connect(a,&QPushButton::clicked,this,&Paginator::onInnerBtnClick);
    }

    connect(pageNumberEdit,&QLineEdit::returnPressed,this,[=](){
        int pageNumber = pageNumberEdit->text().toInt();
        LOG()<<"手动输入页面跳转"<<pageNumber<<"...";
        if(pageNumber <= 1)
            {
            pageNumber = 1;
        }
        if(pageNumber >= pageCount)
            {
            pageNumber = pageCount;
        }
        jumpToPage(pageNumber);
    });
}

///
/// \brief Paginator::jumpToPage
/// \param page_number
/// 跳转的逻辑
void Paginator::jumpToPage(int page_number)
{
    if (page_number < 1 || page_number > pageCount || page_number == currentPage) {
        return;
    }

    currentPage = page_number;
    pageNumberEdit->setText(QString::number(currentPage)); // 直接设置出入的框

    if (pageCount <= 7) {
        for (int i = 0; i < pageBtns.size(); ++i) {
            pageBtns[i]->setPageNumber(i + 1);
            pageBtns[i]->setFolded(false);
            pageBtns[i]->setActive((i + 1) == currentPage);
        }
    } else {
        // 总页数多，处理折叠逻辑
        // pageBtns[0] 到 pageBtns[6]
        int p = currentPage;
        int N = pageCount;

        // 先处理前后
        pageBtns[0]->setPageNumber(1);
        pageBtns[6]->setPageNumber(N);
        pageBtns[0]->setFolded(false);
        pageBtns[6]->setFolded(false);

        if (p < 5) {
            // * （* * * * ...） *
            for(int i=1; i<5; ++i) pageBtns[i]->setPageNumber(i + 1);
            pageBtns[1]->setFolded(false);
            pageBtns[2]->setFolded(false);
            pageBtns[3]->setFolded(false);
            pageBtns[4]->setFolded(false);
            pageBtns[5]->setFolded(true);
        } else if (p > N - 4) {
            //  // * （... * * * * ） *
            pageBtns[1]->setFolded(true);
            for(int i=2; i<6; ++i) pageBtns[i]->setPageNumber(N - (6-i));
            pageBtns[2]->setFolded(false);
            pageBtns[3]->setFolded(false);
            pageBtns[4]->setFolded(false);
            pageBtns[5]->setFolded(false);
        } else { // 中间: 1 ... p-1 p p+1 ... N
            pageBtns[1]->setFolded(true);
            pageBtns[2]->setPageNumber(p - 1);
            pageBtns[3]->setPageNumber(p);
            pageBtns[4]->setPageNumber(p + 1);
            pageBtns[5]->setFolded(true);
            pageBtns[2]->setFolded(false);
            pageBtns[3]->setFolded(false);
            pageBtns[4]->setFolded(false);
        }
        for (auto* btn : pageBtns)
        {
            if (!btn->getFolded()) {
                btn->setActive(btn->getPageNumber() == currentPage);
            } else {
                btn->setActive(false);
            }
        }
    }

}


void Paginator::onPrevPageClick()
{
    if(currentPage == 1)
    {
        return;
    }

    jumpToPage(currentPage-1);
}

void Paginator::onNextPageClick()
{
    if(currentPage == pageCount)
    {
        return;
    }

    jumpToPage(currentPage+1);
}

void Paginator::onInnerBtnClick()
{
    PageBtn* send = static_cast<PageBtn*>(sender());
    int pageNum = send->getPageNumber();
    jumpToPage(pageNum);
}

