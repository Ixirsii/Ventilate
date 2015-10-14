/*
CSE.444-002-Grp-Project
*/

#include <QCoreApplication>
#include "socket_test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Socket_test cTest;
    cTest.Connect();

    return a.exec();
}
