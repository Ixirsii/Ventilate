/*! \file
 * \brief Define functionality for ConnectionHandler class.
 * \author Ryan Porterfield
 * \since 2015-09-11
 * \copyright BSD 3 Clause
 */

#include "connectionhandler.h"
#include <memory>
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QThreadPool>
#include "server/commandparser.h"
#include "networktask.h"
#include "server/server.h"

ConnectionHandler::ConnectionHandler(ConnectionHandler &&move)
    : QObject(move.parent()), socket(move.socket),
      socketDescriptor(move.socketDescriptor), clients(move.clients)
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    disconnect(socket, SIGNAL(readyRead()), &move, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    disconnect(socket, SIGNAL(disconnected()), &move, SLOT(disconnected()));
}

/*!
 * \brief Create a new ConnectionHandler.
 * \param ID Identification number of the connecting socket.
 * \param parent The calling TcpServer.
 */
ConnectionHandler::ConnectionHandler(qintptr ID,
                                     std::vector<ConnectionHandler>& clients,
                                     QObject *parent)
    : QObject(parent), socket(new QTcpSocket()), socketDescriptor(ID),
      clients(clients)
{
    qDebug() << "Opened a new ConnectionHandler";
    socket->setSocketDescriptor(socketDescriptor);
    qDebug() << "Client address: " << socket->peerAddress();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    qDebug() << "Connected to " << socketDescriptor;
}

ConnectionHandler::~ConnectionHandler()
{
}

/*!
 * \brief Called when a client disconnects from the Server.
 */
void ConnectionHandler::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    emit disconnected(*this);
}

const QHostAddress& ConnectionHandler::getHostAddress() const
{
    return std::move(QHostAddress(socket->peerAddress()));
}

void ConnectionHandler::propogate(QString message)
{
    for (ConnectionHandler &h : clients)
        h.send(message);
}

void ConnectionHandler::readyRead()
{
    qDebug() << "Received some input";
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
    QString fullcmd;
    in >> fullcmd;
    blockSize = 0;

    NetworkTask *task = new NetworkTask(*this, fullcmd, clients);
    connect(task, SIGNAL(result(QString)), this, SLOT(taskResult(QString)));
    QThreadPool::globalInstance()->start(task);
}

/**
 * @brief Sends a message to the client.
 * @param data A preformatted message ready to be written directly to the client.
 */
void ConnectionHandler::send(const QString& data) const
{
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

QString ConnectionHandler::serializePeerList()
{
    QString list = "";
    for (const ConnectionHandler &handler: clients) {
        list = list.append(handler.getHostAddress().toString());
        list = list.append(CommandParser::SEP);
    }
    return list;
}

void ConnectionHandler::taskResult(QString result)
{
    send(result);
}

ConnectionHandler& ConnectionHandler::operator=(ConnectionHandler &&move)
{
    setParent(move.parent());
    move.setParent(nullptr);
    socket = move.socket;
    move.socket = nullptr;
    socketDescriptor = move.socketDescriptor;

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    disconnect(socket, SIGNAL(readyRead()), &move, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    disconnect(socket, SIGNAL(disconnected()), &move, SLOT(disconnected()));

    return *this;
}

bool operator==(const ConnectionHandler& ch0, const ConnectionHandler& ch1)
{
    return ch0.socketDescriptor == ch1.socketDescriptor;
}

bool operator!=(const ConnectionHandler& ch0, const ConnectionHandler& ch1)
{
    return ch0.socketDescriptor != ch1.socketDescriptor;
}
