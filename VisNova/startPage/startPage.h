#pragma once
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include "dataCenter/dataCenter.h"
#include "toast.h"

class StartPage : public QDialog
{
    Q_OBJECT
public:
    explicit StartPage(QDialog *parent = nullptr);
    void startTimer();

private:
    void initConnect();

signals:
    void _loginCompleted();

private:
    bool isLoadCompleted = false;
signals:
};


