#include "socket.h"
#include <QByteArray>
#include <QDataStream>
#include <QThread>

Socket::Socket(QString host, qint16 port, QObject *parent)
    : QObject(parent)
{
    socket = new QTcpSocket(this);
    socket->connectToHost(host, port);
    connect(socket, &QTcpSocket::readyRead, this, &Socket::listen);
}

void Socket::listen()
{
    QDataStream in(socket);
    quint16 blockSize = 0;
    in.setVersion(QDataStream::Qt_5_0);
    if (blockSize == 0) {
        if (socket->bytesAvailable() < (int) sizeof(quint16))
            return;
        in >> blockSize;
    }
    while (socket->bytesAvailable() < blockSize)
        QThread::sleep(1);
    QString data;
    in >> data;
    qDebug() << data;
}

void Socket::send(QString data) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << (quint16) 0;
    out << data;
    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));
    socket->write(block);
    socket->close();
}
