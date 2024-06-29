#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>

//it must be in singelton Patern   TODO : make it singelton
using namespace std;

class DataBase
{
private:
    QSqlDatabase db;
public:
    bool open();
};

#endif // DATABASE_H
