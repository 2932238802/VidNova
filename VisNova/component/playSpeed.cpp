#include "playSpeed.h"
#include "ui_playSpeed.h"

PlaySpeed::PlaySpeed(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlaySpeed)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    connect(ui->speed05,&QPushButton::clicked,this,&PlaySpeed::onSpeed05Clicked);
    connect(ui->speed10,&QPushButton::clicked,this,&PlaySpeed::onSpeed10Clicked);
    connect(ui->speed15,&QPushButton::clicked,this,&PlaySpeed::onSpeed15Clicked);
    connect(ui->speed20,&QPushButton::clicked,this,&PlaySpeed::onSpeed20Clicked);
}

PlaySpeed::~PlaySpeed()
{
    delete ui;
}

void PlaySpeed::onSpeed20Clicked()
{
    LOG()<<"[suc] 2倍数播放...";
}

void PlaySpeed::onSpeed15Clicked()
{
    LOG()<<"[suc] 1.5倍数播放...";
}

void PlaySpeed::onSpeed10Clicked()
{
    LOG()<<"[suc] 1倍数播放...";
}

void PlaySpeed::onSpeed05Clicked()
{
    LOG()<<"[suc] 0.5倍数播放...";
}
