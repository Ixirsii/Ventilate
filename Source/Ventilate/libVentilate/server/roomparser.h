/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef ROOMPARSER_H
#define ROOMPARSER_H

#include <QString>
#include "commandparser.h"
#include "../connectionhandler.h"
#include "server.h"

class RoomParser : public CommandParser
{
public:
    explicit RoomParser(Server& server);
    virtual ~RoomParser();

    virtual void parse(const ConnectionHandler& handler, QString& command);

private:
    void create(const ConnectionHandler& handler, QString& command);
};

#endif // ROOMPARSER_H
