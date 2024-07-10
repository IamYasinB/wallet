#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowModality(Qt::ApplicationModal);
    ui->lineEdit_username->setPlaceholderText("Username");
    ui->lineEdit_password->setPlaceholderText("Password");

}

Client::~Client()
{
    delete ui;
}
void Client :: New_page_open(){
    New_page = new client_main(&socket);
    New_page->show();
    close();
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
    if(New_page){
        New_page->read(Message_from_server);
              }
    //qDebug() << Message_from_server;
    return (std::string)Message_from_server.toStdString();
}

void Client::on_pushButton_exit_clicked()
{
    close();
}


void Client::on_pushButton_login_clicked()
{
    //if login was seccesfull
    New_page_open();
}


void Client::on_pushButton_signup_clicked()
{
    //if signup was seccesfull
    New_page_open();

}


void Client::on_pushButton_fpassword_clicked()
{
}

