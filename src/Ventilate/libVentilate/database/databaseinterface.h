/*! \file
 * \brief Abstract base class that defines parent database interfaces.
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
#include "database.h"
#include "libventilate_global.h"

template <typename T> class LIBVENTILATESHARED_EXPORT DatabaseInterface
        : public Database
{
public:
    explicit DatabaseInterface()
    {
    }

    virtual ~DatabaseInterface()
    {
    }

    virtual bool add(const T& elem) = 0;
    virtual T find(const QUuid& id) = 0;
    virtual QList<T> getAll() = 0;
    virtual bool remove(const T& elem) = 0;

protected:
    /*!
     * \brief Build an object from a database query.
     *
     * This templated pure virtual function requires concrete sub-classes to
     * build an object, most likely an Account, ChatRoom, or Message that was
     * stored in the database.
     *
     * \param query Results of the SQL query.
     * \return An object from the database.
     */
    virtual T buildFromQuery(const QSqlQuery& query) const = 0;

    virtual T find(const QUuid &id, const QString& table)
    {
        qDebug() << "Finding row in table: " << id;
        db.transaction();
        QSqlQuery query(db);
        query.prepare("SELECT * FROM " + table
                      + " WHERE " + ID_KEY + " = ?;");
        query.addBindValue(id);
        runQuery(query);
        query.first();
        db.commit();
        return buildFromQuery(query);
    }

    virtual QList<T> getAll(const QString& table)
    {
        qDebug() << "Getting all records from database";
        db.transaction();
        QSqlQuery query(db);
        query.prepare("SELECT * FROM " + table + ";");
        runQuery(query);
        db.commit();
        QList<T> list;
        while (query.next())
            list.append(buildFromQuery(query));
        return std::move(list);
    }

    virtual bool remove(const QUuid& uuid, const QString& table)
    {
        qDebug() << "Removing row from table: ";
        db.transaction();
        QSqlQuery query(db);
        query.prepare("DELETE FROM " + table
                      +" WHERE " + ID_KEY + " = ?;");
        query.addBindValue(uuid);
        bool flag = runQuery(query);
        db.commit();
        return flag;
    }
};

#endif // DATABASEINTERFACE_H
