#include "transaction.h"
#include "coin.h"
#include "mainwindow.h"
using namespace std;
transaction :: transaction(){
    connect(this,SIGNAL(vector_not_empty()),this,SLOT(Add_In_Queue()));
}
int transaction :: buy(int walletIP,string coin,double amount)
{
    for (int i = 0; i < WalletManagement::WalletRefInstant.size(); ++i)
    {
        if(WalletManagement::WalletRefInstant[i].walletIP == walletIP)
        {
            MainWindow priceBoard;
            if(coin == "BTC")
            {
                // withdraw USD
                double needed_USD = priceBoard.BITCOIN->getprice() * amount;
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
                double needed_USD = priceBoard.ETHEREUM->getprice() * amount;
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
                double needed_USD = priceBoard.TETHER->getprice() * amount;
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
                double needed_USD = priceBoard.BNB->getprice() * amount;
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
                double needed_USD = priceBoard.SOLANA->getprice() * amount;
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
