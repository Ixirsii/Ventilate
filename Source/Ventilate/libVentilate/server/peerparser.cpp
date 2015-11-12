/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#include "peerparser.h"
#include <QString>
#include <QStringList>
#include "commandparser.h"
#include <connectionhandler.h>
#include "server.h"

PeerParser::PeerParser(Server& server)
    : CommandParser(server)
{
}


void PeerParser::parse(const ConnectionHandler& handler, QStringList& command)
{
    QString cmd = command.at(1);
    if (cmd != LIST || command.length() < 3)
        return;
    cmd = command.at(2);
    if (cmd == REQUEST)
        sendList(handler);
    // else save the peer list
}

void PeerParser::sendList(const ConnectionHandler& handler)
{
    QString list = server.serializePeerList();
    handler.write(list);
}

