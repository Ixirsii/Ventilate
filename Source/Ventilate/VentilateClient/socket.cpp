#include "socket.h"
#include <QByteArray>
#include <QDataStream>
#include <QPlainTextEdit>
#include <QString>
#include <QThread>
#include "mainwindow.h"


/*!
 * \brief Socket::Socket
 * \param host
 * \param port
 * \param parent
 */
Socket::Socket(QString host, qint16 port, MainWindow& mw, QObject *parent)
    : mw(mw), QObject(parent)
{
    socket = new QTcpSocket(this);
    socket->connectToHost(host, port);
    connect(socket, &QTcpSocket::readyRead, this, &Socket::listen);
}


/*!
 * \brief Socket::~Socket
 */
Socket::~Socket()
{
    socket->deleteLater();
}

/*!
 * \brief Socket::listen
 */
void Socket::listen()
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
    QString data;
    in >> data;
    blockSize = 0;
    // Debugging!
    mw.findChild<QPlainTextEdit*>("ptxtMessageBox")->appendPlainText(data);
}

/*!
 * \brief Socket::send
 * \param data
 */
void Socket::send(QString data) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << (quint16) 0;
    out << data;
    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));
    socket->write(block);
}
