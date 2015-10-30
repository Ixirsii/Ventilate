#include "server.h"
#include <QDataStream>
#include <QIODevice>
#include <QString>
#include "connectionhandler.h"


const QString Server::PASSWORD = "PASSWORD";
const QString Server::CHANGE_PASSWORD_REQUEST = PASSWORD + " RESET";
const QString Server::CREATE_ACCOUNT_REQUEST = PASSWORD + " CHANGE";
const QString Server::LOGIN = "LOGIN";
const QString Server::PEER = "PEER";
const QString Server::PEER_LIST = PEER + " LIST";
const QString Server::PEER_LIST_REQUEST = PEER_LIST + " REQUEST";

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
 * \brief Add a client to the list of connected clients.
 * \param socketDescriptor
 * \param clientAddress
 */
void Server::connectClient(qintptr socketDescriptor, QHostAddress clientAddress)
{
    connectedClients.insert(socketDescriptor, clientAddress);
}

/*!
 * \brief Create a new account for a user
 */
void Server::createAccount()
{

}

void Server::disconnectClient(qintptr socketDescriptor)
{
    qDebug() << connectedClients.remove(socketDescriptor);
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


void Server::onClientRequest(const ConnectionHandler& handler, QString& request)
{
    if (request.startsWith(Server::PEER))
        parsePeerCommand(handler, request);
}


void Server::parsePeerCommand(const ConnectionHandler &handler, QString& request)
{
    if (request.startsWith(Server::PEER_LIST_REQUEST))
        sendPeerList(handler);
}


void Server::sendPeerList(const ConnectionHandler& handler)
{
    QString list = serializePeerList();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    // Reserve space for size of block
    out << (quint16) 0;
    out << list;
    // Seek back to begining of block
    out.device()->seek(0);
    // Insert size of block at beginning
    out << (quint16) (block.size() - sizeof(quint16));
    handler.sendToClient(block);
}


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


void Server::startServer() {
    int port = 37377;

    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "Failed to start server";
    } else {
        qDebug() << "Listening on port " << port;
    }
}
