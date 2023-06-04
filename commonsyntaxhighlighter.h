#ifndef COMMONSYNTAXHIGHLIGHTER_H
#define COMMONSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QDebug>

#include "basesyntaxconfig.h"
#include "consts.h"

class CommonSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

    private:
        BaseSyntaxConfig *syntaxConfig = nullptr;
        QStringList listForHiglight;
//        bool insideString = false;
//        bool insideBaseString = false;
        enum HiglightState {normal = -1, insideBaseString, insideString, insideBlockComment};

        HiglightState highlightState = normal;

        QString getKeyword(int pos, QStringList &keyWords, const QString &line);
        QString getCharacters(int pos, QStringList &keyWords, const QString &line);
        int isNumber(int pos, const QString &line);
        bool charIsHex(const QChar &in);

        bool isEndOfWord(const QChar &symbol);
    public:
        CommonSyntaxHighlighter(QTextDocument *paremt = 0);
        void highlightBlock(const QString &str);
        void assignSyntaxConfig(BaseSyntaxConfig *syntaxConfog);


};

#endif // COMMONSYNTAXHIGHLIGHTER_H
