#include "database.h"

bool DataBase::open()
{
    db = QSqlDatabase::addDatabase("QSQLITE","mydb");
    db.setDatabaseName("./DataBase.db");
    if(db.open())
    {
        qDebug() << "Database opened successfully";
        return true;
    }else
    {
        qDebug() << "Database did not opened successfully";
        throw runtime_error("can not open database");
        return false;
    }
}
vector<string> DataBase::select(const QString& queryStr)
{
    open();
    vector<string> result;

    QSqlQuery query(db);
    if (query.exec(queryStr))
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            for (int i = 0; i < record.count(); ++i)
            {
                result.push_back(record.value(i).toString().toStdString());
            }
        }
        qDebug() << "result of select query :";
        for (int i = 0; i < result.size(); ++i) {
            qDebug() << result[i];
        }

    } else {
        // Handle query execution error (e.g., log or display an error message)
        qDebug() << "Query execution failed:" << query.lastError().text();
        throw runtime_error("query execution failed");

    }
    db.close();
    return result;
}
bool DataBase::insert(const QString& queryText) {

    open();

    QSqlQuery query(db);

    if (!query.exec(queryText))
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    // Commit the transaction
    db.commit();
    db.close();

    qDebug() << "Query inserted successfully!";
    return true;
}
bool DataBase::deleteByID(int recordId,const QString& table_name)
{
    open();

    QSqlQuery query;
    query.prepare("DELETE FROM :my_table WHERE id = :recordId");
    query.bindValue(":my_table", table_name);
    query.bindValue(":recordId", recordId);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    // Commit the transaction
    db.commit();
    db.close();

    qDebug() << "Record deleted successfully!";
    return true;
}
bool DataBase::deleteByQuery(const QString& _query)
{
    open();

    QSqlQuery query(db);

    if (!query.exec(_query))
    {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    db.commit();
    db.close();

    qDebug() << "Query deleted successfully!";
    return true;
}
bool DataBase::update(const QString& _query)
{
    QSqlQuery query(db);
    if (!query.exec(_query)) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return false;
    }

    // Commit the transaction
    db.commit();
    db.close();

    qDebug() << "Query executed successfully!";
    return true;
}
