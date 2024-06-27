#include "mainwindow.h"
#include <QCoreApplication>
#include <QtNetwork/QTcpSocket>
#include <QString>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1",6000);
    while(!socket.waitForConnected(3000)){
        socket.connectToHost("127.0.0.1",6000);
    }
    qDebug() << "Connected to the server";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
