#ifndef CHATROOMLISTENER_H
#define CHATROOMLISTENER_H

#include <QUuid>
#include "message.h"

class ChatRoomListener
{
public:
    explicit ChatRoomListener();

    bool listen(Message message);

private:
    const QUuid chatRoomID;
};

#endif // CHATROOMLISTENER_H
