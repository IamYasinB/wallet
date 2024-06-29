#include "database.h"


bool DataBase::open()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./DataBase.db");
    if(db.open())
    {
        qDebug() << "Database opened successfully";
        return true;
    }else
    {
        qDebug() << "Database did not opened successfully";
        return false;
    }
}
