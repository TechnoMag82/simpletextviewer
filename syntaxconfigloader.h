#ifndef SYNTAXCONFIGLOADER_H
#define SYNTAXCONFIGLOADER_H

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#include "consts.h"
#include "basesyntaxconfig.h"

class SyntaxConfigLoader : public BaseSyntaxConfig
{
    private:
        QStringList keywords;
        QString commentSingleLine;
        QStringList commentsBlock;
        QStringList objects;
        QStringList controlCharacters = {"=", "+", "-", "*", "!", ":"};
        QStringList macros;
        QStringList preprocessor;
        QStringList braces = {"{", "}", "<", ">", "[", "]", "(", ")"};

        enum ConfigType {
            KEYWORDS,
            COMMENTSINGLELINE,
            COMMENTSBLOCK,
            OBJECTS,
            CONTROLCHARACTERS,
            MACROS,
            PREPROCESSOR,
            BRACES
        };

        ConfigType getConfigItemType(QString line);
        void readValues(QString line);
        void clearValues();
        void readToList(QStringList &list, QString values);
        QString getRawValue(QString line, uchar keyLength);

    public:
        SyntaxConfigLoader();
        bool loadConfig(QString openFilePath);


        // BaseSyntaxConfig interface
    public:
        QStringList &getKeywords();
        QStringList &getBraces();
        QStringList &getCommentBlock();
        QStringList &getObjects();
        QStringList &getControlCharacters();
        QStringList &getMacros();
        QStringList &getPreprocessor();
        QString &getCommentSingleLine();
};

#endif // SYNTAXCONFIGLOADER_H
