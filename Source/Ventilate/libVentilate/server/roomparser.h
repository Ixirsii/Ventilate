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

    virtual void parse(const ConnectionHandler& handler, QDataStream& stream);

private:
    const QList<ConnectionHandler*>& clientList;

    void add(const ConnectionHandler& handler, QDataStream& stream);
    void create(const ConnectionHandler& handler, QDataStream& stream);
    void history(const ConnectionHandler& handler, QDataStream& stream);
    void join(const ConnectionHandler& handler, QDataStream& stream);
    void leave(const ConnectionHandler& handler, QDataStream& stream);
    void list(const ConnectionHandler& handler, QDataStream& stream);
    void message(QDataStream& stream);
    void mode(const ConnectionHandler& handler, QDataStream& stream);
    void propogateMessage(const Message& message);
    void remove(const ConnectionHandler& handler, QDataStream& stream);
};

#endif // ROOMPARSER_H
