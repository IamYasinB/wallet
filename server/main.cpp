#include "mainwindow.h"
#include <QApplication>
#include <database.h>
#include "usersmanagement.h"
#include "walletmanagement.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    DataBase* db = DataBase::getInstance();
    UsersManagement::loader();
    WalletManagement::load_all_wallets();
    return a.exec();
}
