#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QtNetwork/QTcpSocket>
#include <QString>
#include <QDebug>
#include <QApplication>
#include <iostream>
QT_BEGIN_NAMESPACE
namespace Ui {
class Client;
}
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT
private:
    QTcpSocket socket;
public:
    Client(QWidget *parent = nullptr);
    ~Client();
    int conncet_to_server();
    int Write(QString Text);
private:
    Ui::Client *ui;
private slots:
    std :: string Read();

    void on_pushButton_exit_clicked();
};
#endif // CLIENT_H
