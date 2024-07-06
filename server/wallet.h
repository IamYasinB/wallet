#ifndef WALLET_H
#define WALLET_H

#include <QObject>
#include <iostream>
class wallet
{
    Q_OBJECT
private:
    std :: string IP;

    double EACH_COIN_BALANCE[5]; //in order bitcon-eithrerum-tether-bnb-solana
public:

    std :: string GetIP();

    static std :: string Generate_IP();

};

#endif // WALLET_H
