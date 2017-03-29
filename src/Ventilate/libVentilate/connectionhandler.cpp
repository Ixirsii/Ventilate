/*! \file
 * \brief Define functionality for ConnectionHandler class.
 * \author Ryan Porterfield
 * \since 2015-09-11
 * \copyright BSD 3 Clause
 */

#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QThreadPool>

#include <memory>

#include "connectionhandler.h"
#include "networktask.h"
#include "socketlistener.h"
#include "server/commandparser.h"
#include "server/server.h"

ConnectionHandler::ConnectionHandler(ConnectionHandler &&move)
    : SocketListener(std::move(move)), clients(move.clients)
{
    connect(socket(), SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    disconnect(socket(), SIGNAL(readyRead()), &move, SLOT(readyRead()));
    connect(socket(), SIGNAL(disconnected()), this, SLOT(disconnected()));
    disconnect(socket(), SIGNAL(disconnected()), &move, SLOT(disconnected()));
    connect(this, SIGNAL(response(QString)), this, SLOT(processResponse(QString)), Qt::DirectConnection);
}

/*!
 * \brief Create a new ConnectionHandler.
 * \param ID Identification number of the connecting socket.
 * \param parent The calling TcpServer.
 */
ConnectionHandler::ConnectionHandler(qintptr socketDescriptor,
                                     std::vector<ConnectionHandler>& clients,
                                     QObject *parent)
    : SocketListener(socketDescriptor, parent), clients(clients)
{
    qDebug() << "Opened a new ConnectionHandler";
    connect(socket(), SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(this, SIGNAL(response(QString)), this, SLOT(processResponse(QString)), Qt::DirectConnection);
}

ConnectionHandler::~ConnectionHandler()
{
    disconnect(this, SIGNAL(response(QString)), this, SLOT(processResponse(QString)));
}

/*!
 * \brief Called when a client disconnects from the Server.
 */
void ConnectionHandler::disconnected()
{
    qDebug() << socket() << " Disconnected";
    socket()->deleteLater();
    emit disconnected(*this);
}

void ConnectionHandler::propogate(QString message)
{
    for (ConnectionHandler &h : clients)
        h.send(message);
}

void ConnectionHandler::processResponse(QString cmd)
{
    NetworkTask *task = new NetworkTask(*this, cmd, clients);
    connect(task, SIGNAL(result(QString)), this, SLOT(taskResult(QString)));
    QThreadPool::globalInstance()->start(task);
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

    connect(socket(), SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    disconnect(socket(), SIGNAL(readyRead()), &move, SLOT(readyRead()));
    connect(socket(), SIGNAL(disconnected()), this, SLOT(disconnected()));
    disconnect(socket(), SIGNAL(disconnected()), &move, SLOT(disconnected()));

    return *this;
}
