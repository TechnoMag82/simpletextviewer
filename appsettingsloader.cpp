#include "appsettingsloader.h"

AppSettingsLoader::AppSettingsLoader()
{

}

AppSettings AppSettingsLoader::loadSettings()
{
    QString settingsPath = QDir::homePath() + CONFIG_PATH;
    if (QFile::exists(settingsPath)) {
        QFile appSettings(settingsPath);
        if (appSettings.open(QIODevice::ReadOnly | QIODevice::Text) == true)
        {
            QString temp;
            QTextStream configStream(&appSettings);
            configStream.setCodec("UTF-8");
            while (configStream.atEnd() != true)
            {
                temp = configStream.readLine(0);
                if (temp.length() > 0 && temp.at(0) != ';') {
                    readValues(temp);
                }
            }
            appSettings.close();
        }
    }
    return appSettings;
}

void AppSettingsLoader::readValues(QString line)
{
    if (line.startsWith(KEY_THEME_NAME)) {
        int index = line.indexOf('=');
        appSettings.colorThemeName = line.mid(index + 1);
    }
}

