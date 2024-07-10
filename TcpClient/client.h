#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QtNetwork/QTcpSocket>
#include <QString>
#include <QDebug>
#include <QApplication>
#include <iostream>
#include "client_main.h"
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
    client_main* New_page;
public:
    Client(QWidget *parent = nullptr);
    ~Client();
    int conncet_to_server();
    int Write(QString Text);
    void New_page_open();
private:
    Ui::Client *ui;
private slots:
    std :: string Read();

    void on_pushButton_exit_clicked();
    void on_pushButton_login_clicked();
    void on_pushButton_signup_clicked();
    void on_pushButton_fpassword_clicked();
};
#endif // CLIENT_H
