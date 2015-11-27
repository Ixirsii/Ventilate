/*! \file
 * \brief Parses peer based network requests.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef PEERPARSER_H
#define PEERPARSER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include "connectionhandler.h"
#include "server/commandparser.h"

class PeerParser : public CommandParser
{
    Q_OBJECT
public:
    explicit PeerParser(ConnectionHandler &handler, QObject *parent = 0);
    virtual ~PeerParser();

    virtual QString parse(QString &subcmd, QStringList& tokens);

private:
    ConnectionHandler &handler;

    QString sendList();
};

#endif // PEERPARSER_H
