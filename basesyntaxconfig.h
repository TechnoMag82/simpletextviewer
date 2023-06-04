#ifndef BASESYNTAXCONFIG_H
#define BASESYNTAXCONFIG_H

#include "QStringList"
#include "QString"

class BaseSyntaxConfig
{
    public:
        BaseSyntaxConfig();
        virtual QStringList & getKeywords() = 0;
        virtual QStringList & getBraces() = 0;
        virtual QString & getCommentSingleLine() = 0;
        virtual QStringList & getCommentBlock() = 0;
        virtual QStringList & getObjects() = 0;
        virtual QStringList & getControlCharacters() =0;
};

#endif // BASESYNTAXCONFIG_H
