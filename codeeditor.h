#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QWidget>
#include <QSize>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTextCursor>
#include <QPainter>
#include <QRect>
#include <QTextBlock>
#include <QColor>
#include <QDebug>
#include <QRegExp>
#include <QLabel>

#include "linenumberarea.h"
#include "colorlabel.h"
#include "consts.h"

class LineNumberArea;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
    public:
        explicit CodeEditor(QWidget *parent = nullptr);
        ~CodeEditor();

        void lineNumberAreaPaintEvent(QPaintEvent *event);
        int lineNumberAreaWidth();
        void setLineNumberColor(QColor &color);
        void setCurrentLineColor(QColor &color);
        void setBackgroundColor(QColor &color);
        void setTextColor(QColor &color);
        void applyColorTheme();

    protected:
        void resizeEvent(QResizeEvent *event) override;
        virtual void mouseMoveEvent(QMouseEvent *mouseEvent) override;

    private slots:
        void updateLineNumberAreaWidth(int newBlockCount);
        void highlightCurrentLine();
        void updateLineNumberArea(const QRect &rect, int dy);

    private:
        LineNumberArea *lineNumberArea;
        QColor *lineNumberColor = nullptr;
        QColor *currentLineColor = nullptr;
        QColor *backgroundColor = nullptr;
        QColor *textColor = nullptr;
        ColorLabel *colorLabel = nullptr;
        int stringPosition = -1;
        QRegExp rx/*("^#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$")*/;
        int oldX = 0;
        int oldY = 0;

};

#endif // CODEEDITOR_H
