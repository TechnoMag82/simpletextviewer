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
        QColor background;
        QColor baseTextColor;
        QColor keyword;
        QColor commentSingleLine;
        QColor commentBlock;
        QColor object;
        QColor macros;
        QColor braces;
        QColor controlCharacter;
        QColor strings;
        QColor chars;
        QColor numbers;

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
};

#endif // COLORTHEMELOADER_H
