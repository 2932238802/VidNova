#ifndef MOCKSERVER_H
#define MOCKSERVER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MockServer;
}
QT_END_NAMESPACE

class MockServer : public QWidget
{
    Q_OBJECT

public:
    MockServer(QWidget *parent = nullptr);
    ~MockServer();

private:
    Ui::MockServer *ui;
};
#endif // MOCKSERVER_H
