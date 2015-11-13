/*! \file
 * \brief Parses Password based network requests.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef PASSWORDPARSER_H
#define PASSWORDPARSER_H

#include <QDataStream>
#include "commandparser.h"
#include "connectionhandler.h"

class PasswordParser : public CommandParser
{
public:
    explicit PasswordParser();
    virtual ~PasswordParser();

    virtual void parse(const ConnectionHandler& handler, QDataStream& stream);

private:
    void change(const ConnectionHandler& handler, QDataStream& stream);
};

#endif // PASSWORDPARSER_H
