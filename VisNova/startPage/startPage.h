#pragma once
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include "dataCenter/dataCenter.h"

class StartPage : public QDialog
{
    Q_OBJECT
public:
    explicit StartPage(QDialog *parent = nullptr);
    void startTimer();

private:
    void initConnect();

private slots:
    void onTempLogin();

private:
    bool isLoginIn = false;

signals:
};


