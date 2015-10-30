#include "chatroom.h"
#include <QUuid>

ChatRoom::ChatRoom(QString name, QUuid ownerID)
    : uuid(QUuid::createUuid()), name(name), ownerID(ownerID)
{

}

