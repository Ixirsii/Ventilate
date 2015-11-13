/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-10-30
 * \copyright 2015-11-10
 */

#include "server.h"
#include <QDataStream>
#include <QIODevice>
#include <QList>
#include <QString>
#include <QStringList>
#include "accountparser.h"
#include "commandparser.h"
#include "passwordparser.h"
#include "peerparser.h"
#include "roomparser.h"

/*!
 * \brief Create a new Server.
 * \param parent The object creating the parent.
 */
Server::Server(QObject *parent)
    : QTcpServer(parent), peerParser(clientList), roomParser(clientList)
{
}

/*!
 * \brief Destroy a Server
 */
Server::~Server()
{
}


void Server::disconnectClient(ConnectionHandler* handler)
{
    clientList.removeOne(handler);
}


/*!
 * \brief Server::incomingConnection
 * \param socketDescriptor
 */
void Server::incomingConnection(qintptr socketDescriptor) {
    qDebug() << "Connecting to " << socketDescriptor;
    ConnectionHandler *handler = new ConnectionHandler(socketDescriptor, this);
    clientList.append(handler);
    connect(handler, SIGNAL(finished()), handler, SLOT(deleteLater()));
    handler->start();
}


const QList<ConnectionHandler*>& Server::getClientList() const
{
    return clientList;
}


/*!
 * \brief Server::onClientRequest
 * \param handler
 * \param request
 */
void Server::onClientRequest(const ConnectionHandler& handler, QDataStream& stream)
{
    QString cmd;
    stream >> cmd;
    qDebug() << "Got string: " << cmd << " from stream";
    if (cmd == CommandParser::ROOM)
        roomParser.parse(handler, stream);
    else if (cmd == CommandParser::ACCOUNT || cmd == CommandParser::LOGIN)
        accountParser.parse(handler, stream);
    else if (cmd == CommandParser::PEER)
        peerParser.parse(handler, stream);
    else if (cmd == CommandParser::PASSWORD)
        passwordParser.parse(handler, stream);
    // Drop incorrectly formatted requests
}


/*!
 * \brief Server::startServer
 */
void Server::startServer() {
    int port = 37377;

    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "Failed to start server";
    } else {
        qDebug() << "Listening on port " << port;
    }
}

/* ************************************************************************* *
 *                                    EOF                                    *
 * ************************************************************************* */
