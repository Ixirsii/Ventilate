/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-10-30
 * \copyright 2015-11-10
 */

#include "chatroom.h"
#include <memory>
#include <QUuid>
#include "database/chatroomdatabase.h"
#include "database/messagedatabase.h"
#include "database/moddatabase.h"
#include "database/userdatabase.h"

ChatRoom::ChatRoom(const ChatRoom& copy)
    : QObject(copy.parent()), uuid(copy.uuid), owner(copy.owner),
      name(copy.name), moderators(copy.moderators), users(copy.users),
      messages(copy.messages)
{
}


ChatRoom::ChatRoom(ChatRoom&& move)
    : QObject(move.parent()), uuid(std::move(move.uuid)),
      owner(std::move(move.owner)), name(std::move(move.name)),
      moderators(std::move(move.moderators)), users(std::move(move.users)),
      messages(std::move(move.messages))
{
    move.setParent(nullptr);
}

ChatRoom::ChatRoom(const QString& owner, const QString& name)
    : uuid(QUuid::createUuid()), owner(owner), name(name)
{
}

ChatRoom::ChatRoom(const QUuid& uuid, const QString& owner, const QString& name)
    : uuid(uuid), owner(owner), name(name)
{
}

void ChatRoom::addMessage(const Message& message)
{
    messages.append(message);
}

void ChatRoom::addMessages(const QList<Message>& messages)
{
    for (Message msg : messages)
        addMessage(msg);
}

void ChatRoom::addModerator(const QString& mod)
{
    ModDatabase db;
    moderators.append(mod);
    db.add(mod, uuid);
}

void ChatRoom::addModerators(const QList<QString>& mods)
{
    for (QString mod : mods)
        addModerator(mod);
}

void ChatRoom::addUser(const QString& user)
{
    UserDatabase db;
    users.append(user);
    db.add(user, uuid);
}

void ChatRoom::addUsers(const QList<QString>& users)
{
    for (QString user : users)
        addUser(user);
}

void ChatRoom::getHistory()
{
    MessageDatabase db;
    QList<Message> history = db.getMessages(uuid, messages.size());
    QList<Message>::iterator iter = history.end() - 1;
    for (; iter != history.begin(); --iter)
        messages.prepend(*iter);
}

QString ChatRoom::getMessages()
{
    QString all_msgs = "";
    for (Message msg : messages) {
        all_msgs.append(serializeMessage(msg));
        all_msgs.append("\n");
    }
    return all_msgs;
}

const QList<QString>& ChatRoom::getModerators() const
{
    return moderators;
}

const QString& ChatRoom::getName() const
{
    return name;
}

const QString& ChatRoom::getOwner() const
{
    return owner;
}

const QUuid& ChatRoom::getUUID() const
{
    return uuid;
}

const QList<QString>& ChatRoom::getUsers() const
{
    return users;
}

void ChatRoom::removeModerator(const QString& mod)
{
    ModDatabase db;
    moderators.removeOne(mod);
    db.remove(mod, uuid);
}

void ChatRoom::removeUser(const QString& user)
{
    UserDatabase db;
    users.removeOne(user);
    db.remove(user, uuid);
}

QString ChatRoom::serializeMessage(const Message& message)
{
    QString msg_str = "[" + message.getTimeStamp().toString() + "] ";
    msg_str.append(message.getUsername());
    msg_str.append(": ");
    msg_str.append(message.getMessage());
    return msg_str;
}


ChatRoom& ChatRoom::operator=(const ChatRoom& copy)
{
    QObject::setParent(copy.parent());
    uuid = copy.uuid;
    owner = copy.owner;
    name = copy.name;
    moderators = copy.moderators;
    users = copy.users;
    messages = copy.messages;
    return *this;
}

ChatRoom& ChatRoom::operator=(ChatRoom&& move)
{
    QObject::setParent(move.parent());
    move.setParent(nullptr);
    uuid = std::move(move.uuid);
    owner = std::move(move.owner);
    name = std::move(move.name);
    moderators = std::move(move.moderators);
    users = std::move(move.users);
    messages = std::move(move.messages);
    return *this;
}

QDataStream& operator<<(QDataStream& out, const ChatRoom& room)
{
    out << room.getUUID();
    out << room.getName();
    out << room.getOwner();
    return out;
}

QDataStream& operator>>(QDataStream& in, ChatRoom& room)
{
    in >> room.uuid;
    in >> room.name;
    in >> room.owner;
    return in;
}
