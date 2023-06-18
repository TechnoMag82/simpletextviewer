#include "colorthemeloader.h"

QColor & ColorThemeLoader::getKeywordColor()
{
    return keyword;
}

QColor & ColorThemeLoader::getCommentSingleLineColor()
{
    return commentSingleLine;
}

QColor & ColorThemeLoader::getCommentBlockColor()
{
    return commentBlock;
}

QColor & ColorThemeLoader::getObjectColor()
{
    return object;
}

QColor & ColorThemeLoader::getMacrosColor()
{
    return macros;
}

QColor & ColorThemeLoader::getBracesColor()
{
    return braces;
}

QColor & ColorThemeLoader::getControlCharacterColor()
{
    return controlCharacter;
}

QColor & ColorThemeLoader::getStringsColor()
{
    return strings;
}

QColor & ColorThemeLoader::getCharsColor()
{
    return chars;
}

QColor & ColorThemeLoader::getBackgroundColor()
{
    return background;
}

QColor & ColorThemeLoader::getBaseTextColor()
{
    return baseTextColor;
}

QColor &ColorThemeLoader::getNumbersColor()
{
    return numbers;
}

QColor &ColorThemeLoader::getCurrentLineColor()
{
    return currentLine;
}

QColor &ColorThemeLoader::getLineNumberColor()
{
    return lineNumber;
}

void ColorThemeLoader::readValues(QString line)
{
    QString color = line.right(7);
    if (line.startsWith(KEY_BRACES)) {
        braces = parseColor(color);
    }
    if (line.startsWith(KEY_KEYWORDS)) {
        keyword = parseColor(color);
    }
    if (line.startsWith(KEY_COMMENTS)) {
        commentBlock = parseColor(color);
        commentSingleLine = commentBlock;
    }
    if (line.startsWith(KEY_CONTROL_CHARACTERS)) {
        controlCharacter = parseColor(color);
    }
    if (line.startsWith(KEY_OBJECTS)) {
        object = parseColor(color);
    }
    if (line.startsWith(KEY_MACROS)) {
        macros = parseColor(color);
    }
    if (line.startsWith(KEY_STRINGS)) {
        strings = parseColor(color);
    }
    if (line.startsWith(KEY_CHARS)) {
        chars = parseColor(color);
    }
    if (line.startsWith(KEY_BACKGROUND)) {
        background = parseColor(color);
    }
    if (line.startsWith(KEY_BASE_TEXT_COLOR)) {
        baseTextColor = parseColor(color);
    }
    if (line.startsWith(KEY_NUMBERS)) {
        numbers = parseColor(color);
    }
    if (line.startsWith(KEY_CURRENT_LINE)) {
        currentLine = parseColor(color);
    }
    if (line.startsWith(KEY_LINE_NUMBER)) {
        lineNumber = parseColor(color);
    }
}

QColor ColorThemeLoader::parseColor(QString color)
{
    bool ok;
    int r, g, b;
    QString strColorPart = color.mid(1, 2);
    r = strColorPart.toInt(&ok, 16);
    strColorPart = color.mid(3, 2);
    g = strColorPart.toInt(&ok, 16);
    strColorPart = color.mid(5, 2);
    b = strColorPart.toInt(&ok, 16);
    return QColor(r, g, b);
}

ColorThemeLoader::ColorThemeLoader()
{

}

void ColorThemeLoader::loadTheme(QString themeName)
{
    QString configPath = THEMES_PATH + themeName + FILE_THEME_EXT;
    QFile syntaxConfig(configPath);
    if (syntaxConfig.open(QIODevice::ReadOnly | QIODevice::Text) == true)
    {
        QString temp;
        QTextStream configStream(&syntaxConfig);
        configStream.setCodec("UTF-8");
        while (configStream.atEnd() != true)
        {
            temp = configStream.readLine(0);
            if (temp.length() > 0 && temp.at(0) != ';') {
                readValues(temp);
            }
        }
        syntaxConfig.close();
    }
}
