#pragma once
#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QFrame>
#include "vidnovamain.h"
#include "style.h"
#include "myLog.h"

class ConfirmDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfirmDialog(QWidget *parent = nullptr);

signals:

public:
    bool getConfirm() const;
    void setText(const QString& text);

private:
    // void initConnect();

private:
    bool isConfirm = false;
    QLabel* textLabel;

};


