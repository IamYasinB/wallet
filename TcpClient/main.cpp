#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w;
    w.conncet_to_server();
    w.Write("Hello Server");
    w.show();
    return a.exec();
}
