/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright BSD 3 Clause
 */

#include "account.h"
#include "../database/accountdatabase.h"
#include "accountparser.h"
#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QUuid>
#include "commandparser.h"
#include "connectionhandler.h"
#include "server.h"

AccountParser::AccountParser(Server& server)
    : CommandParser(server)
{
}


virtual AccountParser::~AccountParser()
{
}

void AccountParser::create(const ConnectionHandler& handler, QStringList& command)
{
    QUuid uuid(command.at(2));
    QString username = command.at(3);
    QDateTime time(command.at(4));
    QByteArray phash(command.at(5));
    QString email = command.at(6);
    Account acc(uuid, username, time, phash, email);
    AccountDatabase db;
    if (db.add(acc))
        handler.write(ACCEPT);
    else
        handler.write(REJECT + " " + GENERIC_ERROR);
}

void AccountParser::login(const ConnectionHandler& handler, QStringList& command)
{
    QString username = command.at(2);
    QByteArray phash(command.at(3));
    if (Account::authenticateUser(username, phash))
        handler.write(ACCEPT);
    else
        handler.write(REJECT + " " + INVALID_PASSWORD);
}

void AccountParser::parse(const ConnectionHandler& handler, QStringList& command)
{
    QString cmd = command.at(1);
    if (cmd == LOGIN)
        login(handler, command);
    else if (cmd == CREATE)
        create(handler, command);
    else if (cmd == DELETE)
        remove(handler, command);

}

void AccountParser::remove(const ConnectionHandler& handler, QStringList& command)
{
    QString username = command.at(2);
    QByteArray phash(command.at(3));
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
