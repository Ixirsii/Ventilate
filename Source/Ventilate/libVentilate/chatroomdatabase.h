/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-11
 * \copyright BSD 3 Clause
 */

#ifndef CHATROOMDATABASE_H
#define CHATROOMDATABASE_H

#include <chatroom.h>
#include <databaseinterface.h>
#include <libventilate_global.h>

class LIBVENTILATESHARED_EXPORT ChatRoomDatabase
        : public DatabaseInterface<ChatRoom>
{
public:
    explicit ChatRoomDatabase();

    virtual bool add(const ChatRoom& elem);
    virtual ChatRoom find(const QUuid& id) const;
    virtual QList<ChatRoom> getAll() const;
    virtual bool remove(const ChatRoom& elem);

protected:
    virtual ChatRoom buildFromQuery(const QSqlQuery& query) const;
};

#endif // CHATROOMDATABASE_H
