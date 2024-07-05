#ifndef ALL_COINS_H
#define ALL_COINS_H
#include "coin.h"
#include <QObject>
#include <QTimer>
#include <QThread>
class all_coins : public QObject
{
    Q_OBJECT
private:
    QTimer timer;


    Coin* BITCOIN;
    Coin* ETHEREUM;
    Coin* TETHER;
    Coin* BNB;
    Coin* SOLANA;
    Coin* XRP;
    Coin* TRON;


public:

    all_coins(QObject* parent = nullptr);
    void update();
};

#endif // ALL_COINS_H
