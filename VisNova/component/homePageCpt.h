#pragma once

#include <QWidget>
#include <QPushButton>
#include"style/btnStyle.h"
#include "ui_homePageCpt.h"
#include <QButtonGroup>
#include "common/myLog.h"
#include <QVBoxLayout>
namespace Ui {
class homePageCpt;
}

class homePageCpt : public QWidget
{
    Q_OBJECT

public:
    explicit homePageCpt(QWidget *parent = nullptr);
    void initKindAndTags();
    void resetTags(const QList<QString>& tags_contain);
    void initRefreshAndTopBtn();
    ~homePageCpt();

private:
    QPushButton* buildBtn(QWidget* parent,const QString&color,const QString&text );
    void clearLayoutAndBtn(QLayout* layout);
    void initVedios();

private slots:
    void onTopBtnClicked();
    void onRefreshBtnClicked();

private:
    Ui::homePageCpt *ui;
    QButtonGroup* tagsGp;
    QHash<QString,QList<QString>> kindTags;
    QList<QString> kinds;
};


