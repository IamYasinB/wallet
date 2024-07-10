#ifndef CLIENT_MAIN_H
#define CLIENT_MAIN_H

#include <QDialog>
#include <QCoreApplication>
#include <QtNetwork/QTcpSocket>
#include <QString>
#include <QDebug>
#include <QApplication>
#include <QObject>
#include <QTimer>
class Client;
namespace Ui {
class client_main;
}

class client_main : public QDialog
{
    Q_OBJECT

public:
    explicit client_main(QTcpSocket* soocket,QWidget *parent = nullptr);
    ~client_main();
    int Write(QString Text);
    void request_price();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
public slots:
    QString read(QByteArray Message_from_serverr);
private:
    Ui::client_main *ui;
    QTcpSocket* socket;
    Client* NewPage;

};

#endif // CLIENT_MAIN_H
