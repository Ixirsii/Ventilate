/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef PEERPARSER_H
#define PEERPARSER_H

#include <QString>
#include "commandparser.h"
#include "../connectionhandler.h"
#include "server.h"

class PeerParser : public CommandParser
{
public:
    explicit PeerParser(Server& server);

    virtual void parse(const ConnectionHandler& handler, QString& command);

private:
    void sendList(const ConnectionHandler& handler, QString& command);
};

#endif // PEERPARSER_H
