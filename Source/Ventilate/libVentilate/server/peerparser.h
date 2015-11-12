/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef PEERPARSER_H
#define PEERPARSER_H

#include <QString>
#include <QStringList>
#include "commandparser.h"
#include "../connectionhandler.h"
#include "server.h"

class PeerParser : public CommandParser
{
public:
    explicit PeerParser(Server& server);

    virtual void parse(const ConnectionHandler& handler, QStringList& command);

private:
    void sendList(const ConnectionHandler& handler);
};

#endif // PEERPARSER_H
