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

#include "socket.h"
#include <QByteArray>
#include <QDataStream>
#include <QPlainTextEdit>
#include <QString>
#include <QThread>
#include "mainwindow.h"


/*!
 * \brief Socket::Socket
 * \param host
 * \param port
 * \param parent
 */
Socket::Socket(QString host, qint16 port, MainWindow& mw, QObject *parent)
    : mw(mw), QObject(parent)
{
    socket = new QTcpSocket(this);
    socket->connectToHost(host, port);
    connect(socket, &QTcpSocket::readyRead, this, &Socket::listen);
}


/*!
 * \brief Socket::~Socket
 */
Socket::~Socket()
{
    socket->deleteLater();
}

/*!
 * \brief Socket::listen
 */
void Socket::listen()
{
    static quint16 blockSize = 0;
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
    // Debugging!
    mw.findChild<QPlainTextEdit*>("ptxtMessageBox")->appendPlainText(data);
}

/*!
 * \brief Socket::send
 * \param data
 */
void Socket::send(QString data) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << (quint16) 0;
    out << data;
    out.device()->seek(0);
    out << (quint16) (block.size() - sizeof(quint16));
    socket->write(block);
}
