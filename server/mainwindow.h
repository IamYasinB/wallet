#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QList>
#include <QCoreApplication>
#include "coin.h"
#include "command_seprator.h"
#include "transaction.h"
#include "usersmanagement.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void Add_new_Client_connection(QTcpSocket* socket);


    // Coin* XRP;
    // Coin* TRON;
    transaction all_trc;

public:

    Coin* BITCOIN;
    Coin* ETHEREUM;
    Coin* TETHER;
    Coin* BNB;
    Coin* SOLANA;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpServer* Server;
    QList<QTcpSocket*> Client_connection_list;
    QString Client_Request(QString REQUEST);
private slots:
    void send_for_client(QString Message);
    void newconnection();
    void Read_Data_From_Socket();
};
#endif // MAINWINDOW_H
