#include "socketlistener.h"

SocketListener::SocketListener(QObject *parent) : QObject(parent)
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(listen()), Qt::DirectConnection);
}

/*!
 * \brief Socket::listen
 */
void SocketListener::listen()
{
    static quint16 blockSize = 0;
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_0);
    if (blockSize == 0) {
        if (socket->bytesAvailable() < (int) sizeof(quint16))
            return;
        in >> blockSize;
    }
    if (socket->bytesAvailable() < blockSize)
        return;
    blockSize = 0;
    QString data;
    in >> data;
    qDebug() << "Received from server: " << data;
    emit response(data);
}

/*!
 * \brief Socket::send
 * \param data
 */
void SocketListener::send(const QString& data) const {
    qDebug() << "Sending data: " << data;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);

    out << (quint16) 0;
    out << data;
    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));

    socket->write(block);
}
