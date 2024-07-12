#include "mainwindow.h"
#include "database.h"
#include <QtCore>
#include <QtNetwork>
#include <QThread>
#include <vector>
#include "wallet.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include "walletmanagement.h"
std::vector<QString> splitIntoWords(const QString &input) {
    // Split the input string by spaces
    QStringList wordList = input.split(' ', Qt::SkipEmptyParts);

    // Convert QStringList to std::vector<QString>
    std::vector<QString> result;
    for (const auto &word : wordList) {
        result.push_back(word);
    }

    return result;
}
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
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
    /*     QTimer* timer = new QTimer(this);
     connect(timer, &QTimer::timeout, this,&MainWindow::sendprice);
     timer->start(20000)*/
}


MainWindow::~MainWindow() {}
void MainWindow :: newconnection(){
    while(Server->hasPendingConnections()){
        Add_new_Client_connection(Server->nextPendingConnection());
    }
}
void MainWindow :: Add_new_Client_connection(QTcpSocket* socket){
    connect(socket,&QTcpSocket::readyRead,this,&MainWindow::Read_Data_From_Socket);
    QString CLient = "Client : " + QString::number(socket->socketDescriptor()) + " Connected with The Server";
    qDebug() << CLient;
}
void MainWindow :: Read_Data_From_Socket(){
    QTcpSocket *socket = reinterpret_cast<QTcpSocket*>(sender());
    QByteArray Message_from_client = socket->readAll();
    qDebug() << Message_from_client;
    //Client_Request(Message_from_client);
    if(Message_from_client == "p"){
        qDebug() << "sending price";
        if(BITCOIN->getprice()!=0){
            send_for_client("B"+QString :: number(BITCOIN->getprice()));
            _sleep(2000);}
        if(ETHEREUM->getprice()!=0){
            send_for_client("E"+QString :: number(ETHEREUM->getprice()));
            _sleep(2000);}
        if(TETHER->getprice()!=0){
            send_for_client("T"+QString :: number(TETHER->getprice()));
            _sleep(2000);}
        if(BNB->getprice()!=0){
            send_for_client("N"+QString :: number(BNB->getprice()));
            _sleep(2000);}
        if(SOLANA->getprice()!=0){
            send_for_client("S"+QString :: number(SOLANA->getprice()));
        }qDebug() << "Price has been sent";
    }
    else{
        send_for_client(Client_Request(Message_from_client));
    }
}
void MainWindow ::  send_for_client(QString Message){
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if(socket && socket->state() == QAbstractSocket::ConnectedState){
        socket->write(Message.toUtf8());
        socket->flush();
    }
    else{
        qDebug() << "error";
    }
}
QString MainWindow :: Client_Request(QString REQUEST){

    if(REQUEST[1] == 'A' && REQUEST[2] == 'W'){  //-AW <username>

        std :: vector<QString> words = splitIntoWords(REQUEST);
        int result = WalletManagement::create_new_wallet(words[1].toStdString());
        QString Result = "WR" + QString :: number(result);
        qDebug() << Result;
        return Result;

    }
    else if(REQUEST[1] == 'S' && REQUEST[2] == 'W'){
        std :: vector<QString> words = splitIntoWords(REQUEST);
        std :: vector<QString> wallet(WalletManagement::get_user_wallet_IPs(words[1].toStdString()));
        QString Result;
        for(size_t i = 0;i<wallet.size();i++){
            Result +=wallet[i]+" ";
        }
        return "WS"+Result;
    }
    else if(REQUEST[1] == 'S' && REQUEST[2] == 'I'){ //-SU <username> <password>
        //TODO
        //sign up function be called and write that in data base
        //if signup was seccesfull return QSTRING "SU_S" and  if it was not return "SU_F" with the send_for_client() function
        std :: vector<QString> words = splitIntoWords(REQUEST);
        bool result = UsersManagement::signin(words[1].toStdString(),words[2].toStdString());
        int R;
        if(result == true){
            R=1;
        }
        else{
            R=0;
        }
        QString Result = QString :: number(R);
        qDebug() << Result;
        return "1"+Result;
    }
    else if(REQUEST[1] == 'S' && REQUEST[2] == 'U'){ //-SU <username> <password> <email>
        //TODO
        //sign in function be called and check user information that in data base
        //if signup was seccesfull return QSTRING "SI_S" and  if it was not return "SI_F" with the send_for_client() function
        std :: vector<QString> words = splitIntoWords(REQUEST);
        int result = UsersManagement::signup(words[3].toStdString(),words[2].toStdString(),words[1].toStdString());
        QString Result = QString :: number(result);
        qDebug() << Result;
        return Result;
    }
    else if(REQUEST[1] == 'C' && REQUEST[2] == 'I' ){ //-CI <username>
        //TODO
        //change username function should be called
        //the user name is already checked in the sign in function so it's valid and there should be no error for changing a user information
    }
    else if(REQUEST[1] == 'G' && REQUEST[2] == 'B'){
        std :: vector<QString> words = splitIntoWords(REQUEST);
        double result = WalletManagement::get_wallet_USD(words[1].toInt());
        QString Result = QString :: number(result);
        qDebug() << Result;
        return "GB" + Result;
    }
    else if(REQUEST[1] == 'R' && REQUEST[2] == 'G'){ //-RG <username> <name> <phone number> <address>
        std :: vector<QString> words = splitIntoWords(REQUEST);
        int result = UsersManagement::do_registeration_by_username(words[1].toStdString(),words[2].toStdString(),words[3].toStdString(),words[4].toStdString());
        QString Result = QString :: number(result);
        return "2"+Result;
    }
    else if(REQUEST[1] == 'I' && REQUEST[2] == 'R'){ //-IR <username>
        std :: vector<QString> words = splitIntoWords(REQUEST);
        bool result = UsersManagement::is_register_by_username(words[1].toStdString());
        QString Result = "IR";
        if(result){
            Result+="1";
        }
        else{
            Result+="0";
        }
        qDebug() << Result;
        return Result;
    }
    else if(REQUEST[1]=='F'&&REQUEST[2]=='P'){
        std :: vector<QString> words = splitIntoWords(REQUEST);
       bool result =  UsersManagement::forget_password(words[2].toStdString(),words[1].toStdString());
        QString Result="1";
        if(result){
            Result+="1";
        }
        else{
            Result+="0";
        }
        return Result;
    }
    else if(REQUEST[1]=='S'&&REQUEST[2]=='H'){
        std :: vector<QString> words = splitIntoWords(REQUEST);
        //yasin waiting for you
        //vector<QString> each_balance
    }
    else if(REQUEST[0]=='X'){
        std :: vector<QString> words = splitIntoWords(REQUEST);
        all_trc = new transaction(BITCOIN->getprice(),ETHEREUM->getprice(),TETHER->getprice(),BNB->getprice(),SOLANA->getprice());
        if(words[1]=="b"){
           int result =  all_trc->buy(words[2].toInt(),words[3].toStdString(),words[4].toDouble());
            QString Result = QString :: number(result);
           return "X"+Result;
        }
        else if(words[1]=="s"){
            int result =  all_trc->sell(words[2].toInt(),words[3].toStdString(),words[4].toDouble());
            QString Result = QString :: number(result);
            return "X"+Result;

        }
    }



    return "nothing";
}
