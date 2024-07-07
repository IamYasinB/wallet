#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <vector>
#include <QObject>
class transaction
{
private:
    transaction();
public:
    std :: vector<std :: vector<std :: string>> Queue; //saf entezar moamelat
    int buy();
    int sell();
    int exchange();
    static int Analayzer(QString Request);
    int Add_In_Queue();
};

#endif // TRANSACTION_H
