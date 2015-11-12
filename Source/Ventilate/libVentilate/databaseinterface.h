/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-08
 * \copyright BSD 3 Clause
 */

#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QUuid>
#include "libventilate_global.h"

template <typename T> class LIBVENTILATESHARED_EXPORT DatabaseInterface
{
public:
    explicit DatabaseInterface()
        : id_key("id"), date_key("date"), email_key("email"),
          message_key("message"), password_key("password"), room_key("room"),
          username_key("username"), account_table("accounts"),
          message_table("messages"), room_table("rooms"),
          db(QSqlDatabase::addDatabase("QSQLITE", "ventilate"))
    {
        QString path = QCoreApplication::applicationDirPath() + "/ventilate.db";
        qDebug() << "Database path: " << path;
        db.setDatabaseName(path);
        if (!db.open()) {
            qDebug() << "DATABASE NOT OPENED: " << db.lastError().text();
            qDebug() << "";
        } else {
            qDebug() << "DATABASE OPENED";
            qDebug() << "";
        }
    }

    virtual ~DatabaseInterface()
    {
        if (db.isOpen())
            db.close();
        QSqlDatabase::removeDatabase(database_name);
    }

    virtual bool add(const T& elem) = 0;
    virtual T find(const QUuid& id) const = 0;
    virtual QList<T> getAll() const = 0;
    virtual bool remove(const T& elem) = 0;

protected:
    const QString id_key;
    const QString date_key;
    const QString email_key;
    const QString message_key;
    const QString password_key;
    const QString room_key;
    const QString username_key;
    const QString account_table;
    const QString message_table;
    const QString room_table;

    QSqlDatabase db;

    virtual T buildFromQuery(const QSqlQuery& query) const = 0;

    virtual T find(const QUuid &id, const QString& table) const
    {
        qDebug() << "Finding row in table: " << id;
        db.transaction();
        QSqlQuery query(db);
        query.prepare("SELECT * FROM " + table
                      + " WHERE " + id_key + " = ?;");
        query.addBindValue(id);
        runQuery(query);
        query.first();
        db.commit();
        return buildFromQuery(query);
    }

    virtual QList<T> getAll(const QString& table) const
    {
        qDebug() << "Getting all records from database";
        db.transaction();
        QSqlQuery query(db);
        query.prepare("SELECT * FROM " + table + ";");
        runQuery(query);
        db.commit();
        QList<T> list;
        while (query.next())
            list.append(buildAccountFromQuery(query));
        return std::move(list);
    }

    virtual bool remove(const QUuid& uuid, const QString& table)
    {
        qDebug() << "Removing row from table: ";
        db.transaction();
        QSqlQuery query(db);
        query.prepare("DELETE FROM " + table
                      +" WHERE " + id_key + " = ?;");
        query.addBindValue(uuid);
        bool flag = runQuery(query);
        db.commit();
        return flag;
    }

    bool runQuery(QSqlQuery& query) const
    {
        bool flag = query.exec();
        if (!flag)
            qDebug() << query.lastError().text();
        return flag;
    }
};

#endif // DATABASEINTERFACE_H
