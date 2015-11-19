/*! \file
 * \brief Parses Account based network requests.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright BSD 3 Clause
 */

#ifndef ACCOUNTPARSER_H
#define ACCOUNTPARSER_H

#include <QDataStream>
#include "commandparser.h"
#include "connectionhandler.h"

class AccountParser : public CommandParser
{
public:
    explicit AccountParser();
    virtual ~AccountParser();

    virtual void parse(const ConnectionHandler& handler, QDataStream& stream);

private:
    void create(const ConnectionHandler& handler, QDataStream& stream);
    void get(const ConnectionHandler& handler, QDataStream& stream);
    void login(const ConnectionHandler& handler, QDataStream& stream);
    void remove(const ConnectionHandler& handler, QDataStream& stream);
};

#endif // ACCOUNTPARSER_H
