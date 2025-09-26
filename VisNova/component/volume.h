#pragma once
#include <QWidget>
#include <QCursor>
#include "common/myLog.h"

namespace Ui {
class Volume;
}

class Volume : public QWidget
{
    Q_OBJECT

public:
    explicit Volume(QWidget *parent = nullptr);
    ~Volume();

private:
    bool eventFilter(QObject * watched,QEvent* event) override;
    void alter();

private:
    Ui::Volume *ui;
    int volume = 35;

signals:
    void volumeSignals(int volume);
};


