/*! \file
 * \brief Provides data types for modeling chat rooms.
 * \author Ryan Porterfield
 * \since 2015-10-30
 * \copyright 2015-11-10
 */

#ifndef CHATROOM_H
#define CHATROOM_H

#include <QDateTime>
#include <QList>
#include <QString>
#include <QUuid>
#include "libventilate_global.h"
#include "message.h"
#include "socket.h"

class LIBVENTILATESHARED_EXPORT ChatRoom : public QObject
{
    Q_OBJECT
public:
    explicit ChatRoom();
    ChatRoom(const ChatRoom& copy);
    ChatRoom(ChatRoom&& move);
    explicit ChatRoom(const QString& owner, const QString& name);
    explicit ChatRoom(const QUuid& uuid, const QString& owner,
                      const QString& name);

    static ChatRoom fromString(const QString& serialized);
    static void requestChat(Socket& socket, QString& name);

    void addMessage(const Message& message);
    void addMessages(const QList<Message>& messages);
    void addModerator(const QString& mod);
    void addModerators(const QList<QString>& mods);
    void addUser(const QString& user);
    void addUsers(const QList<QString>& users);
    void getHistory();
    QString getMessages();
    const QString& getName() const;
    const QString& getOwner() const;
    const QList<QString>& getModerators() const;
    const QUuid& getUUID() const;
    const QList<QString>& getUsers() const;
    void removeModerator(const QString& mod);
    void removeUser(const QString& user);
    QString toString() const;

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
    static QList<QString> usersFromString(QStringList& list, QStringList::iterator& iter);
};

#endif // CHATROOM_H
