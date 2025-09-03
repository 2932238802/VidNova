#ifndef VOLUME_H
#define VOLUME_H

#include <QWidget>
#include <QCursor>

namespace Ui {
class Volume;
}

class Volume : public QWidget
{
    Q_OBJECT

public:
    explicit Volume(QWidget *parent = nullptr);
    ~Volume();

private:
    bool eventFilter(QObject * watched,QEvent* event) override;
    void alter();

private:
    Ui::Volume *ui;
};

#endif // VOLUME_H
