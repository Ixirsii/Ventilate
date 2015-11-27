#include "networktask.h"
#include <QDebug>
#include <QString>
#include <QStringList>
#include "server/accountparser.h"
#include "server/commandparser.h"
#include "server/passwordparser.h"
#include "server/peerparser.h"
#include "server/roomparser.h"

NetworkTask::NetworkTask(ConnectionHandler &handler, QString fullcmd,
                         std::vector<ConnectionHandler>& clients,
                         QObject *parent)
    : QObject(parent), handler(handler), fullcmd(fullcmd), clients(clients)
{
}

/*!
 * \brief Handle requests from the clients.
 *
 * This function gets called any time a ConnectionHandler recieves a request
 * from a client over the network. Some preliminary command parsing is done,
 * then the handler and command stream are passed off to an appropriate
 * CommandParser sub-class to handle the command.
 */
void NetworkTask::run()
{
    QString cmd, subcmd;
    QStringList tokens;
    qDebug() << "Got string: " << fullcmd << " from stream";
    tokens = fullcmd.split(CommandParser::SEP);
    QStringList::iterator iter = tokens.begin();
    cmd = *iter;
    iter = tokens.erase(iter);
    subcmd = *iter;
    iter = tokens.erase(iter);
    parseRequest(cmd, subcmd, tokens);
}

void NetworkTask::parseRequest(QString &cmd, QString &subcmd,
                               QStringList &tokens)
{
    qDebug() << "Command: " << cmd << " - Subcommand: " << subcmd;
    if (cmd == CommandParser::ROOM) {
        RoomParser parser;
        connect(&parser, SIGNAL(propogate(QString)),
                &handler, SLOT(propogate(QString)));
        emit result(parser.parse(subcmd, tokens));
        disconnect(&parser, SIGNAL(propogate(QString)),
                &handler, SLOT(propogate(QString)));
    } else if (cmd == CommandParser::ACCOUNT)
        emit result(AccountParser().parse(subcmd, tokens));
    else if (cmd == CommandParser::PEER)
        emit result(PeerParser(handler).parse(subcmd, tokens));
    else if (cmd == CommandParser::PASSWORD)
        emit result(PasswordParser().parse(subcmd, tokens));
    // Drop incorrectly formatted requests
}
