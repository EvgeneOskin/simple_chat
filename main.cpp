#include <QtGui>
#include <QTimer>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication master_application(argc, argv);
    MainWindow mwdgt;
    mwdgt.show();

    QObject::connect(&mwdgt, SIGNAL(close_MainWindow()), &master_application, SLOT(quit()));

    QTimer::singleShot(1000*60*5, &master_application, SLOT(quit()));

    return master_application.exec();
}
