/*! \file
 * \brief Abstract base class that defines child database interfaces.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright BSD 3 Clause
 */

#ifndef MINIDBINTERFACE_H
#define MINIDBINTERFACE_H

#include <QList>
#include <QString>
#include <QUuid>
#include "database.h"

class MiniDBInterface : public Database
{
public:
    explicit MiniDBInterface(const QString& table);
    virtual ~MiniDBInterface();

    virtual bool add(const QString &name, const QUuid &roomID);
    virtual bool contains(const QString &name, const QUuid& roomID);
    virtual QList<QString> get(const QUuid &roomID);
    virtual bool remove(const QString &name, const QUuid &roomID);

private:
    const QString table;

    QList<QString> getListFromQuery(QSqlQuery &query);
};

#endif // MINIDBINTERFACE_H
