#pragma once
#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class PlayerSlider;
}

class PlayerSlider : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerSlider(QWidget *parent = nullptr);
    ~PlayerSlider();

private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void moveSlider() const;

private:
    Ui::PlayerSlider *ui;
    int playProgress;
};

