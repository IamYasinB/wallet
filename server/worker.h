#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
#include "coin.h"

class Worker : public QObject {
    Q_OBJECT

public:
    Worker() {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Worker::update);
    }

    void start(Coin* bitcoin, Coin* ethereum, Coin* tether, Coin* bnb, Coin* solana, Coin* xrp, Coin* tron) {
        BITCOIN = bitcoin;
        ETHEREUM = ethereum;
        TETHER = tether;
        BNB = bnb;
        SOLANA = solana;
        XRP = xrp;
        TRON = tron;
        timer->start(10000); // Start the timer with a 1-minute interval (60000 milliseconds)
    }

public slots:
    void update() {
        ETHEREUM->Update();        TETHER->Update();
        BNB->Update();
        SOLANA->Update();
        XRP->Update();
        TRON->Update();
    }

private:
    Coin* BITCOIN;
    Coin* ETHEREUM;
    Coin* TETHER;
    Coin* BNB;
    Coin* SOLANA;
    Coin* XRP;
    Coin* TRON;
    QTimer* timer;
};

#endif // WORKER_H
