#include "mainwindow.h"
#include "database.h"
#include <QtCore>
#include <QtNetwork>
#include "coin.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Server = new QTcpServer();
    if(Server->listen(QHostAddress :: Any,6000)){
        qDebug() << "Sever Started Seccessfully";
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
