#pragma once

#include <QWidget>
#include<QPushButton>
#include <QLineEdit>
#include <QLayout>
#include<QHBoxLayout>
#include <QLabel>
#include "pageBtn.h"

class Paginator: public QWidget
{
    using btn_t = QPushButton*;
    Q_OBJECT
public:
    Paginator(int page_count , QWidget* parent);

private:
    void setBtnStyle(btn_t btn);
    void initSignalAndSlots();
    void jumpToPage(int page_number);


private slots:
    void onPrevPageClick();
    void onNextPageClick();
    void onInnerBtnClick();


private:
    size_t pageCount = 7; // 默认给 7 页码
    size_t pageSize = 20;
    size_t currentPage = 1; // 默认页面
    btn_t prevBtn;
    btn_t nextBtn;
    QList<PageBtn*> pageBtns;
    QLineEdit* pageNumberEdit;
};

