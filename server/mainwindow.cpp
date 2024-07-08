#include "mainwindow.h"
#include "database.h"
#include <QtCore>
#include <QtNetwork>
#include <QThread>
#include <vector>
#include "wallet.h"
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
    Client_Request(Message_from_client);
}
void MainWindow ::  send_for_client(QString Message){
    QTcpSocket *socket = reinterpret_cast<QTcpSocket*>(sender());
    socket->write(Message.toUtf8());
    socket->flush();
    socket->waitForBytesWritten(3000);
}
void MainWindow :: Client_Request(QString REQUEST){
    if(REQUEST[1] == 'G' && REQUEST[2] == 'W'){  //-GW <username>
        QString IP = QString :: fromStdString(wallet::Generate_IP());
        //write in data base
        //TODO
        send_for_client(IP);
    }
    else if(REQUEST[1] == 'S' && REQUEST[2] == 'U'){ //-SU <username> <password>
        //TODO
        //sign up function be called and write that in data base
        //if signup was seccesfull return QSTRING "SU_S" and  if it was not return "SU_F" with the send_for_client() function
    }
    else if(REQUEST[1] == 'S' && REQUEST[2] == 'U'){ //-SI <username> <password>
        //TODO
        //sign in function be called and check user information that in data base
        //if signup was seccesfull return QSTRING "SI_S" and  if it was not return "SI_F" with the send_for_client() function

    }
    else if(REQUEST[1] == 'C' && REQUEST[2] == 'I' ){ //-CI <username>
        //TODO
        //change username function should be called
        //the user name is already checked in the sign in function so it's valid and there should be no error for changing a user information
    }
    else if(REQUEST[1] == 'R' && REQUEST[2] == 'G'){ //-RG <username> <code meli> <birth_day(in string)> <phone number>
        //TODO
        //Register function should be called here
    }
    else if(REQUEST[1] == 'I' && REQUEST[2] == 'R'){ //-IR <username>
        //TODO
        //is_registered function should be called here
        //if user was register send 'T' and if it was not return 'F'
    }
    //transaction
    else if(REQUEST[1]=='X'){ //-X <username> <b/s/e> <balance> <1/2/3/4/5> <amount wanted>
        std :: vector<std :: string> command;/* = command_seperator(REQUEST.toStdString());*/
        double price;
        if(command[4]=="1"){
            price = BITCOIN->getprice();
        }
        if(command[4]=="2"){
            price = ETHEREUM->getprice();
        }
        if(command[4]=="3"){
            price = TETHER->getprice();
        }
        if(command[4]=="4"){
            price = BNB->getprice();
        }
        if(command[4]=="5"){
            price = SOLANA->getprice();
        }
        all_trc.Analayzer(command[1],command[2],command[3],command[4],price,atof(command[5].c_str()));
        
    }
 }
