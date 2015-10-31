#include "socket_test.h"

Socket_test::Socket_test(QObject *parent) : QObject(parent)
{

}

void Socket_test::Connect()
{
    socket = new QTcpSocket(this);

    //connect
    socket->connectToHost( , ); //example: socket->connectToHost("voidrealms.com", 80);
    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";

        //send
        socket->write("hello server\n\r\n\r\n\r\n\r");

        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);
        qDebug() << "Reading:" << socket->bytesAvailable();

        qDebug() << socket->readAll();

        socket->close();
    }
    else
    {
        qDebug() << "Not connected!";
    }
    //connect
    //get
    //send
    //close

}
