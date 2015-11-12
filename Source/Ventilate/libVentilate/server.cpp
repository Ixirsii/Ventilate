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
#include "account.h"
#include "accountdatabase.h"
#include "chatroom.h"
#include "chatroomdatabase.h"
#include "commands.h"
#include "connectionhandler.h"
#include "message.h"
#include "messagedatabase.h"

/* ************************************************************************* *
 *                            Command Definitions                            *
 * ************************************************************************* */
const QString ACCEPT = "ACCEPT";
const QString ACCOUNT = "ACCOUNT";
const QString CREATE = "CREATE";
const QString DELETE = "DELETE";
const QString HISTORY = "HISTORY";
const QString LIST = "LIST";
const QString LOGIN = "LOGIN";
const QString PASSWORD = "PASSWORD";
const QString PEER = "PEER";
const QString REJECT = "REJECT";
const QString REQUEST = "REQUEST";
const QString ROOM = "ROOM";

const QString ACCOUNT_CREATE = ACCOUNT + " " + CREATE;
const QString ACCOUNT_DELETE = ACCOUNT + " " + DELETE;
const QString PASSWORD_CHANGE = PASSWORD + " CHANGE";
const QString PASSWORD_RESET = PASSWORD + " RESET";
const QString PEER_LIST = PEER + " " + LIST;
const QString PEER_LIST_REQUEST = PEER_LIST + " " + REQUEST;
const QString ROOM_ADD = ROOM + " ADD";
const QString ROOM_CREATE = ROOM + " " + CREATE;
const QString ROOM_DELETE = ROOM + " " + DELETE;
const QString ROOM_HISTORY = ROOM + " " + HISTORY;
const QString ROOM_HISTORY_REQUEST = ROOM_HISTORY + " " + REQUEST;
const QString ROOM_JOIN = ROOM + " JOIN";
const QString ROOM_LEAVE = ROOM + " LEAVE";
const QString ROOM_LIST = ROOM + " " + LIST;
const QString ROOM_LIST_REQUEST = ROOM_LIST + " " + REQUEST;
const QString ROOM_MESSAGE = ROOM + " MESSAGE";
const QString ROOM_MODE = ROOM + " MODE";


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

void Server::changePassword(const ConnectionHandler& handler, QString& command)
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


void Server::createAccount(const ConnectionHandler& handler, QString& command)
{

}

void Server::createRoom(const ConnectionHandler& handler, QString& command)
{
    QStringList tokens = command.split(" ");
    QString roomName = tokens.at(2);
    QString owner = tokens.at(3);
    ChatRoom room(owner, roomName);
    ChatRoomDatabase db;
    if (db.add(room))
        handler.write(ACCEPT);
    else
        handler.write(REJECT);
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
    if (request.startsWith(ROOM))
        parseRoomCommand(handler, request);
    else if (request.startsWith(ACCOUNT))
        parseAccountCommand(handler, request);
    else if (request.startsWith(PEER))
        parsePeerCommand(handler, request);
}


void Server::parseAccountCommand(const ConnectionHandler& handler, QString& command)
{

}


void Server::parsePeerCommand(const ConnectionHandler &handler, QString& request)
{
    if (request.startsWith(PEER_LIST_REQUEST))
        sendPeerList(handler);
}


void Server::parseRoomCommand(const ConnectionHandler& handler, QString& command)
{
    if (request.startsWith(ROOM_CREATE))
        createChatRoom(handler, command);

}


void Server::sendPeerList(const ConnectionHandler& handler)
{
    QString list = serializePeerList();
    handler.write(list);
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

/* ************************************************************************* *
 *                                    EOF                                    *
 * ************************************************************************* */
