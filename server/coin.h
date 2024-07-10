#ifndef COIN_H
#define COIN_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <iostream>
class Coin : public QObject
{
        Q_OBJECT

private:
    double PRICE = 0;
    QString NAME;
    QString URL;
    QNetworkAccessManager* Network_Maneger;
public:
    Coin(QString name,QString url,QObject* parent = nullptr);

    int getprice();

    void Update();

private slots:

    void OnResult(QNetworkReply* reply);
};

#endif // COIN_H
