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
    : id_key("id"), date_key("date"), message_key("message"),
      room_key("room"), username_key("username")
{
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS " + message_table + "("
                  + id_key + " BLOB NOT NULL UNIQUE PRIMARY KEY, "
                  + room_key + "BLOB NOT NULL"
                  + date_key + " DATETIME NOT NULL, "
                  + message_key + " TEXT NOT NULL, "
                  + username_key + " TEXT NOT NULL, "
                  + "FOREIGN KEY(" + room_key + ") REFERENCES "
                  + room_table + "(" + id_key + "), "
                  + "FOREIGN KEY(" + username_key + ") REFERENCES "
                  + account_table + "(" + username_key + "));");
    runQuery(query);
}

MessageDatabase::~MessageDatabase()
{
}

bool MessageDatabase::add(const Message& elem)
{
    qDebug() << "Adding row to table" << elem.getUUID();
    db.transaction();
    QSqlQuery query(db);
    query.prepare("INSERT INTO " + message_table +
                  "(" + id_key + ", " + room_key + ", " + date_key  + ", "
                  + message_key + ", "  + username_key + ")"
                  + " VALUES(?, ?, ?, ?, ?);");
    query.addBindValue(elem.getUUID());
    query.addBindValue(elem.getRoomID());
    query.addBindValue(elem.getTimeStamp());
    query.addBindValue(elem.getMessage());
    query.addBindValue(elem.getUsername());
    flag = runQuery(query);
    db.commit();
    return flag;
}

Message MessageDatabase::buildFromQuery(const QSqlQuery &query) const
{
    QUuid id = query.value(id_key).toByteArray();
    QUuid room = query.value(room_id).toByteArray();
    QDateTime date = query.value(date_key).toDateTime();
    QString message = query.value(message_key).toString();
    QString username = query.value(username_key).toString();
    return std::move(Message(id, room, date, username, message));
}

Message MessageDatabase::find(const QUuid& id) const
{
    return std::move(find(id, message_table));
}

QList<Message> MessageDatabase::getAll() const
{
    return std::move(getAll(message_table));
}

bool MessageDatabase::remove(const Message& elem)
{
    return remove(elem.getUUID(), message_table);
}

