#include "settings.h"

// Qt headers
#include <QButtonGroup>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QSettings>
#include <QWidget>

Settings::Settings()
{
    loadSettings();
}

Settings::~Settings()
{
    saveSettings();
}

QWidget *Settings::initRadioButtonSettings(QWidget *parent,
                                           QButtonGroup *button_group,
                                           const QString &option_a_name,
                                           const qint32 option_a_value,
                                           const QString &option_b_name,
                                           const qint32 option_b_value,
                                           const qint32 default_value)
{
    auto container{new QWidget(parent)};
    container->setContentsMargins(0, 0, 0, 0);
    auto layout{new QHBoxLayout(container)};
    layout->setContentsMargins(0, 0, 0, 0);

    // Label
    auto label{new QLabel(QString("%1:").arg(button_group->objectName()))};
    layout->addWidget(label);

    // Option a
    auto button_a{new QRadioButton(option_a_name, container)};
    button_group->addButton(button_a, option_a_value);
    layout->addWidget(button_a);

    // Option b
    auto button_b{new QRadioButton(option_b_name, container)};
    button_group->addButton(button_b, option_b_value);
    layout->addWidget(button_b);

    QSettings settings(settingsFileName(), QSettings::IniFormat);
    auto current_setting_value{
        settings
            .value(button_group->objectName().toLower().replace(" ", "_", Qt::CaseInsensitive),
                   default_value)
            .toInt()};

    if (option_a_value == current_setting_value)
        button_a->setChecked(true);
    else
        button_b->setChecked(true);

    // Add to the button group vector
    button_groups_.push_back(button_group);

    return container;
}

/* ================== */
/*      File i/o      */
/* ================== */

void Settings::loadSettings()
{
    QSettings settings(settingsFileName(), QSettings::IniFormat);
    folder_path_default_ = settings.value(object_name_default_folder_path_, QStringLiteral("C:\\"))
                               .toString();
    folder_path_league_standings_ = settings.value(object_name_league_path_, folder_path_default_)
                                        .toString();
    folder_path_player_statistics_ = settings.value(object_name_player_path_, folder_path_default_)
                                         .toString();
}

void Settings::saveSettings()
{
    QSettings settings(settingsFileName(), QSettings::IniFormat);

    // Button groups
    for (const auto &itr : button_groups_)
        settings.setValue(itr->objectName().toLower().replace(" ", "_", Qt::CaseInsensitive),
                          itr->checkedId());

    // File paths
    settings.setValue(object_name_default_folder_path_, folder_path_default_);
    settings.setValue(object_name_league_path_, folder_path_league_standings_);
    settings.setValue(object_name_player_path_, folder_path_player_statistics_);

    settings.sync();
}

/* ================== */
/*      Get Data      */
/* ================== */

QString Settings::folderPath(const QString &object_name) const
{
    if (object_name_league_path_.contains(object_name, Qt::CaseInsensitive))
        return folder_path_league_standings_;

    if (object_name_player_path_.contains(object_name, Qt::CaseInsensitive))
        return folder_path_player_statistics_;

    return folder_path_default_;
}

/* ================== */
/*      Set Data      */
/* ================== */

void Settings::setFolderPath(const QString &path, const QString &object_name)
{
    if (path.isEmpty())
        return;

    QFileInfo fi(path);

    if (object_name_league_path_.contains(object_name, Qt::CaseInsensitive)) {
        folder_path_league_standings_ = path;
        return;
    }

    if (object_name_player_path_.contains(object_name, Qt::CaseInsensitive)) {
        folder_path_player_statistics_ = path;
        return;
    }

    folder_path_default_ = fi.path();
}
