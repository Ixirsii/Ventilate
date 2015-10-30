/* Copyright (C) 2015 Ryan Porterfield
 *
 * This file defines all networking commands.
 *
 * $QT_BEGIN_LICENSE:BSD$
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of The Qt Company Ltd nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 *
 * $QT_END_LICENSE$
 */

#include "server.h"
#include <QDataStream>
#include <QIODevice>
#include <QString>
#include "commands.h"
#include "connectionhandler.h"

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
    if (request.startsWith(PEER))
        parsePeerCommand(handler, request);
}


void Server::parsePeerCommand(const ConnectionHandler &handler, QString& request)
{
    if (request.startsWith(PEER_LIST_REQUEST))
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
