/*! \file
 * \brief Define functionality for ConnectionHandler class.
 * \author Ryan Porterfield
 * \since 2015-09-11
 * \copyright BSD 3 Clause
 */

#include "connectionhandler.h"
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include "server/server.h"

/*!
 * \brief Create a new ConnectionHandler.
 * \param ID Identification number of the connecting socket.
 * \param parent The calling TcpServer.
 */
ConnectionHandler::ConnectionHandler(qintptr ID, QObject *parent)
    : QThread(parent), socketDescriptor(ID)
{
}

/*!
 * \brief Called when a client disconnects from the Server.
 */
void ConnectionHandler::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    Server *server = static_cast<Server*>(this->parent());
    server->disconnectClient(this);
    socket->deleteLater();
    exit(0);
}


const QHostAddress& ConnectionHandler::getHostAddress() const
{
    return std::move(QHostAddress(socket->peerAddress()));
}

/*!
 * \brief Connect to a client.
 */
void ConnectionHandler::run()
{
    qDebug() << "Opened a new ConnectionHandler";
    socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        emit error(socket->error());
        return;
    }
    qDebug() << "Client address: " << socket->peerAddress();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    qDebug() << "Connected to " << socketDescriptor;

    exec();
}

void ConnectionHandler::readyRead()
{
    static qint16 blockSize = 0;
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
    Server *server = static_cast<Server*>(parent());
    server->onClientRequest(*this, in);
}


/**
 * @brief Sends a message to the client.
 * @param data A preformatted message ready to be written directly to the client.
 */
void ConnectionHandler::sendToClient(QByteArray data) const
{
    qDebug() << "Sending data: " << data;
    socket->write(data);
}

void ConnectionHandler::write(QString data) const
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    // Reserve space for size of block
    out << (quint16) 0;
    out << data;
    // Seek back to begining of block
    out.device()->seek(0);
    // Insert size of block at beginning
    out << (quint16) (block.size() - sizeof(quint16));
    sendToClient(block);
}

bool operator==(const ConnectionHandler& ch0, const ConnectionHandler& ch1)
{
    return ch0.socketDescriptor == ch1.socketDescriptor;
}

bool operator!=(const ConnectionHandler& ch0, const ConnectionHandler& ch1)
{
    return ch0.socketDescriptor != ch1.socketDescriptor;
}
