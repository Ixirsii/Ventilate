/* Copyright (C) 2015 Ryan Porterfield
 *
 * This file defines all networking commands.
 *
 * $QT_BEGIN_LICENSE:BSD$
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of The Qt Company Ltd nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 *
 * $QT_END_LICENSE$
 */

#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include "account.h"
#include "accountdatabase.h"
#include "chatroom.h"
#include "chatroomdatabase.h"
#include "database.h"
#include "message.h"
#include "messagedatabase.h"
#include "server.h"

Account testAccountDB();
void testMessageDB(Account &acc, ChatRoom &room);
void testRoomDB(ChatRoom &room);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Database::init();
    Server server;
    server.startServer();

    QString email = "RedRaider92@gmail.com";
    QString name = "ShadowHawk54";
    QString password = "password";
    Account acc(name, password, email);
    name = "THANK BIRB";
    ChatRoom room(acc.getUsername(), name);
    room.addModerator(acc.getUsername());
    room.addUser(acc.getUsername());

    acc = testAccountDB();
    testMessageDB(acc, room);
    testRoomDB(room);

    return a.exec();
}

Account testAccountDB()
{
    qDebug() << "Testing account database";
    AccountDatabase db;
    Account tmp = db.find(QString("ShadowHawk54"));
    qDebug() << tmp.getUsername();
    return std::move(tmp);
}

void testMessageDB(Account& acc, ChatRoom& room)
{
    qDebug() << "Testing message database";
    QString msg_str = "Hello World!";
    Message msg(room.getUUID(), acc.getUsername(), msg_str);
    MessageDatabase db;
    Message tmp = db.find(msg.getUUID());
    qDebug() << tmp.getMessage();
}

void testRoomDB(ChatRoom& room)
{
    qDebug() << "Testing room database";
    ChatRoomDatabase db;
    ChatRoom tmp = db.find(room.getUUID());
    qDebug() << tmp.getName();
    qDebug() << tmp.getModerators();
    qDebug() << tmp.getUsers();
    qDebug() << tmp.getMessages();
}
