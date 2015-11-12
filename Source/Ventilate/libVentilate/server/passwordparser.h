/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef PASSWORDPARSER_H
#define PASSWORDPARSER_H

#include <QString>
#include <QStringList>
#include "commandparser.h"
#include "../connectionhandler.h"
#include "server.h"

class PasswordParser : public CommandParser
{
public:
    explicit PasswordParser(Server& server);

    virtual void parse(const ConnectionHandler& handler, QStringList& command);

private:
    void change(const ConnectionHandler& handler, QString& command);
};

#endif // PASSWORDPARSER_H
