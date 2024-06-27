#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QList>
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void newConnection();
    void Read_Data_From_Socket();
private:
    void Add_new_Client_connection(QTcpSocket* socket);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpServer* Server;
    QList<QTcpSocket*> Client_connection_list;
};
#endif // MAINWINDOW_H
