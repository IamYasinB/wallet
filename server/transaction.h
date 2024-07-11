    #ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <QObject>
#include <vector>
#include <QObject>
#include <string>
#include "walletmanagement.h"

using namespace std;
class transaction : public QObject
{
    Q_OBJECT
public:
    bool is_QUEUE_EMPTY = true;
    transaction();    
    std :: vector<std :: vector<std :: string>> Queue; //saf entezar moamelat
    int buy(int walletIP,string coin,double amount);
    /*
     * if successful return 1
     * if coin name is wrong return 2
     * if could not withdraw USD return 3
     * if could not deposit coin return 4
    */
    int sell();
    int exchange();
    int Analayzer(std :: string username , std :: string operation, std :: string balance ,std :: string coin_requested,double current_price,double amount_requested);
private slots:
    int Add_In_Queue();
signals:
    void vector_not_empty();
};

#endif // TRANSACTION_H
