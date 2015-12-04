/*! \file
 *
 */

#include "socket.h"
#include <QByteArray>
#include <QDataStream>
#include <QString>
#include <QThread>

/*!
 * \brief Socket::Socket
 * \param host
 * \param port
 * \param parent
 */
Socket::Socket(QString host, qint16 port, QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
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
