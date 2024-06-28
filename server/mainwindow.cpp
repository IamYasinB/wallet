#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Server = new QTcpServer();
    if(Server->listen(QHostAddress :: Any,1234)){
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
    connect(socket,SIGNAL(readyRead()),this,SLOT(Read_Data_From_Socket()));
    QString CLient = "Client : " + QString::number(socket->socketDescriptor()) + " Connected with The Server";
    qDebug() << CLient;
}
void MainWindow :: Read_Data_From_Socket(){
    QTcpSocket *socket = (QTcpSocket*)sender();
    QByteArray Message_from_sever = socket->readAll();
    QString Message = QString::fromStdString(Message_from_sever.toStdString());

}
