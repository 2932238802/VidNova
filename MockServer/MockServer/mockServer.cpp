#include "mockServer.h"
#include "ui_mockServer.h"

MockServer::MockServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MockServer)
{
    ui->setupUi(this);
}

MockServer::~MockServer()
{
    delete ui;
}
