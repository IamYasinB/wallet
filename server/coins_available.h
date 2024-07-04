#ifndef COINS_AVAILABLE_H
#define COINS_AVAILABLE_H
#include "coin.h"
#include <QThread>
#include <QMainWindow>
class Coins_available : public QMainWindow
{
    Q_OBJECT
private:  //all Coins available
    Coin* BITCOIN;
    Coin* ETHEREUM;
    Coin* TETHER;
    Coin* BNB;
    Coin* SOLANA;
    Coin* XRP;
    Coin* TRON;
public:
    Coins_available();
    void update_all();
};

#endif // COINS_AVAILABLE_H
