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
    ChatRoom(const ChatRoom& copy);
    ChatRoom(ChatRoom&& move);
    explicit ChatRoom(const QString& owner, const QString& name);
    explicit ChatRoom(const QUuid& uuid, const QString& owner,
                      const QString& name);

    void addMessage(const Message& message);
    void addMessages(const QList<Message>& messages);
    void addModerator(const QString& mod);
    void addModerators(const QList<QString>& mods);
    void addUser(const QString& user);
    void addUsers(const QList<QString>& users);
    QString getMessages();
    const QString& getName() const;
    const QString& getOwner() const;
    const QList<QString>& getModerators() const;
    const QUuid& getUUID() const;
    const QList<QString>& getUsers() const;

    ChatRoom& operator=(const ChatRoom& copy);
    ChatRoom& operator=(ChatRoom&& move);
    friend QDataStream& operator<<(QDataStream& out, const ChatRoom& room);
    friend QDataStream& operator>>(QDataStream& in, ChatRoom& room);

private:
    QUuid uuid;
    QString owner;
    QString name;
    QList<QString> moderators;
    QList<QString> users;
    QList<Message> messages;

    QString serializeMessage(const Message& message);
};

#endif // CHATROOM_H
