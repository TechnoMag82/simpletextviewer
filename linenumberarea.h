#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include <QPaintEvent>
#include <QSize>

#include "codeeditor.h"

class CodeEditor;

class LineNumberArea : public QWidget
{
    public:
        LineNumberArea(QWidget *editor);// : QWidget(editor), codeEditor(editor) {}

        QSize sizeHint() const override;
//        {
//            return QSize(codeEditor->lineNumberAreaWidth(), 0);
//        }

    protected:
        void paintEvent(QPaintEvent *event) override;
//        {
//            codeEditor->lineNumberAreaPaintEvent(event);
//        }

    private:
        CodeEditor *codeEditor;

};

#endif // LINENUMBERAREA_H
