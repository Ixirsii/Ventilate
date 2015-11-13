/*! \file
 * \brief Define functionality for Message class.
 * \author Ryan Porterfield
 * \since 2015-10-30
 * \copyright 2015-11-10
 */

#include "message.h"
#include <memory>
#include <QDateTime>
#include <QUuid>

Message::Message(const Message &copy)
    : QObject(copy.parent()), uuid(copy.message), roomID(copy.roomID),
      timestamp(copy.timestamp), username(copy.username), message(copy.message)
{
}

Message::Message(Message&& v)
    : QObject(v.parent()), uuid(std::move(v.uuid)), roomID(std::move(v.roomID)),
      timestamp(std::move(v.timestamp)), username(std::move(v.username)),
      message(std::move(v.message))
{
    v.setParent(nullptr);
}

Message::Message(const QUuid& roomID, const QString& username,
                 const QString& message, QObject* parent)
    : QObject(parent), uuid(QUuid::createUuid()), roomID(roomID),
      timestamp(QDateTime::currentDateTime()), username(username),
      message(message)
{
}

Message::Message(const QUuid& uuid, const QUuid& roomID,
                 const QDateTime& timestamp, const QString& username,
                 const QString& message, QObject* parent)
    : QObject(parent), uuid(uuid), roomID(roomID), timestamp(timestamp),
      username(username), message(message)
{
}

QString Message::getFormattedMessage() const
{
    QString msgstr = getHeader();
    msgstr = msgstr.append(message);
    return msgstr;
}

QString Message::getHeader() const
{
    QString msgstr("[");
    msgstr.append(timestamp.time().toString()).append("] ").append(username);
    return msgstr.append(": ");
}


QString Message::getSanitizedMessage() const
{
    QString msgstr = getHeader();
    QString clone(message);
    clone.replace(QChar('\\'), QString("\\\\"));
    return msgstr.append(clone);
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

