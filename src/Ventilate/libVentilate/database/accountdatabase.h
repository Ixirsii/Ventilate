/*! \file
 * \brief Helper class that interfaces with the account database.
 * \author Ryan Porterfield
 * \since 2015-11-09
 * \copyright BSD 3 Clause
 */

#ifndef ACCOUNTDATABASE_H
#define ACCOUNTDATABASE_H

#include <QSqlQuery>
#include "account.h"
#include "databaseinterface.h"
#include "libventilate_global.h"

class AccountDatabase : public DatabaseInterface<Account>
{
public:
    AccountDatabase();
    virtual ~AccountDatabase();

    virtual bool add(const Account& elem);
    virtual Account find(const QUuid& id);
    virtual Account find(const QString& username);
    virtual QList<Account> getAll();
    virtual bool remove(const Account& elem);

protected:
    Account buildFromQuery(const QSqlQuery& query) const;
};

#endif // ACCOUNTDATABASE_H
