#include "mainwindow.h"
#include <QApplication>
#include <database.h>
#include "usersmanagement.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    DataBase* db = DataBase::getInstance();
    UsersManagement::loader();
    return a.exec();
}
