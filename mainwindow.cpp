#include "mainwindow.h"

// Application headers
#include "settings.h"
#include "stats/ice_time.h"
#include "stats/stats_manager.h"

// Qt headers
#include <QButtonGroup>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , open_player_stats_button_(new QPushButton(this))
    , open_club_stats_button_(new QPushButton(this))
    , select_output_file_button_(new QPushButton(this))
    , player_stats_path_(new QLineEdit(this))
    , club_stats_path_(new QLineEdit(this))
    , output_file_(new QLineEdit(this))
    , settings_(std::make_unique<Settings>())
{
    setWindowTitle(QString("%1 v%2").arg(QCoreApplication::applicationName(),
                                         QCoreApplication::applicationVersion()));
    setMinimumWidth(640);
    initUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (generate_has_been_clicked_) {
        event->accept();
        return;
    }

    if (QMessageBox::Yes
        == QMessageBox::question(
            this,
            tr("Exit"),
            QString("You have not generated any nice stats.\n\nAre you sure you wish to exit?"),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No))
        event->accept();
    else
        event->ignore();
}

QGroupBox *MainWindow::initGroupFilePaths()
{
    auto group{new QGroupBox(QStringLiteral("File paths"), this)};
    auto layout{new QGridLayout(group)};

    // Input paths
    layout->addWidget(addPathSelectionUi(QStringLiteral("League standings"),
                                         club_stats_path_,
                                         open_club_stats_button_,
                                         true));
    club_stats_path_->setText(settings_->folderPath(open_club_stats_button_->objectName()));

    layout->addWidget(addPathSelectionUi(QStringLiteral("Player statistics"),
                                         player_stats_path_,
                                         open_player_stats_button_,
                                         true));
    player_stats_path_->setText(settings_->folderPath(open_player_stats_button_->objectName()));

    // Output path
    layout->addWidget(addPathSelectionUi(QStringLiteral("Save as"),
                                         output_file_,
                                         select_output_file_button_,
                                         false));

    return group;
}

QGroupBox *MainWindow::initGroupSettings()
{
    auto group{new QGroupBox(QStringLiteral("Settings"), this)};
    auto layout{new QGridLayout(group)};

    // Time format
    time_format_button_group_ = new QButtonGroup(this);
    time_format_button_group_->setObjectName(QStringLiteral("Time format"));
    auto time_format_settings{settings_->initRadioButtonSettings(this,
                                                                 time_format_button_group_,
                                                                 QStringLiteral("hh:mm:ss"),
                                                                 Settings::TIME_FORMAT_HH_MM_SS,
                                                                 QStringLiteral("Decimal"),
                                                                 Settings::TIME_FORMAT_DECIMAL,
                                                                 Settings::TIME_FORMAT_HH_MM_SS)};
    layout->addWidget(time_format_settings);

    return group;
}

void MainWindow::initUi()
{
    auto central_widget{new QWidget(this)};
    setCentralWidget(central_widget);
    auto layout{new QGridLayout(central_widget)};

    // Widget groups
    layout->addWidget(initGroupFilePaths(), 0, 0, 1, 2);
    layout->addWidget(initGroupSettings(), 1, 0);

    // Generate button
    generate_button_ = new QPushButton(QStringLiteral("Generate"), this);
    layout->addWidget(generate_button_, 1, 1, Qt::AlignBottom);

    QObject::connect(generate_button_, &QPushButton::clicked, this, &MainWindow::generate);
}

QWidget *MainWindow::addPathSelectionUi(const QString &title,
                                        QLineEdit *path_widget,
                                        QPushButton *path_selection_button,
                                        const bool is_input_path)
{
    auto container{new QWidget(this)};
    container->setContentsMargins(0, 0, 0, 0);
    auto layout{new QHBoxLayout(container)};
    layout->setContentsMargins(0, 0, 0, 0);

    auto label{new QLabel(QString("%1:").arg(title), container)};
    label->setFixedWidth(100);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(label);

    layout->addWidget(path_widget);

    path_selection_button->setText(QStringLiteral("Select"));
    path_selection_button->setObjectName(title.toLower().replace(" ", "_", Qt::CaseInsensitive));
    layout->addWidget(path_selection_button);

    if (is_input_path) // Input path widget
        QObject::connect(path_selection_button, &QPushButton::clicked, this, [=]() {
            const auto file_name{QFileDialog::getOpenFileName(
                this,
                tr("Select %1 input file").arg(path_selection_button->text().toLower()),
                settings_->folderPath(path_selection_button->objectName()),
                tr("Plain text (*.csv *.txt)"))};

            if (file_name.isEmpty())
                return;

            path_widget->setText(file_name);
            settings_->setFolderPath(file_name, path_selection_button->objectName());
        });
    else // Output path widget
        QObject::connect(path_selection_button, &QPushButton::clicked, this, [=]() {
            const auto file_name{QFileDialog::getSaveFileName(
                this,
                tr("Select %1").arg(path_selection_button->text().toLower()),
                QString("%1/%2").arg(settings_->folderPath(path_selection_button->objectName()),
                                     QStringLiteral("nice_stats.xlsx")),
                tr("Excel spreadsheet(*.xlsx)"))};

            if (file_name.isEmpty())
                return;

            path_widget->setText(file_name);
            settings_->setFolderPath(file_name, path_selection_button->objectName());
        });

    return container;
}

void MainWindow::generate()
{
    // Abort if any file paths are blank
    if (player_stats_path_->text().isEmpty() || club_stats_path_->text().isEmpty()
        || output_file_->text().isEmpty())
        return;

    // Apply any user settings
    stats::IceTime::setTimeFormat(time_format_button_group_->checkedId());

    stats::StatsManager nice_stats(club_stats_path_->text(),
                                   player_stats_path_->text(),
                                   output_file_->text());
    if (nice_stats.generate())
        QMessageBox::information(this,
                                 QStringLiteral("Export complete"),
                                 QStringLiteral(
                                     "The nice statistics have been successfully saved.\n\n"
                                     "Clubs processed: %L1\n\n"
                                     "Skaters processed: %L2")
                                     .arg(nice_stats.clubCount())
                                     .arg(nice_stats.skaterCount()));
    else
        QMessageBox::information(this,
                                 QStringLiteral("Error"),
                                 QStringLiteral("Oh dear. Something went wrong..."));

    generate_has_been_clicked_ = true;
}
