#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QTime>

class start_page : public QDialog
{
    Q_OBJECT
public:
    explicit start_page(QDialog *parent = nullptr);
    void startTimer();

signals:
};

#endif // STARTPAGE_H
