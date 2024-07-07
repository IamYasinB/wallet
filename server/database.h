#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QSqlError>
#include <vector>
#include <string>
#include <exception>
//it must be in singelton Patern   TODO : make it singelton
using namespace std;

class DataBase
{
private:
    QSqlDatabase db;
    bool open();

public:
    vector<string> select(const QString& queryStr);
    bool insert(const QString& queryText);
    bool deleteByID(int recordId,const QString& table_name);
    bool deleteByQuery(const QString& _query);
    bool update(const QString& _query);

};

#endif // DATABASE_H
