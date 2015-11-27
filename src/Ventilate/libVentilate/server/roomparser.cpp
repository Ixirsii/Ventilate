/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#include "roomparser.h"
#include <QObject>
#include <QString>
#include <QStringList>
#include <QUuid>
#include "account.h"
#include "chatroom.h"
#include "message.h"
#include "connectionhandler.h"
#include "database/roomdatabase.h"
#include "database/messagedatabase.h"
#include "database/userdatabase.h"
#include "server/commandparser.h"

RoomParser::RoomParser(QObject *parent)
    : CommandParser(parent)
{
}

RoomParser::~RoomParser()
{
}

QString RoomParser::add(QStringList& tokens)
{
    QStringList::iterator iter = tokens.begin();
    QString username = *iter++;
    QUuid roomID(*iter++);
    RoomDatabase db;
    ChatRoom room = db.find(roomID);
    room.addUser(username);
    return ACCEPT;
}

Message RoomParser::buildMessage(QStringList &tokens)
{
    QStringList::iterator iter = tokens.begin();
    QUuid messageID(*iter++);
    QUuid roomID(*iter++);
    QDateTime time = QDateTime::fromString(*iter++, Qt::ISODate);
    QString sender = *iter++;
    QString message = *iter++;
    return std::move(Message(messageID, roomID, time, sender, message));
}

QString RoomParser::create(QStringList& tokens)
{
    QStringList::iterator iter = tokens.begin();
    QString roomName = *iter++;
    QString owner = *iter++;
    ChatRoom room(owner, roomName);
    RoomDatabase db;
    if (db.add(room))
        return ACCEPT;
    else
        return REJECT;
}

QString RoomParser::get(QStringList& tokens)
{
    QStringList::iterator iter = tokens.begin();
    RoomDatabase db;
    //UserDatabase udb;
    QString name = *iter++;
    ChatRoom chat = db.find(name);
    QString cmd = ROOM + SEP + SEND + SEP + chat.toString();
    return cmd;
}

QString RoomParser::history(QStringList& tokens)
{
    QStringList::iterator iter = tokens.begin();
    QString cmd = *iter++;
    // Need to do something if we receive a list
    if (cmd != LIST)
        return REJECT;
    QUuid roomID(*iter++);
    quint32 offset = (*iter++).toInt();
    MessageDatabase db;
    QList<Message> history = db.getMessages(roomID, offset);
    QString hisstr = ROOM + SEP + HISTORY + SEP;
    for (Message msg : history)
        hisstr = hisstr.append(msg.getMessage()).append(SEP);
    return hisstr;
}

bool RoomParser::inRoom(QString &username, QUuid &room)
{
    UserDatabase db;
    return db.contains(username, room);
}

QString RoomParser::join(QStringList& tokens)
{
    QStringList::iterator iter = tokens.begin();
    UserDatabase db;
    QUuid roomID(*iter++);
    QString username = *iter++;
    if (inRoom(username, roomID))
        return ACCEPT;
    if (db.add(username, roomID))
        return ACCEPT;
    else
        return REJECT + " " + CommandParser::GENERIC_ERROR;
}

QString RoomParser::leave(QStringList& tokens)
{
    QStringList::iterator iter = tokens.begin();
    QUuid roomID(*iter++);
    QString username = *iter++;
    UserDatabase db;
    if (db.remove(username, roomID))
        return ACCEPT;
    else
        return REJECT + " " + CommandParser::GENERIC_ERROR;
}

QString RoomParser::list(QStringList& tokens)
{
    QStringList::iterator iter = tokens.begin();
    QString cmd = *iter++;
    // Need to do something if we receive a list
    if (cmd != LIST)
        return REJECT;
    RoomDatabase db;
    QList<ChatRoom> rooms = db.getAll();
    QString roomstr = ROOM + SEP + LIST + SEP;
    for (ChatRoom room : rooms)
        roomstr = roomstr.append(room.getName()).append(SEP);
    return roomstr;
}

QString RoomParser::message(QStringList& tokens)
{
    Message msg = buildMessage(tokens);
    MessageDatabase db;
    db.add(msg);

    QString command(ROOM);
    command.append(SEP).append(MESSAGE).append(SEP);
    command.append(msg.toString());
    emit propogate(command);
    return ACCEPT;
}

QString RoomParser::mode(QStringList& tokens)
{
    // Do nothing, not enough time to implement this
    return REJECT;
}

QString RoomParser::parse(QString& subcmd,
                       QStringList& tokens)
{
    /* Try to order these in most common first so we're not spending excess
     * time doing unnecessary string comparisons. */
    if (subcmd == MESSAGE)
        return message(tokens);
    else if (subcmd == JOIN)
        return join(tokens);
    else if (subcmd == LEAVE)
        return leave(tokens);
    else if (subcmd == ADD)
        return add(tokens);
    else if (subcmd == HISTORY)
        return history(tokens);
    else if (subcmd == LIST)
        return list(tokens);
    else if (subcmd == GET)
        return get(tokens);
    else if (subcmd == CREATE)
        return create(tokens);
    else if (subcmd == DELETE)
        return remove(tokens);
    else if (subcmd == MODE)
        return mode(tokens);
    return REJECT + " " + GENERIC_ERROR;
}

QString RoomParser::remove(QStringList& tokens)
{
    QStringList::iterator iter = tokens.begin();
    QUuid roomID(*iter++);
    QString username = *iter++;
    QByteArray phash;
    phash.append(*iter++);
    if (!Account::authenticateUser(username, phash)) {
        return REJECT + SEP + INVALID_PASSWORD;
    }
    RoomDatabase db;
    ChatRoom room = db.find(roomID);
    if (db.remove(room))
        return ACCEPT;
    else
        return REJECT + SEP + GENERIC_ERROR;
}
