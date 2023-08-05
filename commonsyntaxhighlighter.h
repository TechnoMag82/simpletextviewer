#ifndef COMMONSYNTAXHIGHLIGHTER_H
#define COMMONSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QDebug>
#include <QRegExp>

#include "basesyntaxconfig.h"
#include "colorthemeloader.h"
#include "consts.h"

class CommonSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

    private:
        BaseSyntaxConfig *syntaxConfig = nullptr;
        ColorThemeLoader *colorTheme = nullptr;
        QStringList listForHiglight;
        QRegExp rx;
        enum HiglightState {normal = -1, insideBaseString, insideString, insideBlockComment};

        HiglightState highlightState = normal;

        QString getKeyword(int pos, QStringList &keyWords, const QString &line);
        QString getCharacters(int pos, QStringList &keyWords, const QString &line);
        int isNumber(int pos, const QString &line);

        bool isEndOfWord(const QChar &symbol);
    public:
        CommonSyntaxHighlighter(QTextDocument *paremt = 0);
        void highlightBlock(const QString &str);
        void assignSyntaxConfig(BaseSyntaxConfig *syntaxConfog);
        void assignColorTheme(ColorThemeLoader *colorTheme);

};

#endif // COMMONSYNTAXHIGHLIGHTER_H
