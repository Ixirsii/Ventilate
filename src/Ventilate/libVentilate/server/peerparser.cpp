/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#include "peerparser.h"
#include <QString>
#include <QDataStream>
#include "commandparser.h"
#include "connectionhandler.h"

PeerParser::PeerParser(QList<ConnectionHandler*>& clientList)
    : clientList(clientList)
{
}


PeerParser::~PeerParser()
{
}

void PeerParser::parse(const ConnectionHandler& handler, QDataStream& stream)
{
    QString cmd;
    stream >> cmd;
    if (cmd != LIST)
        return;
    stream >> cmd;
    if (cmd == REQUEST)
        sendList(handler);
    // else save the peer list
}

void PeerParser::sendList(const ConnectionHandler& handler)
{
    QString list = PEER + " " + LIST + " ";
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
        list = list.append(LIST_SEPARATOR);
    }
    return list;
}

