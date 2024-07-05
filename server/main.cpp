#include "mainwindow.h"
#include <QApplication>
#include <database.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    DataBase d1;
    d1.open();
    return a.exec();
}
