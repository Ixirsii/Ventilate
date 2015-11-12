/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include "server.h"

class CommandParser
{
public:
    explicit CommandParser(Server& server);
    virtual ~CommandParser();

    virtual void parse(const ConnectionHandler& handler, QString& command) = 0;

protected:
    Server& server;
};

#endif // COMMANDPARSER_H
