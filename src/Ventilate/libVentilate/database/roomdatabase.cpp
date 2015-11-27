/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-11
 * \copyright BSD 3 Clause
 */

#include "database/roomdatabase.h"
#include <memory>
#include "message.h"
#include "messagedatabase.h"
#include "moddatabase.h"
#include "userdatabase.h"

RoomDatabase::RoomDatabase()
{
}

bool RoomDatabase::add(const ChatRoom &elem)
{
    qDebug() << "Adding row to table" << elem.getName();
    db.transaction();
    QSqlQuery query(db);
    query.prepare("INSERT INTO " + ROOM_TABLE + "(" + ID_KEY + ", "
                  + OWNER_KEY + ", "  + NAME_KEY + ")" + " VALUES(?, ?, ?);");
    query.addBindValue(elem.getUUID());
    query.addBindValue(elem.getOwner());
    query.addBindValue(elem.getName());
    bool flag = runQuery(query);
    db.commit();
    return flag;
}

ChatRoom RoomDatabase::buildFromQuery(const QSqlQuery &query) const
{
    QUuid id = query.value(ID_KEY).toByteArray();
    QString owner = query.value(OWNER_KEY).toString();
    QString name = query.value(NAME_KEY).toString();
    return std::move(ChatRoom(id, owner, name));
}

ChatRoom RoomDatabase::find(const QUuid &roomID)
{
    ChatRoom room = DatabaseInterface::find(roomID, ROOM_TABLE);
    MessageDatabase mdb;
    ModDatabase modb;
    UserDatabase udb;
    QList<Message> messages = mdb.getMessages(room.getUUID(), 0);
    QList<QString> users = udb.get(roomID);
    QList<QString> mods = modb.get(roomID);
    room.addMessages(messages);
    room.addModerators(mods);
    room.addUsers(users);
    return std::move(room);
}

ChatRoom RoomDatabase::find(const QString &name)
{
    UserDatabase udb;
    qDebug() << "Finding row in table: " << name;
    db.transaction();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + ROOM_TABLE
                  + " WHERE " + NAME_KEY + " = ?;");
    query.addBindValue(name);
    runQuery(query);
    query.first();
    db.commit();
    ChatRoom room = std::move(buildFromQuery(query));
    QList<QString> users = udb.get(room.getUUID());
    room.addUsers(users);
    return std::move(room);
}

QList<ChatRoom> RoomDatabase::getAll()
{
    return std::move(DatabaseInterface::getAll(ROOM_TABLE));
}

bool RoomDatabase::remove(const ChatRoom &elem)
{
    return DatabaseInterface::remove(elem.getUUID(), ROOM_TABLE);
}

