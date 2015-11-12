/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#include "roomparser.h"
#include <QString>
#include <QStringList>
#include <QUuid>
#include "../chatroom.h"
#include "../message.h"
#include "connectionhandler.h"
#include "server.h"
#include "../database/chatroomdatabase.h"
#include "../database/messagedatabase.h"

RoomParser::RoomParser(Server& server)
{

}

RoomParser::~RoomParser()
{
}

void RoomParser::add(const ConnectionHandler& handler, QStringList& command)
{
    QString username = command.at(2);
    QUuid roomID(command.at(3));
    ChatRoomDatabase db;
    ChatRoom room = db.find(roomID);
    room.addUser(username);
    handler.write(ACCEPT);
}

void RoomParser::create(const ConnectionHandler& handler, QStringList& command)
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

void RoomParser::history(const ConnectionHandler& handler, QStringList& command)
{
    QString cmd = command.at(2);
    // Need to do something if we receive a list
    if (cmd != LIST || command.length() < 4)
        return;
    QUuid roomID(command.at(3));
    quint32 offset = command.at(4).toUInt();
    MessageDatabase db;
    QList<Message> history = db.getMessages(roomID, offset);
    QString hisstr = ROOM + " " + HISTORY + " ";
    for (Message msg : history)
        hisstr.append(msg.getMessage()).append(LIST_SEPARATOR);
    handler.write(hisstr);
}

void RoomParser::join(const ConnectionHandler& handler, QStringList& command)
{
    QUuid roomID(command.at(2));
    QString username = command.at(3);
    ChatRoomDatabase db;
    ChatRoom room = db.find(roomID);
    room.addUser(username);
    handler.write(ACCEPT);
}

void RoomParser::leave(const ConnectionHandler& handler, QStringList& command)
{
    QUuid roomID(command.at(2));
    QString username = command.at(3);
    ChatRoomDatabase db;
    ChatRoom room = db.find(roomID);
    room.removeUser(username);
    handler.write(ACCEPT);
}

void RoomParser::list(const ConnectionHandler& handler, QStringList& command)
{
    QString cmd = command.at(2);
    // Need to do something if we receive a list
    if (cmd != LIST || command.length() < 3)
        return;
    ChatRoomDatabase db;
    QList<ChatRoom> rooms = db.getAll();
    QString roomstr = ROOM + " " + LIST + " ";
    for (ChatRoom room : rooms)
        roomstr.append(room.getName()).append(LIST_SEPARATOR);
}

void RoomParser::message(const ConnectionHandler& handler, QStringList& command)
{
    QUuid roomID(command.at(2));
    QDateTime time(command.at(3));
    QString sender = command.at(4);
    QString message = command.at(5);
    Message msg(roomID, time, sender, message);
    MessageDatabase db;
    db.add(msg);
}

void RoomParser::mode(const ConnectionHandler& handler, QStringList& command)
{
    // Do nothing, not enough time to implement this
}

void RoomParser::parse(const ConnectionHandler& handler, QStringList& command)
{
    QString cmd = command.at(1);
    /* Try to order these in most common first so we're not spending excess
     * time doing unnecessary string comparisons. */
    if (cmd == MESSAGE)
        message(handler, command);
    else if (cmd == JOIN)
        join(handler, command);
    else if (cmd == LEAVE)
        leave(handler, command);
    else if (cmd == ADD)
        add(handler, command);
    else if (cmd == HISTORY)
        history(handler, command);
    else if (cmd == LIST)
        list(handler, command);
    else if (cmd == CREATE)
        create(handler, command);
    else if (cmd == DELETE)
        remove(handler, command);
    else if (cmd == MODE)
        mode(handler, command);
}

void RoomParser::remove(const ConnectionHandler& handler, QStringList& command)
{
    QUuid roomID(command.at(2));
    QString username = command.at(3);
    QByteArray phash(command.at(4));
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
