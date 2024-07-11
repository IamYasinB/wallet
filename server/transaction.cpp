#include "transaction.h"
#include "coin.h"
using namespace std;
transaction :: transaction(double _BTC_price,double _ETH_price,double _USDT_price,double _BNB_price,double _SOL_price){
    connect(this,SIGNAL(vector_not_empty()),this,SLOT(Add_In_Queue()));
    BTC_price = _BTC_price;
    ETH_price = _ETH_price;
    USDT_price = _USDT_price;
    BNB_price = _BNB_price;
    SOL_price = _SOL_price;
}
transaction::transaction(){}
int transaction :: buy(int walletIP,string coin,double amount)
{
    for (int i = 0; i < WalletManagement::WalletRefInstant.size(); ++i)
    {
        if(WalletManagement::WalletRefInstant[i].walletIP == walletIP)
        {
            if(coin == "BTC")
            {
                // withdraw USD
                double needed_USD = BTC_price * amount;
                if(WalletManagement::WalletRefInstant[i].withdraw("USD",needed_USD) == 1)
                {
                    // deposit
                    if(WalletManagement::WalletRefInstant[i].deposit("BTC",amount) == 1)
                    {
                        return 1;
                    }else
                    {
                        return 4;
                    }
                }else
                {
                    return 3;
                }
            }
            else if(coin == "ETH")
            {
                // withdraw USD
                double needed_USD = ETH_price * amount;
                if(WalletManagement::WalletRefInstant[i].withdraw("USD",needed_USD) == 1)
                {
                    // deposit
                    if(WalletManagement::WalletRefInstant[i].deposit("ETH",amount) == 1)
                    {
                        return 1;
                    }else
                    {
                        return 4;
                    }
                }else
                {
                    return 3;
                }
            }
            else if(coin == "USDT")
            {
                // withdraw USD
                double needed_USD = USDT_price * amount;
                if(WalletManagement::WalletRefInstant[i].withdraw("USD",needed_USD) == 1)
                {
                    // deposit
                    if(WalletManagement::WalletRefInstant[i].deposit("USDT",amount) == 1)
                    {
                        return 1;
                    }else
                    {
                        return 4;
                    }
                }else
                {
                    return 3;
                }
            }
            else if(coin == "BNB")
            {
                // withdraw USD
                double needed_USD = BNB_price * amount;
                if(WalletManagement::WalletRefInstant[i].withdraw("USD",needed_USD) == 1)
                {
                    // deposit
                    if(WalletManagement::WalletRefInstant[i].deposit("BNB",amount) == 1)
                    {
                        return 1;
                    }else
                    {
                        return 4;
                    }
                }else
                {
                    return 3;
                }
            }
            else if(coin == "SOL")
            {
                // withdraw USD
                double needed_USD = SOL_price * amount;
                if(WalletManagement::WalletRefInstant[i].withdraw("USD",needed_USD) == 1)
                {
                    // deposit
                    if(WalletManagement::WalletRefInstant[i].deposit("SOL",amount) == 1)
                    {
                        return 1;
                    }else
                    {
                        return 4;
                    }
                }else
                {
                    return 3;
                }
            }
            else
            {
                return 2;
            }
        }
    }
    return 5;
}
int transaction ::sell()
{
}
int transaction :: exchange()
{
}
int transaction :: Add_In_Queue()
{
    while(Queue.size() != 0){
        if(Queue[0][1] == "b"){
            //buy methode be called
        }
        else if(Queue[0][1] == "s"){
            //sell method be called
    }
        else{
            //exchange method be called
        }
    Queue.erase(Queue.begin());
    }
    is_QUEUE_EMPTY = true;
}
int transaction :: Analayzer(std :: string username , std :: string operation, std :: string balance ,std :: string coin_requested,double current_price,double amount_requested){
    //-X  <username> (b/s/e) <balance> <a number 1=bitcoin 2=enthrium 3=tether 4=nb 5=solana
    if(atof(balance.c_str())<current_price*amount_requested){
        return -1;    
    }
    else{
        std :: vector<std :: string> temp;
        temp.push_back(username);
        temp.push_back(operation);
        temp.push_back(balance);
        temp.push_back(coin_requested);
        temp.push_back(std::to_string(current_price));
        temp.push_back(std :: to_string(amount_requested));
        Queue.push_back(temp);
        if(is_QUEUE_EMPTY){
        emit vector_not_empty();
            }
        }
    return 1;
}
