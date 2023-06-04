#include "syntaxconfigloader.h"

SyntaxConfigLoader::ConfigType SyntaxConfigLoader::getConfigItemType(QString line)
{
    ConfigType configType;
    if (line.startsWith(KEY_KEYWORDS))
        configType = KEYWORDS;
    if (line.startsWith(KEY_COMMENTS_BLOCK))
        configType = COMMENTSBLOCK;
    if (line.startsWith(KEY_COMMENTS_SINGLE_LINE))
        configType = COMMENTSINGLELINE;
    if (line.startsWith(KEY_CONTROL_CHARACTERS))
        configType = CONTROLCHARACTERS;
    if (line.startsWith(KEY_BRACES))
        configType = BRACES;
    if (line.startsWith(KEY_MACROS))
        configType = MACROS;
    if (line.startsWith(KEY_OBJECTS))
        configType = OBJECTS;
    if (line.startsWith(KEY_PREPROCESSOR))
        configType = PREPROCESSOR;
    return configType;
}

void SyntaxConfigLoader::readValues(QString line)
{
    ConfigType configType = getConfigItemType(line);
    switch (configType) {
        case ConfigType::KEYWORDS:
            readToList(keywords, getRawValue(line, KEY_KEYWORDS.length()));
            break;
        case ConfigType::BRACES:
            readToList(braces, getRawValue(line, KEY_BRACES.length()));
            break;
        case ConfigType::COMMENTSBLOCK:
            readToList(commentsBlock, getRawValue(line, KEY_COMMENTS_BLOCK.length()));
            break;
        case ConfigType::COMMENTSINGLELINE:
            commentSingleLine = getRawValue(line, KEY_COMMENTS_SINGLE_LINE.length());
            break;
        case ConfigType::CONTROLCHARACTERS:
            readToList(controlCharacters, getRawValue(line, KEY_CONTROL_CHARACTERS.length()));
            break;
        case ConfigType::MACROS:
            readToList(macros, getRawValue(line, KEY_MACROS.length()));
            break;
        case ConfigType::OBJECTS:
            readToList(objects, getRawValue(line, KEY_OBJECTS.length()));
            break;
        case ConfigType::PREPROCESSOR:
            readToList(preprocessor, getRawValue(line, KEY_PREPROCESSOR.length()));
        break;
    }
}

void SyntaxConfigLoader::clearValues()
{
    keywords.clear();
    commentSingleLine = "";
    commentsBlock.clear();
    objects.clear();
    controlCharacters.clear();
    macros.clear();
    preprocessor.clear();
    braces.clear();
}

void SyntaxConfigLoader::readToList(QStringList &list, QString values)
{
    list.append(values.split(' '));
}

QString SyntaxConfigLoader::getRawValue(QString line, uchar keyLength)
{
    return line.right(line.length() - keyLength - 1);
}

SyntaxConfigLoader::SyntaxConfigLoader()
{

}

void SyntaxConfigLoader::loadConfig(QString openFilePath)
{
    QFileInfo file(openFilePath);

    uchar index = file.fileName().lastIndexOf('.') + 1;
    uchar length = file.fileName().length();
    QString extention = file.fileName().right(length - index);
    QString configPath = SYNTAX_CONFIGS_PATH + BASE_CONFIG_NAME + extention + FILE_CONFIG_EXT;
    qDebug() << "syntax config path: " << configPath;
    QFile syntaxConfig(configPath);
    if (syntaxConfig.open(QIODevice::ReadOnly | QIODevice::Text) == true)
    {
        clearValues();
        QString temp;
        QTextStream configStream(&syntaxConfig);
        configStream.setCodec("UTF-8");
        while (configStream.atEnd() != true)
        {
            temp = configStream.readLine(0);
            readValues(temp);
        }
        syntaxConfig.close();
    }
}

QStringList &SyntaxConfigLoader::getKeywords()
{
    return keywords;
}

QStringList &SyntaxConfigLoader::getBraces()
{
    return braces;
}

QStringList &SyntaxConfigLoader::getCommentBlock()
{
    return commentsBlock;
}

QStringList &SyntaxConfigLoader::getObjects()
{
    return objects;
}

QStringList &SyntaxConfigLoader::getControlCharacters()
{
    return controlCharacters;
}

QString &SyntaxConfigLoader::getCommentSingleLine()
{
    return commentSingleLine;
}
