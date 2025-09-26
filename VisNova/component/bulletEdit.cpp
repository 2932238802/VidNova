#include "bulletEdit.h"
#include "ui_bulletEdit.h"

BulletEdit::BulletEdit(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BulletEdit)
{
    ui->setupUi(this);
    ui->bulletTextEdit->setMaxLength(30);
    connect(ui->sendBtn,&QPushButton::clicked,this,&BulletEdit::onSendBtnClicked);
}

BulletEdit::~BulletEdit()
{
    delete ui;
}

void BulletEdit::onSendBtnClicked()
{
    emit sendBullet(ui->bulletTextEdit->text());
}


