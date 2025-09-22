#pragma once
#include <QWidget>
#include <QPushButton>
#include "style.h"

class PageBtn : public QPushButton
{
    Q_OBJECT
public:
    ///
    /// \brief PageBtn
    /// \param page_number
    /// \param parent
    /// 默认页面一开始 是一个
    explicit PageBtn(int page_number = 1,QWidget *parent = nullptr);
    void setActive(bool is);
    void setFolded(bool is);
    void setPageNumber(int number);
    int getPageNumber() const;
    bool getFolded() const;
    bool getActived() const;


private:
    int pageNumber;
    bool isActived = false;
    bool isFolded = false ;

signals:
};
