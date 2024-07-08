    #ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <QObject>
#include <vector>
#include <QObject>
class transaction : public QObject
{
    Q_OBJECT
public:
    bool is_QUEUE_EMPTY = true;
    transaction();    
    std :: vector<std :: vector<std :: string>> Queue; //saf entezar moamelat
    int buy();
    int sell();
    int exchange();
    int Analayzer(std :: string username , std :: string operation, std :: string balance ,std :: string coin_requested,double current_price,double amount_requested);
private slots:
    int Add_In_Queue();
signals:
    void vector_not_empty();
};

#endif // TRANSACTION_H
