#ifndef SETTINGS_H
#define SETTINGS_H

// Qt headers
#include <QString>

/*!
 * \brief The Settings class manages the application settings which are saved to a settings.ini file
 */
class Settings
{
public:
    Settings();
    ~Settings();

    /*!
     * \brief Get current folder path
     * \return current folder path
     */
    inline QString folderPath() const { return folder_path_; }

    /*!
     * \brief Sets the folder path setting
     * \param path Folder path
     */
    void setFolderPath(const QString &path);

private:
    // File i/o
    /*!
     * \brief Load application settings if available
     */
    void loadSettings();
    /*!
     * \brief Save application settings
     */
    void saveSettings();

    // File name
    inline QString settingsFileName() const { return QStringLiteral("settings.ini"); }

    // Settings
    QString folder_path_;
};

#endif // SETTINGS_H
