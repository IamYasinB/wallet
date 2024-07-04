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
#include <QThread>
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
    Coin* XRP;
    Coin* TRON;

    QThread workerThread;

signals:

    void start_updating();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpServer* Server;
    QList<QTcpSocket*> Client_connection_list;
private slots:
    void update();
    void newconnection();
    void Read_Data_From_Socket();
    void send_for_client(QString Message);
};
#endif // MAINWINDOW_H
