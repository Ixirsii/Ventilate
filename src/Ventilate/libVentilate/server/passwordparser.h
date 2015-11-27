/*! \file
 * \brief Parses Password based network requests.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef PASSWORDPARSER_H
#define PASSWORDPARSER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include "commandparser.h"

class PasswordParser : public CommandParser
{
    Q_OBJECT
public:
    explicit PasswordParser(QObject *parent = 0);
    virtual ~PasswordParser();

    virtual QString parse(QString& subcmd, QStringList& tokens);

private:
    QString change(QStringList& tokens);
};

#endif // PASSWORDPARSER_H
