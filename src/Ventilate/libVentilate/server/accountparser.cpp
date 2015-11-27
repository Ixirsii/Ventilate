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
#include "server.h"


AccountParser::AccountParser(QObject *parent)
    : CommandParser(parent)
{
}


AccountParser::~AccountParser()
{
}

Account AccountParser::buildAccount(QStringList &tokens)
{
    QStringList::iterator iter = tokens.begin();
    QByteArray phash;
    QUuid uuid = *iter++;
    QString username = *iter++;
    QDateTime time = QDateTime::fromString(*iter++, Qt::ISODate);
    phash.append(*iter++);
    QString email = *iter++;
    return std::move(Account(uuid, username, time, phash, email));
}

QString AccountParser::create(QStringList& tokens)
{
    Account acc = buildAccount(tokens);
    AccountDatabase db;
    if (db.add(acc))
        return ACCEPT;
    else
        return REJECT + SEP + GENERIC_ERROR;
}


QString AccountParser::get(QString& name)
{
    AccountDatabase db;
    Account acc = db.find(name);
    return ACCOUNT + SEP + SEND + SEP + acc.toString();
}

QString AccountParser::login(QStringList& tokens)
{
    QStringList::iterator iter = tokens.begin();
    QString username = *iter++;
    QByteArray phash;
    phash.append(*iter++);
    if (Account::authenticateUser(username, phash))
        return get(username);
    else
        return REJECT + SEP + INVALID_PASSWORD;
}

QString AccountParser::parse(QString& subcmd, QStringList& tokens)
{
    if (subcmd == LOGIN)
        return login(tokens);
    else if (subcmd == CREATE)
        return create(tokens);
    else if (subcmd == DELETE)
        return remove(tokens);
    return REJECT + " " + GENERIC_ERROR;
}

QString AccountParser::remove(QStringList& tokens)
{
    QStringList::iterator iter = tokens.begin();
    QString username = *iter++;
    QByteArray phash;
    phash.append(*iter++);
    if (!Account::authenticateUser(username, phash)) {
        return REJECT + SEP + INVALID_PASSWORD;
    }
    AccountDatabase db;
    Account acc = db.find(username);
    if (db.remove(acc))
        return ACCEPT;
    else
        return REJECT + SEP + GENERIC_ERROR;
}
