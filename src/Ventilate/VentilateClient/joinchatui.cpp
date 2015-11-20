#include "joinchatui.h"
#include <QString>
#include "abstractdialog.h"
#include "socket.h"
#include "ui_joinchatui.h"
#include "server/commandparser.h"

JoinChatUI::JoinChatUI(Socket& socket, QWidget *parent)
    : AbstractDialog(socket, parent), ui(new Ui::JoinChatUI)
{
    ui->setupUi(this);
}

JoinChatUI::~JoinChatUI()
{
    delete ui;
}

ChatRoom JoinChatUI::getChat()
{
    return chat;
}

void JoinChatUI::on_cancelButton_clicked()
{
    reject();
}

void JoinChatUI::on_joinButton_clicked()
{
        QString name = ui->chatNameText->text();
        ChatRoom::requestChat(getSocket(), name);
}

void JoinChatUI::response(QString response)
{
    qDebug() << "CreateChatUI::response(" << response << ")";
    /* This REALLY needs to be more state based */
    if (response.startsWith(CommandParser::ROOM + " "
                                   + CommandParser::SEND)) {
        QString roomStr = response.section(' ', 2, -1);
        chat = ChatRoom::fromString(roomStr);
        accept();
    } else {
        qDebug() << "Something went wrong";
        reject();
    }
}
