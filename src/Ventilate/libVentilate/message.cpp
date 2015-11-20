/*! \file
 * \brief Define functionality for Message class.
 * \author Ryan Porterfield
 * \since 2015-10-30
 * \copyright 2015-11-10
 */

#include "message.h"
#include <memory>
#include <QDateTime>
#include <QDebug>
#include <QUuid>
#include "server/commandparser.h"

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

Message Message::fromString(QString serialized)
{
    qDebug() << "Buiding Message from: " << serialized;
    QStringList tokens = serialized.split(CommandParser::SEP);
    QUuid uuid(tokens.at(0));
    QUuid roomID(tokens.at(1));
    QDateTime dt = QDateTime::fromString(tokens.at(2), Qt::ISODate);
    QString sender = tokens.at(3);
    QString message = tokens.at(4);
    Message msg(uuid, roomID, dt, sender, message);

    return std::move(msg);
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

QString Message::toString() const
{
    QString msg = uuid.toString() + CommandParser::SEP;
    msg += roomID.toString() + CommandParser::SEP;
    msg += timestamp.toString(Qt::ISODate) + CommandParser::SEP;
    msg += username + CommandParser::SEP;
    msg += message;
    return msg;
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

