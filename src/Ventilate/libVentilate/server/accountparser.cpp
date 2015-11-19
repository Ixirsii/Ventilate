/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright BSD 3 Clause
 */

#include "accountparser.h"

#include <QByteArray>
#include <QDataStream>
#include <QString>
#include <QUuid>

#include "account.h"
#include "database/accountdatabase.h"
#include "commandparser.h"
#include "connectionhandler.h"
#include "server.h"


AccountParser::AccountParser()
{
}


AccountParser::~AccountParser()
{
}

void AccountParser::create(const ConnectionHandler& handler, QDataStream& stream)
{
    QUuid uuid;
    QString username, email;
    QDateTime time;
    QByteArray phash;
    stream >> uuid >> username >> time >> phash >> email;
    Account acc(uuid, username, time, phash, email);
    AccountDatabase db;
    if (db.add(acc))
        handler.write(ACCEPT);
    else
        handler.write(REJECT + " " + GENERIC_ERROR);
}


void AccountParser::get(const ConnectionHandler& handler, QDataStream& stream)
{
    AccountDatabase db;
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    QString username;
    stream >> username;
    Account acc = db.find(username);
    str << acc;
    handler.write(data);
}


void AccountParser::login(const ConnectionHandler& handler, QDataStream& stream)
{
    QString username;
    QByteArray phash;
    stream >> username >> phash;
    if (Account::authenticateUser(username, phash))
        handler.write(ACCEPT);
    else
        handler.write(REJECT + " " + INVALID_PASSWORD);
}

void AccountParser::parse(const ConnectionHandler& handler, QDataStream& stream)
{
    QString cmd;
    stream >> cmd;
    if (cmd == LOGIN)
        login(handler, stream);
    else if (cmd == GET)
        get(handler, stream);
    else if (cmd == CREATE)
        create(handler, stream);
    else if (cmd == DELETE)
        remove(handler, stream);
}

void AccountParser::remove(const ConnectionHandler& handler, QDataStream& stream)
{
    QString username;
    QByteArray phash;
    stream >> username >> phash;
    if (!Account::authenticateUser(username, phash)) {
        handler.write(REJECT + " " + INVALID_PASSWORD);
        return;
    }
    AccountDatabase db;
    Account acc = db.find(username);
    if (db.remove(acc))
        handler.write(ACCEPT);
    else
        handler.write(REJECT + " " + GENERIC_ERROR);
}
