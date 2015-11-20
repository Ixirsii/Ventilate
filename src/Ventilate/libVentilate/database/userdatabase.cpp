/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright BSD 3 Clause
 */

#include "userdatabase.h"
#include "account.h"
#include "accountdatabase.h"
#include "chatroom.h"
#include "chatroomdatabase.h"

UserDatabase::UserDatabase()
    : MiniDBInterface(USER_TABLE)
{
}

UserDatabase::~UserDatabase()
{
}

bool UserDatabase::add(const QString &name, const QUuid &roomID)
{
    AccountDatabase adb;
    Account acc = adb.find(name);
    ChatRoomDatabase cdb;
    ChatRoom chat = cdb.find(roomID);
    chat.addUser(acc.getUsername());
    return MiniDBInterface::add(name, roomID);
}

bool UserDatabase::remove(const QString &name, const QUuid &roomID)
{
    AccountDatabase adb;
    Account acc = adb.find(name);
    ChatRoomDatabase cdb;
    ChatRoom chat = cdb.find(roomID);
    chat.removeUser(acc.getUsername());
    return MiniDBInterface::remove(name, roomID);
}
