/*! \file
 * \brief Parses Account based network requests.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright BSD 3 Clause
 */

#ifndef ACCOUNTPARSER_H
#define ACCOUNTPARSER_H

#include <QStringList>
#include "commandparser.h"
#include "connectionhandler.h"

class AccountParser : public CommandParser
{
public:
    explicit AccountParser();
    virtual ~AccountParser();

    virtual void parse(const ConnectionHandler& handler, QStringList& tokens);

private:
    void create(const ConnectionHandler& handler, QStringList& tokens);
    void get(const ConnectionHandler& handler, QString& name);
    void login(const ConnectionHandler& handler, QStringList& tokens);
    void remove(const ConnectionHandler& handler, QStringList& tokens);
};

#endif // ACCOUNTPARSER_H
