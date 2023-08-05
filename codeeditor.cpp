#include "codeeditor.h"

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    rx.setPattern("^([A-Fa-f0-9]{8}|[A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$");
    setMouseTracking(true);
    lineNumberArea = new LineNumberArea(this);

    colorLabel = new ColorLabel(this);
    colorLabel->setVisible(false);

    setFont(QFont("Consolas", 16));
    setWordWrapMode(QTextOption::NoWrap);
    setReadOnly(true);

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

CodeEditor::~CodeEditor()
{
    delete lineNumberArea;
    delete colorLabel;
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), *backgroundColor);
    painter.setPen(*lineNumberColor);
    painter.drawLine(event->rect().topRight(), event->rect().bottomRight());

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(*lineNumberColor);
            painter.drawText(0, top, lineNumberArea->width() - 5, fontMetrics().height(),
                                Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space + 10;
}

void CodeEditor::setLineNumberColor(QColor &color)
{
    lineNumberColor = &color;
}

void CodeEditor::setCurrentLineColor(QColor &color)
{
    currentLineColor = &color;
}

void CodeEditor::setBackgroundColor(QColor &color)
{
    backgroundColor = &color;
}

void CodeEditor::setTextColor(QColor &color)
{
    textColor = &color;
}

void CodeEditor::applyColorTheme()
{
    QPalette p = palette();
    p.setColor(QPalette::Base, *backgroundColor);
    p.setColor(QPalette::Text, *textColor);
    setPalette(p);
}

void CodeEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    QTextCursor cursor = cursorForPosition(mouseEvent->pos());
    cursor.select(QTextCursor::WordUnderCursor);
    QString strWord = cursor.selectedText();
    stringPosition = cursor.block().text().indexOf(strWord);
    if (!strWord.isEmpty() &&
            cursor.block().text().at(stringPosition - 1) == '#' &&
            rx.exactMatch(strWord)) {
        colorLabel->setColor(QColor('#' + strWord));
        colorLabel->setGeometry(mouseEvent->pos().x() - 16, mouseEvent->pos().y() - 16, 50, 50);
        colorLabel->setVisible(true);
    } else {
        colorLabel->setVisible(false);
    }
    QPlainTextEdit::mouseMoveEvent(mouseEvent);
}

void CodeEditor::updateLineNumberAreaWidth(int newBlockCount)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    QTextEdit::ExtraSelection selection;

    if (currentLineColor != nullptr) {
        QColor lineColor = QColor(*currentLineColor);
        selection.format.setBackground(lineColor);
    }
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);

    setExtraSelections(extraSelections);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}
