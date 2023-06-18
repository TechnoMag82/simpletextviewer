#ifndef APPSETTINGSLOADER_H
#define APPSETTINGSLOADER_H

#include <QFile>
#include <QTextStream>
#include <QDir>

#include "consts.h"

class AppSettings {
    public:
        QString colorThemeName = "default";
};

class AppSettingsLoader
{
    public:
        AppSettingsLoader();
        AppSettings loadSettings();
    private:
        AppSettings appSettings;

        void readValues(QString line);
};

#endif // APPSETTINGSLOADER_H
