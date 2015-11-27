/*! \file
 * \brief Parses ChatRoom and Message based network requests.
 * \author Ryan Porterfield
 * \since 2015-11-12
 * \copyright 2015-11-10
 */

#ifndef ROOMPARSER_H
#define ROOMPARSER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include "message.h"
#include "commandparser.h"

class RoomParser : public CommandParser
{
    Q_OBJECT
public:
    explicit RoomParser(QObject *parent = 0);
    virtual ~RoomParser();

    virtual QString parse(QString &subcmd, QStringList &tokens);

signals:
    void propogate(QString message);

private:
    // Command functions
    QString add(QStringList &tokens);
    QString create(QStringList &tokens);
    QString get(QStringList &tokens);
    QString history(QStringList &tokens);
    QString join(QStringList &tokens);
    QString leave(QStringList &tokens);
    QString list(QStringList &tokens);
    QString message(QStringList &tokens);
    QString mode(QStringList &tokens);
    QString remove(QStringList &tokens);


    // Helper functions
    Message buildMessage(QStringList &tokens);
    bool inRoom(QString &username, QUuid &room);
};

#endif // ROOMPARSER_H
