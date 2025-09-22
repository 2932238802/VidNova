#pragma once
#include <QWidget>
#include <QFileDialog>
#include "vidnovamain.h"
#include "common/myLog.h"

namespace Ui {
class UploadVideoPage;
}

class UploadVideoPage : public QWidget
{
    Q_OBJECT

public:
    explicit UploadVideoPage(QWidget *parent = nullptr);
    ~UploadVideoPage();

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
    Ui::UploadVideoPage *ui;

};


