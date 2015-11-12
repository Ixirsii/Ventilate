/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-11
 * \copyright BSD 3 Clause
 */

#ifndef MESSAGEDATABASE_H
#define MESSAGEDATABASE_H

#include <QString>
#include "databaseinterface.h"
#include "libventilate_global.h"
#include "message.h"

class LIBVENTILATESHARED_EXPORT MessageDatabase
        : public DatabaseInterface<Message>
{
public:
    explicit MessageDatabase();
    virtual ~MessageDatabase();

    virtual bool add(const Message& elem);
    virtual Message find(const QUuid& id);
    virtual QList<Message> getAll();
    virtual QList<Message> getMessages(const QUuid& roomID, quint32 start);
    virtual bool remove(const Message& elem);

protected:
    virtual Message buildFromQuery(const QSqlQuery& query) const;

};

#endif // MESSAGEDATABASE_H
