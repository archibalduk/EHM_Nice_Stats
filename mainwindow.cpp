#include "mainwindow.h"

// Application headers
#include "settings.h"
#include "stats/manager.h"

// Qt headers
#include <QCoreApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
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

    //setWindowIcon(QIcon("ehm_editor.ico")); // TODO

    initUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUi()
{
    auto central_widget{new QWidget(this)};
    setCentralWidget(central_widget);
    auto layout{new QGridLayout(central_widget)};

    // Input paths
    layout->addWidget(addPathSelectionUi(QStringLiteral("League standings"),
                                         club_stats_path_,
                                         open_club_stats_button_,
                                         true));
    layout->addWidget(addPathSelectionUi(QStringLiteral("Player statistics"),
                                         player_stats_path_,
                                         open_player_stats_button_,
                                         true));

    // Output path
    layout->addWidget(addPathSelectionUi(QStringLiteral("Output file"),
                                         output_file_,
                                         select_output_file_button_,
                                         false));

    // Generate
    generate_button_ = new QPushButton(QStringLiteral("Generate"), this);
    layout->addWidget(generate_button_);
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

    auto label{new QLabel(QString("%1:").arg(title), container)};
    layout->addWidget(label);

    layout->addWidget(path_widget);

    path_selection_button->setText(QStringLiteral("Select"));
    layout->addWidget(path_selection_button);

    if (is_input_path) // Input path widget
        QObject::connect(path_selection_button, &QPushButton::clicked, this, [=]() {
            const auto file_name{
                QFileDialog::getOpenFileName(this,
                                             tr("Select %1 input file")
                                                 .arg(path_selection_button->text().toLower()),
                                             settings_->folderPath(),
                                             tr("Plain text (*.csv *.txt)"))};

            if (file_name.isEmpty())
                return;

            path_widget->setText(file_name);
            settings_->setFolderPath(file_name);
        });
    else // Output path widget
        QObject::connect(path_selection_button, &QPushButton::clicked, this, [=]() {
            const auto file_name{QFileDialog::getSaveFileName(
                this,
                tr("Select %1").arg(path_selection_button->text().toLower()),
                QString("%1/%2").arg(settings_->folderPath(), QStringLiteral("nice_stats.xlsx")),
                tr("Excel spreadsheet(*.xlsx)"))};

            if (file_name.isEmpty())
                return;

            path_widget->setText(file_name);
            settings_->setFolderPath(file_name);
        });

    return container;
}

void MainWindow::generate()
{
    // Abort if any file paths are blank
    if (player_stats_path_->text().isEmpty() || club_stats_path_->text().isEmpty()
        || output_file_->text().isEmpty())
        return;

    stats::Manager nice_stats(club_stats_path_->text(),
                              player_stats_path_->text(),
                              output_file_->text());
    if (nice_stats.generate())
        QMessageBox::information(this,
                                 QStringLiteral("Export complete"),
                                 QStringLiteral(
                                     "The nice statistics have been successfully saved.\n\nNice!"));
}
