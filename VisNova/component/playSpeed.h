#pragma once
#include <QWidget>
#include "common/myLog.h"

namespace Ui {
class PlaySpeed;
}

class PlaySpeed : public QWidget
{
    Q_OBJECT

public:
    explicit PlaySpeed(QWidget *parent = nullptr);
    ~PlaySpeed();

private slots:
    void onSpeed20Clicked();
    void onSpeed15Clicked();
    void onSpeed10Clicked();
    void onSpeed05Clicked();

signals:
    void speedSignals(double speed);


private:
    Ui::PlaySpeed *ui;
};


