#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
}

Client::~Client()
{
    delete ui;
}
int Client :: conncet_to_server(){
    socket.connectToHost("127.0.0.1",6000);
    while(!socket.waitForConnected(3000)){
        socket.connectToHost("127.0.0.1",6000);
    }
    qDebug() << "Connected to the server";
    connect(&socket,&QTcpSocket::readyRead,this,&Client::Read);
    return 1;
}
int Client :: Write(QString Text){
    if(socket.write(Text.toUtf8())==-1){
        return -1;
    }
    socket.flush();
    socket.waitForBytesWritten(3000);
    return 1;
}
std :: string Client :: Read(){
    QByteArray Message_from_server = socket.readAll();
    qDebug() << Message_from_server;
    return (std::string)Message_from_server.toStdString();
}
