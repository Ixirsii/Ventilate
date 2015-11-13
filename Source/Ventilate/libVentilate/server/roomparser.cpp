/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#include "roomparser.h"
#include <QString>
#include <QDataStream>
#include <QUuid>
#include "../account.h"
#include "../chatroom.h"
#include "../message.h"
#include "connectionhandler.h"
#include "../database/chatroomdatabase.h"
#include "../database/messagedatabase.h"

RoomParser::RoomParser(QList<ConnectionHandler*>& clientList)
    : clientList(clientList)
{
}

RoomParser::~RoomParser()
{
}

void RoomParser::add(const ConnectionHandler& handler, QDataStream& stream)
{
    QString username;
    QUuid roomID;
    stream >> username >> roomID;
    ChatRoomDatabase db;
    ChatRoom room = db.find(roomID);
    room.addUser(username);
    handler.write(ACCEPT);
}

void RoomParser::create(const ConnectionHandler& handler, QDataStream& stream)
{
    QString roomName;
    QString owner;
    stream >> roomName >> owner;
    ChatRoom room(owner, roomName);
    ChatRoomDatabase db;
    if (db.add(room))
        handler.write(ACCEPT);
    else
        handler.write(REJECT);
}

void RoomParser::history(const ConnectionHandler& handler, QDataStream& stream)
{
    QString cmd;
    stream >> cmd;
    // Need to do something if we receive a list
    if (cmd != LIST)
        return;
    QUuid roomID;
    quint32 offset;
    stream >> roomID >> offset;
    MessageDatabase db;
    QList<Message> history = db.getMessages(roomID, offset);
    QString hisstr = ROOM + " " + HISTORY + " ";
    for (Message msg : history)
        hisstr = hisstr.append(msg.getMessage()).append(LIST_SEPARATOR);
    handler.write(hisstr);
}

void RoomParser::join(const ConnectionHandler& handler, QDataStream& stream)
{
    QUuid roomID;
    QString username;
    stream >> roomID >> username;
    ChatRoomDatabase db;
    ChatRoom room = db.find(roomID);
    room.addUser(username);
    handler.write(ACCEPT);
}

void RoomParser::leave(const ConnectionHandler& handler, QDataStream& stream)
{
    QUuid roomID;
    QString username;
    stream >> roomID >> username;
    ChatRoomDatabase db;
    ChatRoom room = db.find(roomID);
    room.removeUser(username);
    handler.write(ACCEPT);
}

void RoomParser::list(const ConnectionHandler& handler, QDataStream& stream)
{
    QString cmd;
    stream >> cmd;
    // Need to do something if we receive a list
    if (cmd != LIST)
        return;
    ChatRoomDatabase db;
    QList<ChatRoom> rooms = db.getAll();
    QString roomstr = ROOM + " " + LIST + " ";
    for (ChatRoom room : rooms)
        roomstr = roomstr.append(room.getName()).append(LIST_SEPARATOR);
    handler.write(roomstr);
}

void RoomParser::message(QDataStream& stream)
{
    QUuid messageID;
    QUuid roomID;
    QDateTime time;
    QString sender;
    QString message;
    stream >> messageID >> roomID >> time >> sender >> message;
    Message msg(messageID, roomID, time, sender, message);
    MessageDatabase db;
    db.add(msg);
    propogateMessage(msg);
}

void RoomParser::mode(const ConnectionHandler& handler, QDataStream& stream)
{
    // Do nothing, not enough time to implement this
}

void RoomParser::parse(const ConnectionHandler& handler, QDataStream& stream)
{
    QString cmd;
    stream >> cmd;
    /* Try to order these in most common first so we're not spending excess
     * time doing unnecessary string comparisons. */
    if (cmd == MESSAGE)
        message(stream);
    else if (cmd == JOIN)
        join(handler, stream);
    else if (cmd == LEAVE)
        leave(handler, stream);
    else if (cmd == ADD)
        add(handler, stream);
    else if (cmd == HISTORY)
        history(handler, stream);
    else if (cmd == LIST)
        list(handler, stream);
    else if (cmd == CREATE)
        create(handler, stream);
    else if (cmd == DELETE)
        remove(handler, stream);
    else if (cmd == MODE)
        mode(handler, stream);
}

void RoomParser::propogateMessage(const Message& message)
{
    for (ConnectionHandler* handler : clientList) {
        QString command(ROOM);
        command.append(" ").append(MESSAGE).append(" ");
        command.append(message.getSanitizedMessage());
        handler->write(command);
    }
}


void RoomParser::remove(const ConnectionHandler& handler, QDataStream& stream)
{
    QUuid roomID;
    QString username;
    QByteArray phash;
    stream >> roomID >> username >> phash;
    if (!Account::authenticateUser(username, phash)) {
        handler.write(REJECT + " " + INVALID_PASSWORD);
        return;
    }
    ChatRoomDatabase db;
    ChatRoom room = db.find(roomID);
    if (db.remove(room))
        handler.write(ACCEPT);
    else
        handler.write(REJECT + " " + GENERIC_ERROR);
}
