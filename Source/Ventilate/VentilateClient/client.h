#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include <QList>
#include <QSet>
#include "account.h"
#include "chatroom.h"
#include "chatroomlistener.h"
#include "socket.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client();

    void onMessageRecieved(Message& message, Socket& sender);
    void registerListener(ChatRoomListener& listener);
    void unregisterListener(ChatRoomListener& listener);

private:
    QList< ChatRoom > chatRooms;
    QList< ChatRoomListener > listeners;
    QList< Socket > peers;
    QSet< QUuid > recentMessages;
    //Socket server;
    //Account userAccount;

    void cleanRecentMessages();
    void processMessage(Message& message);
    void propagateMessage(Message& message, Socket& sender);
};

#endif // CLIENT_H
