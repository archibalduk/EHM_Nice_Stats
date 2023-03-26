#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Application headers
class Settings;

// Qt headers
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

private:
    // Buttons
    QPushButton *generate_button_{nullptr};
    QPushButton *open_player_stats_button_{nullptr};
    QPushButton *open_club_stats_button_{nullptr};
    QPushButton *select_output_file_button_{nullptr};

    // Fields
    QLineEdit *player_stats_path_{nullptr};
    QLineEdit *club_stats_path_{nullptr};
    QLineEdit *output_file_{nullptr};

    // Settings
    std::unique_ptr<Settings> settings_;

    // Ui functions
    /*!
     * \brief Initialise the user interface
     */
    void initUi();
    /*!
     * \brief Initialise path selection widgets
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
     * \brief Generate and output the statistics
     */
    void generate();
};
#endif // MAINWINDOW_H
