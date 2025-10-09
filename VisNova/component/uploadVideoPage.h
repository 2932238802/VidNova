#pragma once
#include <QWidget>
#include <QFileDialog>
#include "vidnovamain.h"
#include "dataCenter/dataCenter.h"
#include "dataCenter/videoInfo.h"
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
    void onTagChanged(const QString &choosed_tag);

private:
    void addTags(const QString& str);


signals:
    void returnMyPage(int page_id);
    void tagChanged(const QString &choosed_tag);



private:
    int maxContentLenth;
    int maxNumberLimit;
    Ui::UploadVideoPage *ui;

};


