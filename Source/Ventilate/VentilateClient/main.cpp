#include "mainwindow.h"
#include <QApplication>
#include "socket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Socket s("127.0.0.1", 37377);
    s.send("LOGIN ShadowHawk54 password");

    return a.exec();
}
