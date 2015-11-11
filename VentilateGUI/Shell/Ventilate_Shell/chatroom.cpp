#include <QString>
#include <QList>
#include "chatroom.h"

chatroom::chatroom(QString name, QUuid ownerID)
    : uuid(QUuid::createUuid()), name(name), ownerID(ownerID){

}

void chatroom::setMods(QList<QString> m){
    moderators = m;
}

void chatroom::setUsers(QList<QString> u){
    users = u;
}

void chatroom::setOwnerID(QUuid o){
    ownerID = o;
}

QString chatroom::getName(){
    return name;
}

QList<QString> chatroom::getMods(){
    return moderators;
}

QList<QString> chatroom::getUsers(){
    return users;
}

QUuid chatroom::getChatID(){
    return  uuid;
}

QUuid chatroom::getOwnerID(){
    return ownerID;
}


