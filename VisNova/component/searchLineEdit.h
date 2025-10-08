#pragma once
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "common/myLog.h"

class SearchLineEdit:public QLineEdit
{
    Q_OBJECT
public:
    explicit SearchLineEdit(QWidget* parent);


private slots:
    void onSearchBrnClicked();



signals:
    void _searchVideos(const QString& searchText);

};


