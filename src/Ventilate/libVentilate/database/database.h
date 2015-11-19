/*! \file
 * \brief Abstract base class that defines database interfaces.
 * \author Ryan Porterfield
 * \since 2015-11-11
 * \copyright BSD 3 Clause
 */

#ifndef DATABASEINITIALIZER_H
#define DATABASEINITIALIZER_H

#include <QSqlDatabase>
#include "libventilate_global.h"

class Database
{
public:
    explicit Database();
    virtual ~Database();

    static void init();

protected:
    static const QString ID_KEY;
    static const QString DATABASE_NAME;
    static const QString DATE_KEY;
    static const QString EMAIL_KEY;
    static const QString MESSAGE_KEY;
    static const QString MODERATOR_KEY;
    static const QString NAME_KEY;
    static const QString OWNER_KEY;
    static const QString PASSWORD_KEY;
    static const quint32 RETURN_RANGE;
    static const QString ROOM_KEY;
    static const QString USER_KEY;
    static const QString ACCOUNT_TABLE;
    static const QString MESSAGE_TABLE;
    static const QString MOD_TABLE;
    static const QString ROOM_TABLE;
    static const QString USER_TABLE;

    QSqlDatabase db;

    static void openDB(QSqlDatabase& db);
    static bool runQuery(QSqlQuery& query);

private:
    static quint32 counter;
    QString connection_name;

    static void createAccountDB(QSqlDatabase& db);
    static void createMessageDB(QSqlDatabase& db);
    static void createModeratorDB(QSqlDatabase& db);
    static void createRoomDB(QSqlDatabase& db);
    static void createUserDB(QSqlDatabase& db);
};

#endif // DATABASEINITIALIZER_H
