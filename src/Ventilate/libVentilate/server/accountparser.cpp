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
#include <QStringList>
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

void AccountParser::create(const ConnectionHandler& handler, QStringList& tokens)
{
    QUuid uuid = tokens.at(2);
    QString username = tokens.at(3);
    qDebug() << "QDateTime::fromString(" << tokens.at(4) << QString(")");
    QDateTime time = QDateTime::fromString(tokens.at(4), Qt::ISODate);
    QByteArray phash;
    phash.append(tokens.at(5));
    QString email = tokens.at(3);
    Account acc(uuid, username, time, phash, email);
    AccountDatabase db;
    if (db.add(acc))
        handler.write(ACCEPT);
    else
        handler.write(REJECT + SEP + GENERIC_ERROR);
}


void AccountParser::get(const ConnectionHandler& handler, QString& name)
{
    AccountDatabase db;
    Account acc = db.find(name);
    QString cmd = ACCOUNT + SEP + SEND + SEP + acc.toString();
    handler.write(cmd);
}


void AccountParser::login(const ConnectionHandler& handler, QStringList& tokens)
{
    QString username = tokens.at(2);
    QByteArray phash;
    phash.append(tokens.at(3));
    if (Account::authenticateUser(username, phash))
        get(handler, username);
    else
        handler.write(REJECT + SEP + INVALID_PASSWORD);
}

void AccountParser::parse(const ConnectionHandler& handler, QStringList& tokens)
{
    QString cmd = tokens.at(1);
    if (cmd == LOGIN)
        login(handler, tokens);
    else if (cmd == CREATE)
        create(handler, tokens);
    else if (cmd == DELETE)
        remove(handler, tokens);
}

void AccountParser::remove(const ConnectionHandler& handler, QStringList& tokens)
{
    QString username = tokens.at(2);
    QByteArray phash;
    phash.append(tokens.at(3));
    if (!Account::authenticateUser(username, phash)) {
        handler.write(REJECT + SEP + INVALID_PASSWORD);
        return;
    }
    AccountDatabase db;
    Account acc = db.find(username);
    if (db.remove(acc))
        handler.write(ACCEPT);
    else
        handler.write(REJECT + SEP + GENERIC_ERROR);
}
