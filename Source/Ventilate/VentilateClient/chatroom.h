#ifndef CHATROOM_H
#define CHATROOM_H

#include <QDateTime>
#include <QList>
#include <QString>
#include <QUuid>
#include "message.h"

class ChatRoom
{
public:
    explicit ChatRoom(QString name);
    virtual ~ChatRoom();

    void addMessage(QDateTime timestamp, QString user, QString message);
    QString getMessages();
    QList<QString> getUsers();

private:
    const QUuid uuid;
    const QString name;
    QUuid ownerID;
    QList<QUuid> moderators;
    QList<QUuid> users;
    QList<Message> messages;

    QString serializeMessage(QDateTime timestamp, QString user, QString message);
};

#endif // CHATROOM_H
