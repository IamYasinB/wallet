#ifndef WALLET_H
#define WALLET_H
#include <string>
#include "database.h"

using namespace std;

class Wallet
{
public:

    double USD_balance;
    double BTC_balance;
    double ETH_balance;
    double USDT_balance;
    double BNB_balance;
    double SOL_balance;
    int ownerUserID;
    int walletIP;

    Wallet();

    int withdraw(string coin_name,double amount);
    /*
     * returns 1 if successful
     * returns 2 if coin name is wrong
     * returns 3 if amount is greater than balance
     * returns 4 if could not update database
     */
    int deposit(string coin_name,double amount);
};

#endif // WALLET_H
