#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <database.h>
#include "coin.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    DataBase d1;
    d1.open();
    //adding coin updates
    Coin BITCOIN("bitcoin","https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd");
    BITCOIN.Update(); //this goes in a thread
    return a.exec();
}
