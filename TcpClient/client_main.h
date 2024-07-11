#ifndef CLIENT_MAIN_H
#define CLIENT_MAIN_H

#include <QDialog>
#include <QCoreApplication>
#include <QtNetwork/QTcpSocket>
#include <QString>
#include <QDebug>
#include <QApplication>
#include <vector>
#include <QObject>
#include <QTimer>
#include "register.h"

class Client;
namespace Ui {
class client_main;
}

class client_main : public QDialog
{
    Q_OBJECT

public:
    explicit client_main(QString username,QTcpSocket* soocket,QWidget *parent = nullptr);
    ~client_main();
    int Write(QString Text);
    void request_price();
    void request_balance();
    std :: vector<QString> Wallet_name;
    void request_wallets(QString username);
    void request_isregister();
    void buy_sell_rq(QString operation,QString amount,QString coin);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_addwallet_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

public slots:
    QString read(QByteArray Message_from_serverr);
private:
        bool isregister;
    QTimer* timer;
    QString username;
    QString balance;
    Ui::client_main *ui;
    QTcpSocket* socket;
    Client* NewPage;
    Register* NewPage2;
};

#endif // CLIENT_MAIN_H
