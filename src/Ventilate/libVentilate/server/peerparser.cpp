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
#include "connectionhandler.h"

PeerParser::PeerParser(QList<ConnectionHandler*>& clientList)
    : clientList(clientList)
{
}


PeerParser::~PeerParser()
{
}

void PeerParser::parse(const ConnectionHandler& handler, QStringList& tokens)
{
    QString cmd = tokens.at(2);
    if (cmd != LIST)
        return;
    cmd = tokens.at(3);
    if (cmd == REQUEST)
        sendList(handler);
    // else save the peer list
}

void PeerParser::sendList(const ConnectionHandler& handler)
{
    QString list = PEER + SEP + LIST + SEP;
    list.append(serializePeerList());
    handler.write(list);
}


/*!
 * \brief Server::serializePeerList
 * \return
 */
QString PeerParser::serializePeerList()
{
    QString list = "";
    for (const ConnectionHandler* handler: clientList) {
        list = list.append(handler->getHostAddress().toString());
        list = list.append(SEP);
    }
    return list;
}

