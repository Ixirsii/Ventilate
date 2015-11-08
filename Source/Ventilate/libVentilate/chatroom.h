#ifndef CHATROOM_H
#define CHATROOM_H

#include <QDateTime>
#include <QList>
#include <QString>
#include <QUuid>
#include "libventilate_global.h"
#include "message.h"

class LIBVENTILATESHARED_EXPORT ChatRoom : public QObject
{
    Q_OBJECT
public:
    explicit ChatRoom(QString name, QUuid ownerID);

    void addMessage(QDateTime timestamp, QString user, QString message);
    QString getMessages();
    QList<QString> getUsers();

private:
    const QUuid uuid;
    const QString name;
    QUuid ownerID;
    QList< QString > moderators;
    QList< QString > users;
    QList< Message > messages;

    QString serializeMessage(QDateTime timestamp, QString user, QString message);
};

#endif // CHATROOM_H
