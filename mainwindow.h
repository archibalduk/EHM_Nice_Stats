#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Application headers
class Settings;

// Qt headers
class QButtonGroup;
class QGroupBox;
class QLineEdit;
class QPushButton;
#include <QMainWindow>
#include <memory>

/*!
 * \brief The MainWindow class is the main user interface of the application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    /*!
     * \brief Close the application
     * \param event QCloseEvent
     */
    void closeEvent(QCloseEvent *event);

private:
    // Attributes
    bool generate_has_been_clicked_{false};

    // Buttons
    QPushButton *generate_button_{nullptr};
    QPushButton *open_player_stats_button_{nullptr};
    QPushButton *open_club_stats_button_{nullptr};
    QPushButton *select_output_file_button_{nullptr};

    // Button groups
    QButtonGroup *time_format_button_group_{nullptr};

    // Fields
    QLineEdit *player_stats_path_{nullptr};
    QLineEdit *club_stats_path_{nullptr};
    QLineEdit *output_file_{nullptr};

    // Settings
    std::unique_ptr<Settings> settings_;

    // Ui functions
    /*!
    * \brief Initialises the file paths group and returns as a group widget
    * \return file paths QGroupWidget
    */
    QGroupBox *initGroupFilePaths();
    /*!
     * \brief Initialises the settings group and returns as a group widget
     * \return settings QGroupWidget
     */
    QGroupBox *initGroupSettings();
    /*!
     * \brief Initialises the user interface
     */
    void initUi();
    /*!
     * \brief Initialises path selection widgets
     * \param title Path title
     * \param path_widget Path text display
     * \param path_selection_button Path selection button
     * \param is_input_path True = input path widget / False = output path widget
     * \return a constructed widget
     */
    QWidget *addPathSelectionUi(const QString &title,
                                QLineEdit *path_widget,
                                QPushButton *path_selection_button,
                                const bool is_input_path);

private slots:
    /*!
     * \brief Generates and output the statistics xlsx spreadsheet
     */
    void generate();
};
#endif // MAINWINDOW_H
