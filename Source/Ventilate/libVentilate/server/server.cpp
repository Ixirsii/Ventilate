/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-10-30
 * \copyright 2015-11-10
 */

#include "server.h"
#include <QDataStream>
#include <QIODevice>
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
    : QTcpServer(parent)
{
}

/*!
 * \brief Destroy a Server
 */
Server::~Server()
{
}


/*!
 * \brief Add a client to the list of connected clients.
 * \param socketDescriptor
 * \param clientAddress
 */
void Server::connectClient(qintptr socketDescriptor, QHostAddress clientAddress)
{
    connectedClients.insert(socketDescriptor, clientAddress);
}


/*!
 * \brief Server::disconnectClient
 * \param socketDescriptor
 */
void Server::disconnectClient(qintptr socketDescriptor)
{
    qDebug() << connectedClients.remove(socketDescriptor);
}


/*!
 * \brief Server::incomingConnection
 * \param socketDescriptor
 */
void Server::incomingConnection(qintptr socketDescriptor) {
    qDebug() << "Connecting to " << socketDescriptor;
    ConnectionHandler *handler = new ConnectionHandler(socketDescriptor, this);
    connect(handler, SIGNAL(finished()), handler, SLOT(deleteLater()));
    handler->start();
}

/*!
 * \brief Server::login
 */
void Server::login()
{

}


/*!
 * \brief Server::onClientRequest
 * \param handler
 * \param request
 */
void Server::onClientRequest(const ConnectionHandler& handler, QString& request)
{
    QStringList tokens = request.split(" ");
    QString cmd = tokens.at(0);
    if (cmd == CommandParser::ROOM)
        RoomParser(*this).parse(handler, tokens);
    else if (cmd == CommandParser::ACCOUNT || cmd == CommandParser::LOGIN)
        AccountParser(*this).parse(handler, tokens);
    else if (cmd == CommandParser::PEER)
        PeerParser(*this).parse(handler, tokens);
    else if (cmd == CommandParser::PASSWORD)
        PasswordParser(*this).parse(handler, tokens);
    // Drop incorrectly formatted requests
}


/*!
 * \brief Server::serializePeerList
 * \return
 */
QString Server::serializePeerList()
{
    QString list = PEER_LIST;
    QHash<qintptr, QHostAddress>::iterator iter;
    for (iter = connectedClients.begin(); iter != connectedClients.end(); ++iter) {
        list = list.append(" ");
        list = list.append(iter.value().toString());
    }
    return list;
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
