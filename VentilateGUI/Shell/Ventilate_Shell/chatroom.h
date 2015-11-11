#ifndef CHATROOM_H
#define CHATROOM_H

#include <QString>
#include <QList>
#include <QUuid>

class chatroom
{
public:
    explicit chatroom(QString name, QUuid ownerID);
public:
    void setPrivate(QString name, QList<QString> mods, QList<QString> users);
    void setPublic(QString name, QList<QString> mods);
    QUuid getOwnerID();
    void setOwnerID(QUuid o);
    QUuid getChatID();
    QString getName();
    void setMods(QList<QString> m);
    QList<QString> getMods();
    void setUsers(QList<QString> u);
    QList<QString> getUsers();
private:
    const QUuid uuid;
    const QString name;
    QUuid ownerID;
    QList< QString > moderators;
    QList< QString > users;
    QList< QString > messages;
};

#endif // CHATROOM_H
