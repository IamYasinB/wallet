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

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void Add_new_Client_connection(QTcpSocket* socket);

    Coin* BITCOIN;
    Coin* ETHEREUM;
    Coin* TETHER;
    Coin* BNB;
    Coin* SOLANA;
    // Coin* XRP;
    // Coin* TRON;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpServer* Server;
    QList<QTcpSocket*> Client_connection_list;
    void Client_Request(std :: string REQUEST);
private slots:
    void newconnection();
    void Read_Data_From_Socket();
    void send_for_client(QString Message);
};
#endif // MAINWINDOW_H
