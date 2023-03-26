#include "settings.h"

// Qt headers
#include <QFileInfo>
#include <QSettings>
#include <QString>

Settings::Settings()
{
    loadSettings();
}

Settings::~Settings()
{
    saveSettings();
}

void Settings::setFolderPath(const QString &path)
{
    if (path.isEmpty())
        return;

    QFileInfo fi(path);
    folder_path_ = fi.path();
}

void Settings::loadSettings()
{
    QSettings settings(settingsFileName(), QSettings::IniFormat);
    folder_path_ = settings.value(QStringLiteral("folder_path"), QStringLiteral("C:\\")).toString();
}

void Settings::saveSettings()
{
    QSettings settings(settingsFileName(), QSettings::IniFormat);
    settings.setValue(QStringLiteral("folder_path"), folder_path_);
    settings.sync();
}
