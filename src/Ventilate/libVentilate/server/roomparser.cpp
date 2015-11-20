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

void RoomParser::add(const ConnectionHandler& handler, QStringList& tokens)
{
    QString username = tokens.at(2);
    QUuid roomID(tokens.at(3));
    ChatRoomDatabase db;
    ChatRoom room = db.find(roomID);
    room.addUser(username);
    handler.write(ACCEPT);
}

void RoomParser::create(const ConnectionHandler& handler, QStringList& tokens)
{
    QString roomName = tokens.at(2);
    QString owner = tokens.at(3);
    ChatRoom room(owner, roomName);
    ChatRoomDatabase db;
    if (db.add(room))
        handler.write(ACCEPT);
    else
        handler.write(REJECT);
}

void RoomParser::get(const ConnectionHandler& handler, QStringList& tokens)
{
    ChatRoomDatabase db;
    QString name = tokens.at(2);
    ChatRoom chat = db.find(name);
    QString cmd = ROOM + " " + SEND + " " + chat.toString();
    handler.write(cmd);
}

void RoomParser::history(const ConnectionHandler& handler, QStringList& tokens)
{
    QString cmd = tokens.at(1);
    // Need to do something if we receive a list
    if (cmd != LIST)
        return;
    QUuid roomID(tokens.at(3));
    quint32 offset = tokens.at(4).toInt();
    MessageDatabase db;
    QList<Message> history = db.getMessages(roomID, offset);
    QString hisstr = ROOM + " " + HISTORY + " ";
    for (Message msg : history)
        hisstr = hisstr.append(msg.getMessage()).append(LIST_SEPARATOR);
    handler.write(hisstr);
}

void RoomParser::join(const ConnectionHandler& handler, QStringList& tokens)
{
    QUuid roomID(tokens.at(2));
    QString username = tokens.at(3);
    ChatRoomDatabase db;
    ChatRoom room = db.find(roomID);
    room.addUser(username);
    handler.write(ACCEPT);
}

void RoomParser::leave(const ConnectionHandler& handler, QStringList& tokens)
{
    QUuid roomID(tokens.at(2));
    QString username = tokens.at(3);
    ChatRoomDatabase db;
    ChatRoom room = db.find(roomID);
    room.removeUser(username);
    handler.write(ACCEPT);
}

void RoomParser::list(const ConnectionHandler& handler, QStringList& tokens)
{
    QString cmd = tokens.at(2);
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

void RoomParser::message(QStringList& tokens)
{
    QUuid messageID(tokens.at(2));
    QUuid roomID(tokens.at(3));
    QDateTime time = QDateTime::fromString(tokens.at(4));
    QString sender = tokens.at(5);
    QString message = tokens.at(6);
    Message msg(messageID, roomID, time, sender, message);
    MessageDatabase db;
    db.add(msg);
    propogateMessage(msg);
}

void RoomParser::mode(const ConnectionHandler& handler, QStringList& tokens)
{
    // Do nothing, not enough time to implement this
}

void RoomParser::parse(const ConnectionHandler& handler, QStringList& tokens)
{
    QString cmd = tokens.at(1);
    /* Try to order these in most common first so we're not spending excess
     * time doing unnecessary string comparisons. */
    if (cmd == MESSAGE)
        message(tokens);
    else if (cmd == JOIN)
        join(handler, tokens);
    else if (cmd == LEAVE)
        leave(handler, tokens);
    else if (cmd == ADD)
        add(handler, tokens);
    else if (cmd == HISTORY)
        history(handler, tokens);
    else if (cmd == LIST)
        list(handler, tokens);
    else if (cmd == GET)
        get(handler, tokens);
    else if (cmd == CREATE)
        create(handler, tokens);
    else if (cmd == DELETE)
        remove(handler, tokens);
    else if (cmd == MODE)
        mode(handler, tokens);
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


void RoomParser::remove(const ConnectionHandler& handler, QStringList& tokens)
{
    QUuid roomID(tokens.at(2));
    QString username = tokens.at(3);
    QByteArray phash;
    phash.append(tokens.at(4));
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
