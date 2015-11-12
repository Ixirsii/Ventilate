/*! \file
 * \brief Interfaces with the database storing user accounts.
 * \author Ryan Porterfield
 * \since 2015-11-09
 * \copyright BSD 3 Clause
 */

#include "accountdatabase.h"
#include <memory>
#include <QDebug>
#include <QVariant>


AccountDatabase::AccountDatabase()
    : DatabaseInterface("account")
{
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS " + account_table + "("
               + id_key + " BLOB NOT NULL UNIQUE PRIMARY KEY, "
               + date_key + " DATETIME NOT NULL, "
               + email_key + " TEXT NOT NULL UNIQUE, "
               + password_key + " BLOB NOT NULL, "
               + username_key + " TEXT NOT NULL UNIQUE);");
    runQuery(query);
}

AccountDatabase::~AccountDatabase()
{
}

bool AccountDatabase::add(const Account& elem)
{
    qDebug() << "Adding row to table: " << elem.getUsername();
    db.transaction();
    QSqlQuery query(db);
    query.prepare("INSERT INTO " + account_table +
                  "(" + id_key + ", " + date_key  + ", "
                  + email_key + ", "  + password_key + ", " + username_key + ")"
                  + " VALUES(?, ?, ?, ?, ?);");
    query.addBindValue(elem.getUUID());
    query.addBindValue(elem.getCreationDate());
    query.addBindValue(elem.getEmailAddress());
    query.addBindValue(elem.getPasswordHash());
    query.addBindValue(elem.getUsername());
    bool flag = runQuery(query);
    db.commit();
    return flag;
}


Account AccountDatabase::buildFromQuery(QSqlQuery &query) const
{
    QUuid id = query.value(id_key).toByteArray();
    QDateTime date = query.value(date_key).toDateTime();
    QString email = query.value(email_key).toString();
    QByteArray password = query.value(password_key).toByteArray();
    QString username = query.value(username_key).toString();
    return std::move(Account(id, username, date, password, email));
}


Account AccountDatabase::find(const QUuid& id) const
{
    return std::move(find(id, account));
}

Account AccountDatabase::find(const QString &username) const
{
    qDebug() << "Finding row in table: " << username;
    db.transaction();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + account_table
                  + " WHERE " + username_key + " = ?;");
    query.addBindValue(username);
    runQuery(query);
    query.first();
    db.commit();
    return std::move(buildAccountFromQuery(query));
}

QList<Account> AccountDatabase::getAll() const
{
    return std::move(getAll(account_table));
}

bool AccountDatabase::remove(const Account& elem)
{
    return remove(elem.getUUID(), account_table);
}

