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

#include "message.h"
#include <memory>
#include <QDateTime>
#include <QUuid>

Message::Message(const Message &copy)
    : QObject(copy.parent()), message(copy.message), uuid(copy.message),
      timestamp(copy.timestamp), username(copy.username)
{
}

Message::Message(Message&& v)
    : QObject(v.parent()), message(std::move(v.message)),
      uuid(std::move(v.uuid)), timestamp(std::move(v.timestamp)),
      username(std::move(v.username))
{
    v.parent() = nullptr;
}

Message::Message(QUuid& roomID, QString& username, QString& message, QObject* parent)
    : QObject(parent), uuid(QUuid::createUuid()), roomID(roomID),
      timestamp(QDateTime::currentDateTime()), username(username),
      message(message)
{

}

Message::Message(QUuid& uuid, QUuid& roomID, QDateTime& timestamp, QString& username,
                 QString& message, QObject* parent)
    : QObject(parent), uuid(uuid), roomID(roomID), timestamp(timestamp),
      username(username), message(message)
{

}

const QString& Message::getMessage() const
{
    return message;
}

const QUuid& Message::getRoomID() const
{
    return roomID;
}

const QDateTime& Message::getTimeStamp() const
{
    return timestamp;
}

const QString& Message::getUsername() const
{
    return username;
}

const QUuid& Message::getUUID() const
{
    return uuid;
}

Message& Message::operator=(const Message& msg)
{
    uuid = msg.uuid;
    timestamp = msg.timestamp;
    message = msg.message;
    username = msg.username;
    return *this;
}

Message& Message::operator=(Message&& msg)
{
    uuid = std::move(msg.uuid);
    timestamp = std::move(msg.timestamp);
    message = std::move(msg.message);
    username = std::move(msg.username);
    return *this;
}

