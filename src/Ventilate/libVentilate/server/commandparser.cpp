/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#include "commandparser.h"

/* ************************************************************************* *
 *                            Command Definitions                            *
 * ************************************************************************* */

const QString CommandParser::ACCEPT = "ACCEPT";
const QString CommandParser::ACCOUNT = "ACCOUNT";
const QString CommandParser::ADD = "ADD";
const QString CommandParser::CHANGE = "CHANGE";
const QString CommandParser::CREATE = "CREATE";
const QString CommandParser::DELETE = "DELETE";
const QString CommandParser::GET = "GET";
const QString CommandParser::HISTORY = "HISTORY";
const QString CommandParser::JOIN = "JOIN";
const QString CommandParser::LEAVE = "LEAVE";
const QString CommandParser::LIST = "LIST";
const QString CommandParser::LIST_SEPARATOR = " \\SEP\\ ";
const QString CommandParser::LOGIN = "LOGIN";
const QString CommandParser::MESSAGE = "MESSAGE";
const QString CommandParser::MODE = "MODE";
const QString CommandParser::PASSWORD = "PASSWORD";
const QString CommandParser::PEER = "PEER";
const QString CommandParser::REJECT = "REJECT";
const QString CommandParser::REQUEST = "REQUEST";
const QString CommandParser::RESET = "RESET";
const QString CommandParser::ROOM = "ROOM";
const QString CommandParser::SEND = "SEND";

const QString CommandParser::GENERIC_ERROR = "An unkown error occurred";
const QString CommandParser::INVALID_PASSWORD = "Invalid password";

CommandParser::CommandParser()
{
}


CommandParser::~CommandParser()
{
}
