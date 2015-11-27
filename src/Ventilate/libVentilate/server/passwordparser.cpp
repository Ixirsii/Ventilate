#include "passwordparser.h"
#include <QStringList>

PasswordParser::PasswordParser(QObject *parent)
    : CommandParser(parent)
{
}


PasswordParser::~PasswordParser()
{
}

QString PasswordParser::change(QStringList& tokens)
{
    return REJECT;
}

QString PasswordParser::parse(QString& subcmd, QStringList& tokens)
{
    return REJECT;
}
