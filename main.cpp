#include "mainwindow.h"

#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    // Application details
    QCoreApplication::setApplicationName("EHM Nice Stats");
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setOrganizationName("EHM The Blue Line");
    QCoreApplication::setOrganizationDomain("ehmtheblueline.com");

    QApplication a(argc, argv);

    // Use Fusion style if dark mode is enabled (Fusion is dark mode compatible)
    QSettings settings(
        "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        QSettings::NativeFormat);
    if (settings.value("AppsUseLightTheme") == 0)
        a.setStyle("fusion");

    MainWindow w;
    w.show();
    return a.exec();
}
