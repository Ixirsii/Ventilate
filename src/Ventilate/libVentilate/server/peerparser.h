/*! \file
 * \brief Parses peer based network requests.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef PEERPARSER_H
#define PEERPARSER_H

#include <QStringList>
#include "commandparser.h"
#include "connectionhandler.h"

class PeerParser : public CommandParser
{
public:
    explicit PeerParser(QList<ConnectionHandler*>& clientList);
    virtual ~PeerParser();

    virtual void parse(const ConnectionHandler& handler, QStringList& tokens);

private:
    const QList<ConnectionHandler*>& clientList;

    void sendList(const ConnectionHandler& handler);
    QString serializePeerList();
};

#endif // PEERPARSER_H
