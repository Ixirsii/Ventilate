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
{
}

AccountDatabase::~AccountDatabase()
{
}

bool AccountDatabase::add(const Account& elem)
{
    qDebug() << "Adding row to table: " << elem.getUsername();
    db.transaction();
    QSqlQuery query(db);
    query.prepare("INSERT INTO " + ACCOUNT_TABLE +
                  "(" + ID_KEY + ", " + DATE_KEY  + ", "
                  + EMAIL_KEY + ", "  + PASSWORD_KEY + ", " + NAME_KEY + ")"
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


Account AccountDatabase::buildFromQuery(const QSqlQuery& query) const
{
    QUuid id = query.value(ID_KEY).toByteArray();
    QDateTime date = query.value(DATE_KEY).toDateTime();
    QString email = query.value(EMAIL_KEY).toString();
    QByteArray password = query.value(PASSWORD_KEY).toByteArray();
    QString username = query.value(NAME_KEY).toString();
    return std::move(Account(id, username, date, password, email));
}


Account AccountDatabase::find(const QUuid& id)
{
    return std::move(DatabaseInterface::find(id, ACCOUNT_TABLE));
}

Account AccountDatabase::find(const QString &username)
{
    qDebug() << "Finding row in table: " << username;
    db.transaction();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM " + ACCOUNT_TABLE
                  + " WHERE " + NAME_KEY + " = ?;");
    query.addBindValue(username);
    runQuery(query);
    query.first();
    db.commit();
    return std::move(buildFromQuery(query));
}

QList<Account> AccountDatabase::getAll()
{
    return std::move(DatabaseInterface::getAll(ACCOUNT_TABLE));
}

bool AccountDatabase::remove(const Account& elem)
{
    return DatabaseInterface::remove(elem.getUUID(), ACCOUNT_TABLE);
}

