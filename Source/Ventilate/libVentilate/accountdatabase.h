#ifndef ACCOUNTDATABASE_H
#define ACCOUNTDATABASE_H

#include <QSqlQuery>
#include "account.h"
#include "databaseinterface.h"
#include "libventilate_global.h"

class LIBVENTILATESHARED_EXPORT AccountDatabase : public DatabaseInterface<Account>
{
public:
    AccountDatabase();
    virtual ~AccountDatabase();

    virtual bool add(const Account& elem);
    virtual Account find(const QUuid& id) const;
    virtual Account find(const QString& username) const;
    virtual bool remove(const Account& elem);

private:
    static const QString ID_KEY;
    static const QString DATE_KEY;
    static const QString EMAIL_KEY;
    static const QString PASSWORD_KEY;
    static const QString USERNAME_KEY;
    Account buildAccountFromQuery(QSqlQuery& query) const;
};

#endif // ACCOUNTDATABASE_H
