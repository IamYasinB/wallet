#include "mainwindow.h"
#include <QApplication>
#include <database.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    DataBase* db = DataBase::getInstance();
    db->insert("INSERT INTO Accounts (email,password,username,level,name,phone,address) VALUES ('yasinbeheshti13@gmail.com','1234','yasinb','1','yasin','09921184825','yasuj');");
    return a.exec();
}
