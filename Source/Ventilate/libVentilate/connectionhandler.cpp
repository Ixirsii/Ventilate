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

#include "connectionhandler.h"
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include "server.h"

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
    server->disconnectClient(socketDescriptor);
    socket->deleteLater();
    exit(0);
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
    Server *server = static_cast<Server*>(this->parent());
    server->connectClient(socketDescriptor, socket->peerAddress());
    qDebug() << "peer address: " << socket->peerAddress();
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
    QString data;
    in >> data;
    blockSize = 0;
    qDebug() << data;
    Server *server = static_cast<Server*>(parent());
    server->onClientRequest(*this, data);
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

void ConnectionHandler::write(QString data)
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
