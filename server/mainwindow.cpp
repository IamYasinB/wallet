#include "mainwindow.h"
#include "database.h"
#include <QtCore>
#include <QtNetwork>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Server = new QTcpServer();
    if(Server->listen(QHostAddress :: Any,6000)){
        qDebug() << "Sever Started Seccessfully";

        BITCOIN = new Coin("bitcoin", "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd");
        ETHEREUM = new Coin("ethereum", "https://api.coingecko.com/api/v3/simple/price?ids=ethereum&vs_currencies=usd");
        TETHER = new Coin("tether", "https://api.coingecko.com/api/v3/simple/price?ids=tether&vs_currencies=usd");
        BNB = new Coin("binancecoin", "https://api.coingecko.com/api/v3/simple/price?ids=binancecoin&vs_currencies=usd");
        SOLANA = new Coin("solana", "https://api.coingecko.com/api/v3/simple/price?ids=solana&vs_currencies=usd");




         // XRP = new Coin("ripple", "https://api.coingecko.com/api/v3/simple/price?ids=ripple&vs_currencies=usd");
         // TRON = new Coin("tron", "https://api.coingecko.com/api/v3/simple/price?ids=tron&vs_currencies=usd");




        bool connectionSuccessful = connect(Server,SIGNAL(newConnection()),this,SLOT(newconnection()));

        if (connectionSuccessful) {
            qDebug() << "Connected newConnection signal to slot successfully.";
        } else {
            qDebug() << "Failed to connect newConnection signal to slot.";
        }
    }
    else{
        qDebug() << "Server Failed";
    }
}



MainWindow::~MainWindow() {}
void MainWindow :: newconnection(){
    while(Server->hasPendingConnections()){
    Add_new_Client_connection(Server->nextPendingConnection());
    }
}
void MainWindow :: Add_new_Client_connection(QTcpSocket* socket){
    Client_connection_list.append(socket);
    connect(socket,&QTcpSocket::readyRead,this,&MainWindow::Read_Data_From_Socket);
    QString CLient = "Client : " + QString::number(socket->socketDescriptor()) + " Connected with The Server";
    qDebug() << CLient;
}
void MainWindow :: Read_Data_From_Socket(){
    QTcpSocket *socket = reinterpret_cast<QTcpSocket*>(sender());
    QByteArray Message_from_client = socket->readAll();
    qDebug() << Message_from_client;

}
void MainWindow ::  send_for_client(QString Message){
    QTcpSocket *socket = reinterpret_cast<QTcpSocket*>(sender());
    socket->write(Message.toUtf8());
    socket->flush();
    socket->waitForBytesWritten(3000);
}
