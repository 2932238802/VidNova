#ifndef VEDIOBOX_H
#define VEDIOBOX_H

#include <QWidget>

namespace Ui {
class VedioBox;
}

class VedioBox : public QWidget
{
    Q_OBJECT

public:
    explicit VedioBox(QWidget *parent = nullptr);
    ~VedioBox();
    bool eventFilter(QObject *watched, QEvent *event) override;



private:
    Ui::VedioBox *ui;
};

#endif // VEDIOBOX_H
