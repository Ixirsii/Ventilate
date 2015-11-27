/*! \file
 * \brief Parses Account based network requests.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright BSD 3 Clause
 */

#ifndef ACCOUNTPARSER_H
#define ACCOUNTPARSER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include "account.h"
#include "commandparser.h"
#include "connectionhandler.h"

class AccountParser : public CommandParser
{
    Q_OBJECT
public:
    explicit AccountParser(QObject *parent = 0);
    virtual ~AccountParser();

    virtual QString parse(QString& subcmd, QStringList& tokens);

private:
    // Command functions
    QString create(QStringList& tokens);
    QString get(QString& name);
    QString login(QStringList& tokens);
    QString remove(QStringList& tokens);

    // Helper functinos
    Account buildAccount(QStringList& tokens);
};

#endif // ACCOUNTPARSER_H
