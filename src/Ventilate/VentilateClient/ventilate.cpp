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
#include "ui_ventilate.h"
#include "ventilate_login.h"

Ventilate::Ventilate(Socket& socket, QWidget *parent)
    : QMainWindow(parent), socket(socket), ui(new Ui::Ventilate)
{
    ui->setupUi(this);
}

Ventilate::~Ventilate()
{
    delete ui;
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

void Ventilate::on_btnSend_clicked()
{
}

void Ventilate::on_btnClear_clicked()
{
    ui->composeText->clear();
    ui->composeText->setFocus();
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
    JoinChatUI join(socket);
    join.setModal(true);
    if (join.exec() == QDialog::Accepted) {
        setChatRoom(join.getChat());
    }
}
