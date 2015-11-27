/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright BSD 3 Clause
 */

#include "minidbinterface.h"
#include <QDebug>
#include <QList>
#include <QSqlQuery>
#include <QString>

MiniDBInterface::MiniDBInterface(const QString& table)
    : table(table)
{
}

MiniDBInterface::~MiniDBInterface()
{
}

bool MiniDBInterface::add(const QString& name, const QUuid& roomID)
{
    qDebug() << "Adding " << name << " to room " << roomID.toString() << " in database";
    db.transaction();
    QSqlQuery query(db);
    query.prepare("INSERT INTO " + table + "(" + NAME_KEY + ", "
                  + ID_KEY + ")" + " VALUES(?, ?);");
    query.addBindValue(name);
    query.addBindValue(roomID);
    bool flag = runQuery(query);
    db.commit();
    return flag;
}

bool MiniDBInterface::contains(const QString &name, const QUuid &roomID)
{
    qDebug() << "Checking if room " << roomID << " contains user " << name;
    db.transaction();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + table + " WHERE " + NAME_KEY +
                  " = ? AND " + ID_KEY
                  + " = ? ORDER BY " + NAME_KEY + " ASC;");
    query.addBindValue(name);
    query.addBindValue(roomID);
    runQuery(query);
    db.commit();
    int count = 0;
    while (query.next())
        ++count;
    qDebug() << "size: " << count;
    return count > 0;
}

QList<QString> MiniDBInterface::get(const QUuid &roomID)
{
    qDebug() << "Getting from room in database";
    db.transaction();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + table + " WHERE " + ID_KEY
                  + " = ? ORDER BY " + NAME_KEY + " ASC;");
    query.addBindValue(roomID);
    runQuery(query);
    db.commit();
    return std::move(getListFromQuery(query));
}

QList<QString> MiniDBInterface::getListFromQuery(QSqlQuery& query)
{
    QList<QString> list;
    while (query.next())
        list.append(query.value(NAME_KEY).toString());
    return std::move(list);
}

bool MiniDBInterface::remove(const QString& name, const QUuid& roomID)
{
    qDebug() << "Removing from room in database: ";
    db.transaction();
    QSqlQuery query(db);
    query.prepare("DELETE FROM " + table + " WHERE " + NAME_KEY + " = ? AND "
                  + ID_KEY + " = ?;");
    query.addBindValue(name);
    query.addBindValue(roomID);
    bool flag = runQuery(query);
    db.commit();
    return flag;
}
