#include "server.h"
#include "connectionhandler.h"


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
 * \brief Change the password for an account
 */
void Server::changePassword()
{
}

/*!
 * \brief Create a new account for a user
 */
void Server::createAccount()
{

}

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

void Server::startServer() {
    int port = 37377;

    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "Failed to start server";
    } else {
        qDebug() << "Listening on port " << port;
    }
}
