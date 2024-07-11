#ifndef WALLETMANAGEMENT_H
#define WALLETMANAGEMENT_H
#include "wallet.h"
#include <string>

class WalletManagement
{
    WalletManagement();
public:
    static vector<Wallet> WalletRefInstant;
    static void load_all_wallets();

    static int create_new_wallet(int ownerUserID);
    /*
     * it returns IP address of new created wallet
    */
    static int create_new_wallet(string username);
    /*
     * it returns IP address of new created wallet
    */
};

#endif // WALLETMANAGEMENT_H
