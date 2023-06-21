#ifndef COLORTHEMELOADER_H
#define COLORTHEMELOADER_H

#include <QColor>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "consts.h"

class ColorThemeLoader
{
    private:
        QColor background = Qt::white;
        QColor baseTextColor = Qt::black;
        QColor currentLine = Qt::lightGray;
        QColor lineNumber = Qt::black;
        QColor keyword = Qt::blue;
        QColor commentSingleLine = Qt::gray;
        QColor commentBlock = Qt::gray;
        QColor object = Qt::cyan;
        QColor macros = Qt::darkGray;
        QColor braces = Qt::darkMagenta;
        QColor preprocessor = Qt::darkCyan;
        QColor controlCharacter = Qt::magenta;
        QColor strings = Qt::green;
        QColor chars = Qt::green;
        QColor numbers = Qt::red;

        void readValues(QString line);
        QColor parseColor(QString color);

    public:
        ColorThemeLoader();
        void loadTheme(QString themeName);


        QColor & getKeywordColor();
        QColor & getCommentSingleLineColor();
        QColor & getCommentBlockColor();
        QColor & getObjectColor();
        QColor & getMacrosColor();
        QColor & getBracesColor();
        QColor & getControlCharacterColor();
        QColor & getStringsColor();
        QColor & getCharsColor();
        QColor & getBackgroundColor();
        QColor & getBaseTextColor();
        QColor & getNumbersColor();
        QColor & getCurrentLineColor();
        QColor & getLineNumberColor();
        QColor & getPreprocessorColor();
};

#endif // COLORTHEMELOADER_H
