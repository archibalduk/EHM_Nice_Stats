#ifndef SETTINGS_H
#define SETTINGS_H

// Qt headers
class QButtonGroup;
#include <QString>
class QWidget;

/*!
 * \brief The Settings class manages the application settings which are saved to a settings.ini file
 */
class Settings
{
public:
    Settings();
    ~Settings();

    // Factory functions
    /*!
     * \brief Generates a two QRadioButtons linked to a setting
     * \details The QButtonGroup must have an object name set to the field name and settings key
     * \param button_group QButtonGroup for linking to the radio buttons
     * \param option_a_name name text of first option
     * \param option_a_value setting id of the first option
     * \param option_b_name name text of second option
     * \param option_b_value setting id of the second option
     * \param default_value default value if no setting can be found in the settings file
     * \return QWidget containing the QRadioButtons
     */
    QWidget *initRadioButtonSettings(QWidget *parent,
                                     QButtonGroup *button_group,
                                     const QString &option_a_name,
                                     const qint32 option_a_value,
                                     const QString &option_b_name,
                                     const qint32 option_b_value,
                                     const qint32 default_value);

    // Get data
    /*!
     * \brief Returns current folder path for the selected `object_name`
     * \param object_name Object name (this will be used to locate the relevant path setting)
     * \return current folder path
     */
    QString folderPath(const QString &object_name) const;

    // Set data
    /*!
     * \brief Sets the folder path setting for the selected `object_name`
     * \param path Folder path
     * \param object_name Object name (this will be used to locate the relevant path setting)
     */
    void setFolderPath(const QString &path, const QString &object_name);

    // Settings ids
    /*!
     * \brief The ENUM_SETTINGS_IDS enum provides unique ids for various settings
     */
    enum ENUM_SETTINGS_IDS { TIME_FORMAT_DECIMAL, TIME_FORMAT_HH_MM_SS };

private:
    // File i/o
    /*!
     * \brief Loads application settings if available
     */
    void loadSettings();
    /*!
     * \brief Saves application settings
     */
    void saveSettings();

    // File name
    /*!
     * \brief Returns the file name containing the application settings
     * \return file name
     */
    inline QString settingsFileName() const { return QStringLiteral("settings.ini"); }

    // Settings: button groups
    std::vector<QButtonGroup *> button_groups_;

    // Settings: folder paths
    QString folder_path_default_;
    QString folder_path_league_standings_;
    QString folder_path_player_statistics_;

    // Settings: folder path object names
    const QString object_name_default_folder_path_{QStringLiteral("folder_path_default")};
    const QString object_name_league_path_{QStringLiteral("folder_path_league_standings")};
    const QString object_name_player_path_{QStringLiteral("folder_path_player_statistics")};
};

#endif // SETTINGS_H
