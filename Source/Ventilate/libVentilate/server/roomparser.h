/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef ROOMPARSER_H
#define ROOMPARSER_H

#include <QString>
#include <QStringList>
#include "commandparser.h"
#include "connectionhandler.h"
#include "server.h"

class RoomParser : public CommandParser
{
public:
    explicit RoomParser(Server& server);
    virtual ~RoomParser();

    virtual void parse(const ConnectionHandler& handler, QStringList& command);

private:
    void add(const ConnectionHandler& handler, QStringList& command);
    void create(const ConnectionHandler& handler, QStringList& command);
    void history(const ConnectionHandler& handler, QStringList& command);
    void join(const ConnectionHandler& handler, QStringList& command);
    void leave(const ConnectionHandler& handler, QStringList& command);
    void list(const ConnectionHandler& handler, QStringList& command);
    void message(const ConnectionHandler& handler, QStringList& command);
    void mode(const ConnectionHandler& handler, QStringList& command);
    void remove(const ConnectionHandler& handler, QStringList& command);
};

#endif // ROOMPARSER_H
