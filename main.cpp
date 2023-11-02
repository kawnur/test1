#include <QApplication>

#include "customwidgets.h"
#include "mainwindow.h"
#include "manager.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow* mainWindow = MainWindow::instance();

    mainWindow->show();
    return a.exec();
}
