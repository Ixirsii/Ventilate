/*! \file
 * \brief Helper class that interfaces with the user <-> chat room database.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright BSD 3 Clause
 */

#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <QString>
#include <QUuid>
#include "account.h"
#include "databaseinterface.h"
#include "minidbinterface.h"

class UserDatabase : public MiniDBInterface
{
public:
    explicit UserDatabase();
    virtual ~UserDatabase();

    virtual bool add(const QString& name, const QUuid& roomID);
    virtual bool remove(const QString& name, const QUuid& roomID);
};

#endif // USERDATABASE_H
