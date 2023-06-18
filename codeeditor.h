#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QWidget>
#include <QSize>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QTextBlock>
#include <QColor>

#include "linenumberarea.h"

class LineNumberArea;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
    public:
        explicit CodeEditor(QWidget *parent = nullptr);

        void lineNumberAreaPaintEvent(QPaintEvent *event);
        int lineNumberAreaWidth();
        void setLineNumberColor(QColor &color);
        void setCurrentLineColor(QColor &color);
        void setBackgroundColor(QColor &color);
        void setTextColor(QColor &color);
        void applyColorTheme();

    protected:
        void resizeEvent(QResizeEvent *event) override;

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

};

#endif // CODEEDITOR_H
