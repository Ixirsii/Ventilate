/*! \file
 * \brief Parses Password based network requests.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef PASSWORDPARSER_H
#define PASSWORDPARSER_H

#include <QStringList>
#include "commandparser.h"
#include "connectionhandler.h"

class PasswordParser : public CommandParser
{
public:
    explicit PasswordParser();
    virtual ~PasswordParser();

    virtual void parse(const ConnectionHandler& handler, QStringList& tokens);

private:
    void change(const ConnectionHandler& handler, QStringList& tokens);
};

#endif // PASSWORDPARSER_H
