#include "client_main.h"
#include "ui_client_main.h"
#include "client.h"
#include <QDebug>
#include <QMessageBox>
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
    request_wallets(this->username);
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
    Write("-GB "+ui->comboBox->currentText().remove(0,10));
    qDebug() << "-GB "+ui->comboBox->currentText().remove(0,10);
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
             Wallet_name.push_back(Message_from_server);
             ui->comboBox->addItem("Wallet_ID_"+Message_from_server);

    }
    else if(Message_from_server[0] == 'W' && Message_from_server[1] == 'S'){
               Message_from_server = Message_from_server.remove(0,2);
        Wallet_name = splitIntoWords(Message_from_server);
               for(size_t i = 0;i<Wallet_name.size();i++){
            ui->comboBox->addItem("Wallet_ID_"+Wallet_name[i]);
        }

            }
    else if(Message_from_server[0] == 'I'&& Message_from_server[1] == 'R'){
                if(Message_from_server=="IR1"){
            isregister = true;
        }
                else{
                    isregister = false;
                }

    }
    else if(Message_from_server[0]=='G' &&Message_from_server[1]=='B'){
                Message_from_server = Message_from_server.remove(0,2);
        qDebug() << Message_from_server;
        balance = Message_from_server;
            }
    else if(Message_from_server[0] == 'X'){
        Message_from_server =  Message_from_server.remove(0,1);
                if(Message_from_server=="1"){
            QMessageBox::information(this, "Operation", "Operation seccessful");

        }
                else{
                    /*
     * if successful return 1
     * if coin name is wrong return 2
     * if could not deposit coin return 3
     * if could not withdraw USD return 4
     * if could not find wallet ip return 5
    */
                     if(Message_from_server=="2"){
                        QMessageBox::information(this, "Operation", "Operation Faild : coin not valid");
                    }
                     else if(Message_from_server=="3"){
                         QMessageBox::information(this, "Operation", "Operation Faild : deposit failed");
                     }
                    else if(Message_from_server=="4"){
                        QMessageBox::information(this, "Operation", "Operation Faild : withdraw failed");

                    }
                     else if(Message_from_server=="5"){
                         QMessageBox::information(this, "Operation", "Operation Faild : Wallet not found");

                     }
                }
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
void client_main:: request_wallets(QString username){
    Write("-SW "+username);
}
void client_main :: buy_sell_rq(QString operation,QString amount,QString coin){
    QString walletIP = ui->comboBox->currentText().remove(0,10);
    Write("X "+operation+" "+walletIP+" "+coin+" "+amount+" ");
}
void client_main::request_isregister(){
    Write("-IR "+username);
}
void client_main::on_pushButton_addwallet_clicked()
{
    // request_isregister();
    // if(isregister == true){
    //         QMessageBox::information(this, "Create wallet failed", "You are not registered yet");
    //     return;
    // }
    if(Wallet_name.size()>=3){
             QMessageBox::information(this, "Create wallet failed", "You can not have more then 3 wallets");
        return;
    }
    Write("-AW "+username);
}


void client_main::on_pushButton_3_clicked()
{
    buy_sell_rq("b",ui->lineEdit_1->text(),"BTC");
    ui->lineEdit_1->setText("");
}


void client_main::on_pushButton_4_clicked()
{
    buy_sell_rq("s",ui->lineEdit_1->text(),"BTC");
    ui->lineEdit_1->setText("");

}


void client_main::on_pushButton_5_clicked()
{
    buy_sell_rq("b",ui->lineEdit_2->text(),"ETH");
    ui->lineEdit_2->setText("");

}


void client_main::on_pushButton_6_clicked()
{
    buy_sell_rq("s",ui->lineEdit_2->text(),"ETH");
    ui->lineEdit_2->setText("");

}


void client_main::on_pushButton_7_clicked()
{
    buy_sell_rq("b",ui->lineEdit_3->text(),"USDT");
    ui->lineEdit_3->setText("");

}


void client_main::on_pushButton_8_clicked()
{
    buy_sell_rq("s",ui->lineEdit_3->text(),"USDT");
    ui->lineEdit_3->setText("");

}


void client_main::on_pushButton_9_clicked()
{
    buy_sell_rq("b",ui->lineEdit_4->text(),"BNB");
    ui->lineEdit_4->setText("");
}


void client_main::on_pushButton_10_clicked()
{
    buy_sell_rq("s",ui->lineEdit_4->text(),"BNB");
    ui->lineEdit_4->setText("");
}


void client_main::on_pushButton_11_clicked()
{
    buy_sell_rq("b",ui->lineEdit_5->text(),"SOL");
    ui->lineEdit_5->setText("");
}


void client_main::on_pushButton_12_clicked()
{
    buy_sell_rq("s",ui->lineEdit_5->text(),"SOL");
    ui->lineEdit_5->setText("");
}


void client_main::on_pushButton_showwallet_clicked()
{
    Write("-SH "+ui->comboBox->currentText().remove(0,10));
}

