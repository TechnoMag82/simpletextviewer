#ifndef COLORLABEL_H
#define COLORLABEL_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QColor>

class ColorLabel : public QLabel
{
    Q_OBJECT
    public:
        explicit ColorLabel(QWidget *parent = 0);
        void setColor(QColor color);

    protected:
        void paintEvent(QPaintEvent *event) override;

    private:
        QColor color;
};

#endif // COLORLABEL_H
