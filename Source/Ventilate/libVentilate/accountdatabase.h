/*! \file
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

class LIBVENTILATESHARED_EXPORT AccountDatabase
        : public DatabaseInterface<Account>
{
public:
    AccountDatabase();
    virtual ~AccountDatabase();

    virtual bool add(const Account& elem);
    virtual Account find(const QUuid& id) const;
    virtual Account find(const QString& username) const;
    virtual QList<Account> getAll() const;
    virtual bool remove(const Account& elem);

protected:
    Account buildFromQuery(const QSqlQuery& query) const;
};

#endif // ACCOUNTDATABASE_H
