/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright BSD 3 Clause
 */

#ifndef ACCOUNTPARSER_H
#define ACCOUNTPARSER_H

#include <QStringList>
#include "commandparser.h"
#include "connectionhandler.h"
#include "server.h"

class AccountParser : public CommandParser
{
public:
    explicit AccountParser(Server& server);
    virtual ~AccountParser();

    virtual void parse(const ConnectionHandler& handler, QStringList& command);

private:
    void create(const ConnectionHandler& handler, QStringList& command);
    void login(const ConnectionHandler& handler, QStringList& command);
    void remove(const ConnectionHandler& handler, QStringList& command);
};

#endif // ACCOUNTPARSER_H
