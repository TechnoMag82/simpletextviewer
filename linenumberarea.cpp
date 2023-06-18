#include "linenumberarea.h"

LineNumberArea::LineNumberArea(QWidget *editor) : QWidget(editor)
{
    codeEditor = (CodeEditor *) editor;
}

QSize LineNumberArea::sizeHint() const
{
    return QSize(codeEditor->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
    codeEditor->lineNumberAreaPaintEvent(event);
}
