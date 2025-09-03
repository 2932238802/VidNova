#pragma once
#include <QWidget>
#include <QFileDialog>
#include "vidnovamain.h"
#include "common/myLog.h"

namespace Ui {
class UploadVedioPage;
}

class UploadVedioPage : public QWidget
{
    Q_OBJECT

public:
    explicit UploadVedioPage(QWidget *parent = nullptr);
    ~UploadVedioPage();

private slots:
    void onCommitBtnClicked();
    void onTitleEditTextNumberChanged(const QString& words);
    void onPlainBriefIntroduceEditTextNumberChanged();
    void onChangeBtnClicked();

signals:
    void returnMyPage(int page_id);

private:
    int maxContentLenth;
    int maxNumberLimit;
    Ui::UploadVedioPage *ui;

};


