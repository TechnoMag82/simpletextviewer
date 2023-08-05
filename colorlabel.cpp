#include "colorlabel.h"


ColorLabel::ColorLabel(QWidget *parent) : QLabel(parent)
{

}

void ColorLabel::setColor(QColor color)
{
    this->color = color;
}

void ColorLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QColor(0, 0, 0));
    painter.drawRect(QRectF(0, 0, 30.0, 30.0));
    painter.fillRect(QRect(1, 1, 29, 29), color);
}
