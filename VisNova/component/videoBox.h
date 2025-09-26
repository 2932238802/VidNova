#pragma once
#include <QWidget>
#include <QDir>
#include "mpvPlayer.h"
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

    ///
    /// \brief eventFilter
    /// \param watched
    /// \param event
    /// \return
    /// 虚函数重写
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void onPlayBtnClicked();
    void checkPlayPageIsNullptr();

private slots:
    void onPlayerPageDestroyed();

private:
    Ui::VideoBox *ui;
    PlayerPage* playerPage;

};

