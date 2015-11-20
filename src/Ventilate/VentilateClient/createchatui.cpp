#include "createchatui.h"

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <cstdlib>
#include <QListWidgetItem>
#include <QList>
#include <QUuid>

#include "account.h"
#include "chatroom.h"
#include "socket.h"
#include "ui_ventilate_createchat.h"
#include "server/commandparser.h"

CreateChatUI::CreateChatUI(Account& account, Socket& socket, QWidget *parent)
    : AbstractDialog(socket, parent), account(account),
      ui(new Ui::CreateChatUI)
{
    ui->setupUi(this);
}

CreateChatUI::~CreateChatUI()
{
    delete ui;
}

ChatRoom CreateChatUI::getChat()
{
    return std::move(chat);
}

void CreateChatUI::on_cancelButton_clicked()
{
    reject();
}

void CreateChatUI::on_createButton_clicked()
{
    QString roomName = ui->chatNameText->text();
    QString data = CommandParser::ROOM + " " + CommandParser::CREATE + " ";
    data += roomName + " " + account.getUsername();
    getSocket().send(data);
}

void CreateChatUI::response(QString response)
{
    qDebug() << "CreateChatUI::response(" << response << ")";
    /* This REALLY needs to be more state based */
    if (response == CommandParser::ACCEPT) {
        QString name = ui->chatNameText->text();
        ChatRoom::requestChat(getSocket(), name);
    } else if (response.startsWith(CommandParser::ROOM + " "
                                   + CommandParser::SEND)) {
        QString roomStr = response.section(' ', 2, -1);
        chat = ChatRoom::fromString(roomStr);
        accept();
    } else {
        qDebug() << "Something went wrong";
        reject();
    }
}
