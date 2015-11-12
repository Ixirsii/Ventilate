/*! \file
 * \author Ryan Porterfield
 * \since 2015-11-11
 * \copyright BSD 3 Clause
 */

#include "messagedatabase.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <message.h>

MessageDatabase::MessageDatabase()
{
}

MessageDatabase::~MessageDatabase()
{
}

bool MessageDatabase::add(const Message& elem)
{
    qDebug() << "Adding row to table" << elem.getMessage();
    db.transaction();
    QSqlQuery query(db);
    query.prepare("INSERT INTO " + MESSAGE_TABLE +
                  "(" + ID_KEY + ", " + ROOM_KEY + ", " + DATE_KEY  + ", "
                  + MESSAGE_KEY + ", "  + NAME_KEY + ")"
                  + " VALUES(?, ?, ?, ?, ?);");
    query.addBindValue(elem.getUUID());
    query.addBindValue(elem.getRoomID());
    query.addBindValue(elem.getTimeStamp());
    query.addBindValue(elem.getMessage());
    query.addBindValue(elem.getUsername());
    bool flag = runQuery(query);
    db.commit();
    return flag;
}

Message MessageDatabase::buildFromQuery(const QSqlQuery &query) const
{
    QUuid id = query.value(ID_KEY).toByteArray();
    QUuid room = query.value(ROOM_KEY).toByteArray();
    QDateTime date = query.value(DATE_KEY).toDateTime();
    QString message = query.value(MESSAGE_KEY).toString();
    QString username = query.value(NAME_KEY).toString();
    return std::move(Message(id, room, date, username, message));
}

Message MessageDatabase::find(const QUuid& id)
{
    return std::move(DatabaseInterface::find(id, MESSAGE_TABLE));
}

QList<Message> MessageDatabase::getAll()
{
    return std::move(DatabaseInterface::getAll(MESSAGE_TABLE));
}

QList<Message> MessageDatabase::getMessages(const QUuid& roomID, quint32 start)
{
    qDebug() << "Getting Messages from database";
    db.transaction();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + MESSAGE_TABLE + " WHERE " + ROOM_KEY
                  + " = ? ORDER BY " + DATE_KEY + " DESC LIMIT " + RETURN_RANGE + " OFFSET "
                  + QString::number(start) + ";");
    query.addBindValue(roomID);
    runQuery(query);
    db.commit();
    QList<Message> list;
    while (query.next())
        list.append(buildFromQuery(query));
    return std::move(list);
}

bool MessageDatabase::remove(const Message& elem)
{
    return DatabaseInterface::remove(elem.getUUID(), MESSAGE_TABLE);
}

