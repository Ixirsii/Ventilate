/*! \file
 * \brief Interfaces with the database storing user accounts.
 * \author Ryan Porterfield
 * \since 2015-11-09
 * \copyright BSD 3 Clause
 */

#include "accountdatabase.h"
#include <memory>
#include <QVariant>

const QString AccountDatabase::ID_KEY = "id";
const QString AccountDatabase::DATE_KEY = "date";
const QString AccountDatabase::EMAIL_KEY = "email";
const QString AccountDatabase::PASSWORD_KEY = "password";
const QString AccountDatabase::USERNAME_KEY = "username";


AccountDatabase::AccountDatabase()
    : DatabaseInterface("account")
{
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS " + table_name + " ("
               + ID_KEY + " BLOB NOT NULL UNIQUE, "
               + DATE_KEY + " DATETIME NOT NULL, "
               + EMAIL_KEY + " TEXT NOT NULL UNIQUE, "
               + PASSWORD_KEY + " BLOB NOT NULL, "
               + USERNAME_KEY + " TEXT NOT NULL UNIQUE, "
               + "PRIMARY KEY (" + ID_KEY + "))");
}

AccountDatabase::~AccountDatabase()
{

}

bool AccountDatabase::add(const Account& elem)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO ? (?, ?, ?, ?, ?) VALUES (?, ?, ?, ?, ?);");
    query.addBindValue(QVariant(table_name));
    query.addBindValue(ID_KEY);
    query.addBindValue(DATE_KEY);
    query.addBindValue(EMAIL_KEY);
    query.addBindValue(PASSWORD_KEY);
    query.addBindValue(USERNAME_KEY);
    query.addBindValue(elem.getUUID());
    query.addBindValue(elem.getCreationDate());
    query.addBindValue(elem.getEmailAddress());
    query.addBindValue(elem.getPasswordHash());
    query.addBindValue(elem.getUsername());
    return query.exec();
}


Account AccountDatabase::buildAccountFromQuery(QSqlQuery &query) const
{
    query.next();
    QUuid id = query.value(ID_KEY).toByteArray();
    QDateTime date = query.value(DATE_KEY).toDateTime();
    QString email = query.value(EMAIL_KEY).toString();
    QByteArray password = query.value(PASSWORD_KEY).toByteArray();
    QString username = query.value(USERNAME_KEY).toString();
    return Account(id, username, date, password, email);
}


Account AccountDatabase::find(const QString &username) const
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM ? WHERE ? = ?;");
    query.addBindValue(table_name);
    query.addBindValue(USERNAME_KEY);
    query.addBindValue(username);
    query.exec();
    return std::move(buildAccountFromQuery(query));
}

Account AccountDatabase::find(const QUuid& id) const
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM ? WHERE ? = ?;");
    query.addBindValue(table_name);
    query.addBindValue(ID_KEY);
    query.addBindValue(id.toByteArray());
    query.exec();
    return buildAccountFromQuery(query);
}

bool AccountDatabase::remove(const Account& elem)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ? WHERE ? = ?;");
    query.addBindValue(table_name);
    query.addBindValue(ID_KEY);
    query.addBindValue(elem.getUUID().toByteArray());
    return query.exec();
}

