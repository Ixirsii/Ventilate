/*! \file
 * \brief Parses ChatRoom and Message based network requests.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef ROOMPARSER_H
#define ROOMPARSER_H

#include <QDataStream>
#include "message.h"
#include "commandparser.h"
#include "connectionhandler.h"

class RoomParser : public CommandParser
{
public:
    explicit RoomParser(QList<ConnectionHandler*>& clientList);
    virtual ~RoomParser();

    virtual void parse(const ConnectionHandler& handler, QStringList& tokens);

private:
    const QList<ConnectionHandler*>& clientList;

    void add(const ConnectionHandler& handler, QStringList& tokens);
    void create(const ConnectionHandler& handler, QStringList& tokens);
    void history(const ConnectionHandler& handler, QStringList& tokens);
    void join(const ConnectionHandler& handler, QStringList& tokens);
    void leave(const ConnectionHandler& handler, QStringList& tokens);
    void list(const ConnectionHandler& handler, QStringList& tokens);
    void message(QStringList& tokens);
    void mode(const ConnectionHandler& handler, QStringList& tokens);
    void propogateMessage(const Message& message);
    void remove(const ConnectionHandler& handler, QStringList& tokens);
};

#endif // ROOMPARSER_H
