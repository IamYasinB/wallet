#include "client.h"
#include "ui_client.h"
#include <QMessageBox>
Client::Client(QTcpSocket* socket,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
    , socket(socket ? socket : new QTcpSocket(this))
{
    conncet_to_server();
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowModality(Qt::ApplicationModal);
    ui->lineEdit_username->setPlaceholderText("Username");
    ui->lineEdit_password->setPlaceholderText("Password");
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_Email->setPlaceholderText("Email");

}

Client::~Client()
{
    delete ui;
}
void Client :: New_page_open(){
    New_page = new client_main(ui->lineEdit_username->text(),&socket);
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
    QString Message = QString(Message_from_server);
    if(Message == "1"){
        QMessageBox::information(this, "Sign Up", "seccessful");
    New_page_open();
    }
    else if(Message == "2"){
        QMessageBox::information(this, "Sign Up", "this email exists");
    }
    else if(Message == "3"){
        QMessageBox::information(this, "Sign Up", "this username exist");
    }
    else if(Message == "4"){
        QMessageBox::information(this, "Sign Up", "email is not valid");
    }
    else if(Message == "5"){
        QMessageBox::information(this, "Sign Up", "username is not valid");
    }
    else if(Message == "6"){
        QMessageBox::information(this, "Sign Up", "password is not valid");
    }
    else if(Message == "7"){
        QMessageBox::information(this, "Sign Up", "Connection lost , data base not found");
    }
    else if(Message == "11"){
        QMessageBox::information(this, "Login", "Seccessfull");
        New_page_open();
    }
    else if(Message == "10"){
        QMessageBox::information(this, "Login", "Failed");
    }

    else if(New_page){
        New_page->read(Message_from_server);
              }
    qDebug() << Message_from_server;
    return (std::string)Message_from_server.toStdString();
}

void Client::on_pushButton_exit_clicked()
{
    close();
}


void Client::on_pushButton_login_clicked()
{
    if(ui->lineEdit_username->text() != "" && ui->lineEdit_password->text()!=""){
    Write("-SI " + ui->lineEdit_username->text() + " " + ui->lineEdit_password->text());
    }

}
void Client::on_pushButton_signup_clicked()
{    if(ui->lineEdit_username->text() != "" && ui->lineEdit_password->text()!="" && ui->lineEdit_Email->text()!=""){
    Write("-SU " + ui->lineEdit_username->text() + " " + ui->lineEdit_password->text() + " " + ui->lineEdit_Email->text());
    }
}


void Client::on_pushButton_fpassword_clicked()
{
    if(ui->lineEdit_username->text()!=""&&ui->lineEdit_Email->text()!=""){
        Write("-FP "+ui->lineEdit_username->text()+" "+ui->lineEdit_Email->text());
    }

}

