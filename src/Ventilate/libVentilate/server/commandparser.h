/*! \file
 * \brief Abstract base class that defines behavior for command parsers.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <QStringList>
#include "connectionhandler.h"

class LIBVENTILATESHARED_EXPORT CommandParser
{
public:
    static const QString ACCEPT;
    static const QString ACCOUNT;
    static const QString ADD;
    static const QString CHANGE;
    static const QString CREATE;
    static const QString DELETE;
    static const QString GET;
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
    static const QString SEND;
    static const QString SEP;
    static const QString USERS;

    static const QString GENERIC_ERROR;
    static const QString INVALID_PASSWORD;

    explicit CommandParser();
    virtual ~CommandParser();

    /*!
     * \brief Parse an incoming command from a client.
     *
     * This pure virtual function must be implemented by all concrete
     * sub-classes. This function handles extended parsing of sub-commands.
     *
     * \param handler Reference to the ConnectionHandler that recieved the
     * request.
     * \param request QDataStream that the handler read in from the network.
     */
    virtual void parse(const ConnectionHandler& handler, QStringList& tokens) = 0;

protected:
};

#endif // COMMANDPARSER_H
