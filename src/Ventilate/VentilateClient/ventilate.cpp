/*! \file
 * \brief
 * \author Jacob Pebworth
 * \author Ryan Porterfield
 * \since 2015-11-11
 * \copyright BSD 3 Clause
 */

#include "ventilate.h"
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QDateTime>
#include <QWidget>
#include <vector>

#include "chatroom.h"
#include "createchatui.h"
#include "joinchatui.h"
#include "message.h"
#include "ui_ventilate.h"
#include "ventilate_login.h"
#include "server/commandparser.h"

Ventilate::Ventilate(Socket& socket, QWidget *parent)
    : QMainWindow(parent), socket(socket), ui(new Ui::Ventilate)
{
    ui->setupUi(this);
    connect(&(this->socket), SIGNAL(response(QString)), this, SLOT(response(QString)));
}

Ventilate::~Ventilate()
{
    delete ui;
    disconnect(&(this->socket), SIGNAL(response(QString)), this, SLOT(response(QString)));
}

void Ventilate::on_actionCreate_Chat_room_triggered()
{
    CreateChatUI createChat(account, socket);
    createChat.setModal(true);
    if (createChat.exec() == QDialog::Accepted) {
        setChatRoom(createChat.getChat());
    }
}

void Ventilate::on_actionLogin_triggered()
{
    ventilate_login vlogin(socket);
    vlogin.setModal(true);
    if (vlogin.exec() == QDialog::Accepted) {
        account = vlogin.getAccount();
        ui->currentUserLabel->setText(account.getUsername());
    }
}

void Ventilate::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void Ventilate::on_actionLogout_triggered()
{
    UserID = NULL;
}

void Ventilate::on_actionAbout_Ventilate_triggered()
{
    QMessageBox::about(this, "About Ventilate", "");
}

void Ventilate::on_actionLeave_Chat_room_triggered()
{
}

void Ventilate::onChatRoomChanged()
{
    ui->userListView->clear();
    ui->userListView->addItem(chat.getOwner());
    ui->userListView->addItems(chat.getUsers());
    ui->chatNameLabel->setText(chat.getName());
    ui->messageWindow->setPlainText(chat.getMessages());
}

void Ventilate::setChatRoom(ChatRoom chat)
{
    this->chat = chat;
    onChatRoomChanged();
}

void Ventilate::on_actionJoin_Chat_room_triggered()
{
    JoinChatUI join(socket, account);
    join.setModal(true);
    if (join.exec() == QDialog::Accepted) {
        setChatRoom(join.getChat());
    }
}

void Ventilate::on_sendButton_clicked()
{
    QString message = ui->composeText->text();
    Message msg(chat.getUUID(), account.getUsername(), message);
    publishMessage(msg);
    QString cmd = CommandParser::ROOM + CommandParser::SEP;
    cmd += CommandParser::MESSAGE + CommandParser::SEP;
    cmd += msg.toString();
    socket.send(cmd);
}

void Ventilate::publishMessage(Message& msg)
{
    if (received.contains(msg.getUUID()))
        return;
    received.insert(msg.getUUID());
    ui->messageWindow->append(msg.getFormattedMessage());
    ui->composeText->clear();
}

void Ventilate::response(QString response)
{
    qDebug() << "Ventilate::response(" << response << ")";
    /* This REALLY needs to be more state based */
    if (response.startsWith(CommandParser::ROOM + CommandParser::SEP
                                   + CommandParser::MESSAGE)) {
        QString message = response.section(CommandParser::SEP, 2, -1);
        Message msg = Message::fromString(message);
        publishMessage(msg);
    } else {
        qDebug() << "Something went wrong";
    }
}
