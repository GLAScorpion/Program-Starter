#include "mainwindow.h"
#include <QDir>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    {
        // must give an absolute path to the "theme" folder
        QDir::addSearchPath("icon", QDir::currentPath() + "/theme");
    }
    MainWindow w;
    w.show();
    return a.exec();
}
