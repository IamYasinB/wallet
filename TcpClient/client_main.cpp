#include "client_main.h"
#include "ui_client_main.h"
#include "client.h"
#include <QDebug>
client_main::client_main(QString username,QTcpSocket* socket,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::client_main)
{
    this->socket = socket;
    this->username = username;
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowModality(Qt::ApplicationModal);
//    connect(socket,&QTcpSocket::readyRead,this,&client_main::read);


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &client_main::request_price);
    timer->start(130000);

    request_price();
}
void client_main :: request_price(){
    Write("p");
    qDebug() << "Price requested";
}

client_main::~client_main()
{
    timer->stop();
    delete ui;
}
void client_main :: request_balance(){
    Write("-balance");
}

QString client_main :: read(QByteArray Message_from_serverr){
    if(Message_from_serverr.size()<=0){
        return "Empty";
    }

    QString Message_from_server = QString(Message_from_serverr);
    qDebug() << Message_from_server;
    if(Message_from_server[0]=='B'){
       Message_from_server =  Message_from_server.remove(0,1);
        ui->label_bitcoin->setText("  "+Message_from_server);
    }
    else if(Message_from_server.at(0) == 'E'){
        Message_from_server =  Message_from_server.remove(0,1);
        ui->label_Etherium->setText("  "+Message_from_server);
    }
    else if(Message_from_server[0] == 'T'){
        Message_from_server =  Message_from_server.remove(0,1);
        ui->label_Tether->setText("  "+Message_from_server);
    }
    else if(Message_from_server[0] == 'N'){
        Message_from_server =  Message_from_server.remove(0,1);
        ui->label_bnb->setText("  "+Message_from_server);
    }
    else if(Message_from_server[0] == 'S'){
        Message_from_server =  Message_from_server.remove(0,1);
        ui->label_solana->setText("  "+Message_from_server);
         }
    else if(Message_from_server[0] == 'W' && Message_from_server[1] == 'R'){
        Message_from_server = Message_from_server.remove(0,2);
             ui->comboBox->addItem(Message_from_server);
    }
    else if(NewPage2){
        NewPage2->Read(Message_from_serverr);
    }

    return Message_from_server;
}
void client_main::on_pushButton_2_clicked()
{
    NewPage = new Client(socket);
    NewPage->show();
    close();
}
int client_main ::  Write(QString Text){
    if(socket->write(Text.toUtf8())==-1){
        return -1;
    }
    socket->flush();
    socket->waitForBytesWritten(3000);
    return 1;
}

void client_main::on_pushButton_clicked()
{
    NewPage2 = new Register(username,socket,nullptr);
    NewPage2->show();
}


void client_main::on_pushButton_addwallet_clicked()
{
    Write("-AW "+username);
}

