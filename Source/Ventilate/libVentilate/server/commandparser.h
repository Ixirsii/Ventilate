/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <QString>
#include <QStringList>
#include "connectionhandler.h"
#include "server.h"

class CommandParser
{
public:
    static const QString ACCEPT;
    static const QString ACCOUNT;
    static const QString ADD;
    static const QString CHANGE;
    static const QString CREATE;
    static const QString DELETE;
    static const QString HISTORY;
    static const QString JOIN;
    static const QString LEAVE;
    static const QString LIST;
    static const QString LOGIN;
    static const QString MESSAGE;
    static const QString MODE;
    static const QString PASSWORD;
    static const QString PEER;
    static const QString REJECT;
    static const QString REQUEST;
    static const QString RESET;
    static const QString ROOM;

    static const QString GENERIC_ERROR;
    static const QString INVALID_PASSWORD;

    explicit CommandParser(Server& server);
    virtual ~CommandParser();

    virtual void parse(const ConnectionHandler& handler, QStringList& command) = 0;

protected:
    static const QSring LIST_SEPARATOR;
    Server& server;
};

#endif // COMMANDPARSER_H
