#include "commonsyntaxhighlighter.h"

CommonSyntaxHighlighter::CommonSyntaxHighlighter(QTextDocument* parent)
    : QSyntaxHighlighter(parent)
{

}

void CommonSyntaxHighlighter::highlightBlock(const QString &str)
{
    if (syntaxConfig == nullptr || colorTheme == nullptr)
        return;
    int strLength = str.length();
    for (int i = 0; i < strLength; i++) {

        // skip escaped characters

        if (highlightState == insideBaseString || highlightState == insideString) {
            if ((str.mid(i, 2) == "\\\"") || (str.mid(i, 2) == "\\\'")) {
                setFormat(i, 2, colorTheme->getStringsColor());
                i+=2;
                continue;
            }
        }

        // find end of block

        if (highlightState == insideBaseString) {
            if (str.at(i) == '\"') {
                setFormat(i, 1, colorTheme->getStringsColor());
                highlightState = normal;
                continue;
            } else {
                setFormat(i, 1, colorTheme->getStringsColor());
                continue;
            }
        } else if (highlightState == insideString) {
            if (str.at(i) == '\'') {
                setFormat(i, 1, colorTheme->getCharsColor());
                highlightState = normal;
                continue;
            } else {
                setFormat(i, 1, colorTheme->getCharsColor());
                continue;
            }
        } else if (highlightState == insideBlockComment) {
            if (syntaxConfig->getCommentBlock().size() > 0 &&
                    str.mid(i, syntaxConfig->getCommentBlock().at(1).size()) == syntaxConfig->getCommentBlock().at(1)) {
                setFormat(i, syntaxConfig->getCommentBlock().at(1).size(), colorTheme->getCommentBlockColor());
                highlightState = normal;
                continue;
            } else {
                setFormat(i, 1, colorTheme->getCommentBlockColor());
                continue;
            }
        }

        // find start of block or keywords

        if (str.mid(i, 2) == syntaxConfig->getCommentSingleLine()) {
            setFormat(i, strLength - i, colorTheme->getCommentSingleLineColor());
            break;
        } else if (syntaxConfig->getCommentBlock().size() > 0 &&
                   str.mid(i, syntaxConfig->getCommentBlock().at(0).size()) == syntaxConfig->getCommentBlock().at(0)) {
            setFormat(i, syntaxConfig->getCommentBlock().at(0).size(), colorTheme->getCommentSingleLineColor());
            highlightState = insideBlockComment;
            continue;
        } else if (str.at(i) == '\"') {
            setFormat(i, 1, colorTheme->getStringsColor());
            highlightState = insideBaseString;
            continue;
        } else if (str.at(i) == '\'') {
            setFormat(i, 1, colorTheme->getCharsColor());
            highlightState = insideString;
            continue;
        } else {
            QString strKeyword = getKeyword(i, syntaxConfig->getKeywords(), str);
            if (!strKeyword.isEmpty()) {
                setFormat(i, strKeyword.length(), colorTheme->getKeywordColor());
                i+=strKeyword.length() - 1;
            }
            strKeyword = getKeyword(i, syntaxConfig->getMacros(), str);
            if (!strKeyword.isEmpty()) {
                setFormat(i, strKeyword.length(), colorTheme->getMacrosColor());
                i+=strKeyword.length() - 1;
            }
            strKeyword = getKeyword(i, syntaxConfig->getPreprocessor(), str);
            if (!strKeyword.isEmpty()) {
                setFormat(i, strKeyword.length(), colorTheme->getPreprocessorColor());
                i+=strKeyword.length() - 1;
            }
            strKeyword = getKeyword(i, syntaxConfig->getObjects(), str);
            if (!strKeyword.isEmpty()) {
                setFormat(i, strKeyword.length(), colorTheme->getObjectColor());
                i+=strKeyword.length() - 1;
            }
            strKeyword = getCharacters(i, syntaxConfig->getControlCharacters(), str);
            if (!strKeyword.isEmpty()) {
                setFormat(i, strKeyword.length(), colorTheme->getControlCharacterColor());
                i+=strKeyword.length() - 1;
            }

            // find number
            int isNumber1 = isNumber(i, str);
            if (isNumber1 > 0) {
                setFormat(i, isNumber1, colorTheme->getNumbersColor());
                i+=isNumber1;
            } else {
                i+=abs(isNumber1);
            }

            // find braces
            strKeyword = getCharacters(i, syntaxConfig->getBraces(), str);
            if (!strKeyword.isEmpty()) {
                setFormat(i, strKeyword.length(), colorTheme->getBracesColor());
                i+=strKeyword.length() - 1;
            }

        }
    }
}

void CommonSyntaxHighlighter::assignSyntaxConfig(BaseSyntaxConfig *syntaxConfog)
{
    this->syntaxConfig = syntaxConfog;
}

void CommonSyntaxHighlighter::assignColorTheme(ColorThemeLoader *colorTheme)
{
    this->colorTheme = colorTheme;
}


QString CommonSyntaxHighlighter::getKeyword(int pos, QStringList &keyWords, const QString &line)
{
    QString strTemp = "";

    foreach (QString keyWord, keyWords) {
        if (pos == 0 && pos + keyWord.size() <= line.size()) {
            if ((!line.at(pos + keyWord.size()).isLetter()) &&
                    line.mid(pos, keyWord.size()) == keyWord
            ) {
                strTemp = keyWord;
                break;
            }
        } else if (pos > 0 && pos + keyWord.size() == line.size()) {
            if ((!line.at(pos - 1).isLetter() &&
                    line.mid(pos, keyWord.size()) == keyWord
                    )
            ) {
                strTemp = keyWord;
                break;
            }

        } else if (pos > 0 && pos + keyWord.size() < line.size()) {
            if (line.mid(pos, keyWord.size()) == keyWord
                    &&
                    (!line.at(pos-1).isLetter() && !line.at(pos + keyWord.size()).isLetter())
            ) {
                strTemp = keyWord;
                break;
            }
        }
    }
    return strTemp;
}

QString CommonSyntaxHighlighter::getCharacters(int pos, QStringList &keyWords, const QString &line)
{
    QString strTemp = "";

    foreach (QString keyWord, keyWords) {
        if (line.mid(pos, keyWord.size()) == keyWord) {
            strTemp = keyWord;
            break;
        }
    }
    return strTemp;
}

bool CommonSyntaxHighlighter::isEndOfWord(const QChar &symbol)
{
    return symbol == '<' ||
            symbol == '>' ||
            symbol == '\'' ||
            symbol == '\"' ||
            symbol == ' ' ||
            symbol == '\\' ||
            symbol == '[' ||
            symbol == ']' ||
            symbol == '(' ||
            symbol == ')' ||
            symbol == '{' ||
            symbol == '}' ||
            symbol == '=' ||
            symbol == '$' ||
            symbol == '#' ||
            symbol == ';' ||
            symbol == ':' ||
            symbol == ',' ||
            symbol == '/' ||
            symbol == '!' ||
            symbol == '?' ||
            symbol == '*' ||
            symbol == '.' ||
            symbol == '&' ||
            symbol == '|' ||
            symbol == '%' ||
            symbol.isSymbol();
}

int CommonSyntaxHighlighter::isNumber(int pos, const QString &line)
{
   bool numberIsBegin = false;
   int strTemp = 0;
   if (pos == 0) {
       // case completed
        for (int i = pos; i < line.length(); i++) {
            if (line.mid(pos, 2) == "0x") {
                for (int k = i + 2; k < line.length(); k++) {
                    if (charIsHex(line.at(k)) || line.at(k).isNumber()) {
                        strTemp++;
                    } else
                        return strTemp+2;
                }
                return strTemp+2;
            }

            if (numberIsBegin && line.at(i).isLetter()) {
                return strTemp;
            } else if (line.at(i).isNumber()) {
                numberIsBegin = true;
                strTemp++;
            } else if (numberIsBegin && (line.at(i) == '.' || line.at(i) == ',')) {
                strTemp++;
            } else {
                return strTemp;
            }
        }
   } else if (pos > 0 && pos < line.size()) {
       bool isIdentifier = false;
       for (int i = pos; i < line.length(); i++) {

           // hex number
           if (line.mid(pos, 2) == "0x") {
               for (int k = i + 2; k < line.length(); k++) {
                   if (charIsHex(line.at(k)) || line.at(k).isNumber()) {
                       strTemp++;
                   } else
                       return strTemp + 2;
               }
               return strTemp + 2;
           }

           // is identifier
           if (line.at(i - 1).isLetter() && line.at(i).isNumber()) {
               int noNumberLength = 0;
               for (int k = i; k < line.length(); k++) {
                   if (!isEndOfWord(line.at(k))) {
                       noNumberLength--;
                   } else {
                       return noNumberLength + 1;
                   }
               }
           }

           if (numberIsBegin && line.at(i).isLetter()) {
               isIdentifier = false;
               return strTemp;
           } else if (!line.at(i-1).isLetter() && line.at(i).isNumber()) {
               numberIsBegin = true;
               strTemp++;
           } else if (numberIsBegin && line.at(i).isNumber()) {
               strTemp++;
           } else if (numberIsBegin && (line.at(i) == '.' || line.at(i) == ',')) {
               strTemp++;
           } else {
               isIdentifier = false;
               return strTemp;
           }
       }
   }
   return strTemp;
}

bool CommonSyntaxHighlighter::charIsHex(const QChar &in)
{
    for (int i = 0; i <= sizeof(hex1); i++) {
        if (hex1[i] == in) {
            return true;
        }
    }
    return false;
}
