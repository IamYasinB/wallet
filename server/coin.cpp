#include "coin.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
Coin :: Coin(QString NAME,QString url_string,QObject* parent) : QObject(parent),Network_Maneger(new QNetworkAccessManager(this)){
    this->NAME = NAME;
    this->URL = url_string;
    connect(Network_Maneger,&QNetworkAccessManager::finished,this, &Coin :: OnResult);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Coin::Update);
    timer->start(120000);

    Update();

}
int Coin :: getprice(){
    return PRICE;
}

void Coin :: Update(){
    QUrl Url(URL);
    QNetworkRequest request(Url);
    Network_Maneger->get(request);
}
void Coin :: OnResult(QNetworkReply* reply){
    if(reply->error() == QNetworkReply :: NoError){
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument:: fromJson(response);
        QJsonObject JsonObj = jsonDoc.object();
        QJsonObject PriceObj = JsonObj.value(NAME).toObject();
        this->PRICE = PriceObj.value("usd").toDouble();
        qDebug() << "Price is updated know";
        qDebug() << NAME << ": ";
        qDebug() << QString :: number(PRICE);
     }
    else{
        qDebug() << "Low internet quality";
    }
     reply->deleteLater();
}
