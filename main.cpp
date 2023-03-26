#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Application details
    QCoreApplication::setApplicationName("EHM Nice Stats");
    QCoreApplication::setApplicationVersion(APP_VERSION);
    QCoreApplication::setOrganizationName("EHM The Blue Line");
    QCoreApplication::setOrganizationDomain("ehmtheblueline.com");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
