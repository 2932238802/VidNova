#pragma once
#include <QWidget>
#include "playerPage.h"
#include "common/myLog.h"
#include"toast.h"
#include"lrPage/login.h"

namespace Ui {
class VideoBox;
}

class VideoBox : public QWidget
{
    Q_OBJECT

public:
    explicit VideoBox(QWidget *parent = nullptr);
    ~VideoBox();
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void onPlayBtnClicked();

private:
    Ui::VideoBox *ui;
    PlayerPage* playerPage;
};

