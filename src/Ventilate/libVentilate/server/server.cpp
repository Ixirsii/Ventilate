/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-10-30
 * \copyright 2015-11-10
 */

#include "server.h"
#include <algorithm>
#include <vector>
#include <QDataStream>
#include <QIODevice>
#include <QList>
#include <QString>
#include <QStringList>
#include "database/database.h"
#include "server/commandparser.h"

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

void Server::disconnected(ConnectionHandler& handler)
{
    std::vector<ConnectionHandler>::iterator iter;
    iter = std::find(clients.begin(), clients.end(), handler);
    disconnect(&(*iter), SIGNAL(disconnected(ConnectionHandler&)),
            this, SLOT(disconnected(ConnectionHandler&)));
    clients.erase(iter);
}

/*!
 * \brief Server::incomingConnection
 * \param socketDescriptor
 */
void Server::incomingConnection(qintptr socketDescriptor) {
    qDebug() << "Connecting to " << socketDescriptor;
    ConnectionHandler handler(socketDescriptor, clients);
    connect(&handler, SIGNAL(disconnected(ConnectionHandler&)),
            this, SLOT(disconnected(ConnectionHandler&)));
    clients.push_back(std::move(handler));
}

/*!
 * \brief Server::startServer
 */
void Server::startServer() {
    int port = 37377;

    Database::init();
    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "Failed to start server";
    } else {
        qDebug() << "Listening on port " << port;
    }
}

/* ************************************************************************* *
 *                                    EOF                                    *
 * ************************************************************************* */
