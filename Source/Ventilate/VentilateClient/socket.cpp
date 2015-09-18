#include "socket.h"

Socket::Socket(QString host, qint16 port, QObject *parent)
    : QObject(parent), connected(false), socket(this)
{
    socket->connectToHost(host, port);
    connect(socket, &QTcpSocket::readyRead, this, &Socket::listen);
}

void Socket::listen()
{

}
