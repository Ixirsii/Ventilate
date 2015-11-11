#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QUuid>
#include "libventilate_global.h"

template <typename T> class LIBVENTILATESHARED_EXPORT DatabaseInterface
{
public:
    explicit DatabaseInterface(QString table_name)
        : table_name(table_name), db(QSqlDatabase::addDatabase("QMYSQL", table_name)),
          db_host("localhost"), db_name("ventilate"),
          db_password("3rG1T1599{$8@[2hZL}cGN4i)TAywy2A"), db_username("ventilate")
    {
        QSqlQuery query(db);
        query.prepare("CREATE DATABASE IF NOT EXISTS ?;");
        query.addBindValue(db_name);
        if (!query.exec())
            qDebug() << query.lastError().text();
        db.setHostName(db_host);
        db.setDatabaseName(db_name);
        db.setUserName(db_username);
        db.setPassword(db_password);
        db.open();
    }

    virtual ~DatabaseInterface()
    {
        if (db.isOpen())
            db.close();
        QSqlDatabase::removeDatabase(table_name);
    }

    virtual bool add(const T& elem) = 0;
    virtual T find(const QUuid& id) const = 0;
    virtual T find(const QString& name) const = 0;
    virtual bool remove(const T& elem) = 0;

protected:
    const QString table_name;
    QSqlDatabase db;

private:
    const QString db_host;
    const QString db_name;
    const QString db_password;
    const QString db_username;
};

#endif // DATABASEINTERFACE_H
