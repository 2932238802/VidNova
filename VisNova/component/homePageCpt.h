#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QButtonGroup>
#include"dataCenter/data.h"
#include "dataCenter/dataCenter.h"
#include "common/myLog.h"
#include"style/style.h"
#include "ui_homePageCpt.h"
#include "videoBox.h"

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
    void initConnect();
    ~homePageCpt();

private:
    QPushButton* buildBtn(QWidget* parent,const QString&color,const QString&text );
    void clearLayoutAndBtn(QLayout* layout);
    void initVideos();
    void openPlayerPage(const QString& path);

private slots:
    void onTopBtnClicked();
    void onRefreshBtnClicked();

private:
    Ui::homePageCpt *ui;
    QButtonGroup* tagsGp;

};


