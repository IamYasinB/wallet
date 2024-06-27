#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Server = new QTcpServer();
    if(Server->listen(QHostAddress :: Any,6000)){
        connect(Server,SIGNAL(newConnection()),this,SLOT(newconnection()));
        qDebug() << "Sever Started Seccessfully";
    }
    else{
        qDebug() << "Server Failed";
    }
}

MainWindow::~MainWindow() {}
void MainWindow :: newConnection(){
    while(Server->hasPendingConnections()){
    Add_new_Client_connection(Server->nextPendingConnection());
    }
}
void MainWindow :: Add_new_Client_connection(QTcpSocket* socket){
    Client_connection_list.append(socket);
    connect(socket,SIGNAL(readyRead()),this,SLOT(Read_Data_From_Socket()));
    qDebug() << "new client has been connected";
    QString CLient = "Client : " + QString::number(socket->socketDescriptor()) + "Connected with The Server";
}
void MainWindow :: Read_Data_From_Socket(){
    QTcpSocket *socket = (QTcpSocket*)sender();
    QByteArray Message_from_sever = socket->readAll();
    QString Message = QString::fromStdString(Message_from_sever.toStdString());

}
