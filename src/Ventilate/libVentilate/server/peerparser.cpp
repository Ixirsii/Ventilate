/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#include "peerparser.h"
#include <vector>
#include <QString>
#include <QStringList>
#include "commandparser.h"

PeerParser::PeerParser(ConnectionHandler &handler, QObject *parent)
    : CommandParser(parent), handler(handler)
{
}


PeerParser::~PeerParser()
{
}

QString PeerParser::parse(QString& subcmd, QStringList& tokens)
{
    if (subcmd != LIST)
        return "";
    subcmd = tokens.at(0);
    if (subcmd == REQUEST)
        return sendList();
    // else save the peer list
    return REJECT + " " + GENERIC_ERROR;
}

QString PeerParser::sendList()
{
    QString list = PEER + SEP + LIST + SEP;
    list.append(handler.serializePeerList());
    return list;
}
