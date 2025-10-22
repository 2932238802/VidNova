#pragma once
#include<QLabel>
#include<QPushButton>
#include"common/myLog.h"
class PageSwitchBtn:public QPushButton
{
    Q_OBJECT
public:
    PageSwitchBtn(QWidget* parent = nullptr);

    void setImageAndText(
        const QString& image_path,
        const QString& text_content,
        int page_id
        );

    void setTextColor(const QString& color);
    void setImage(const QString& image_path);
    int getPageId();

private:
    ///
    /// \brief mousePressEvent
    /// \param event
    /// 重写 按钮
    void mousePressEvent(QMouseEvent* event);

private:
    QLabel*icon;
    QLabel*text;
    int pageId;

signals:
    // 切换页面的信号
    void switchPage(int page_id);
};



