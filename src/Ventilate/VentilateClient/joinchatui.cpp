#include "joinchatui.h"
#include <QString>
#include "abstractdialog.h"
#include "account.h"
#include "socket.h"
#include "ui_joinchatui.h"
#include "server/commandparser.h"

JoinChatUI::JoinChatUI(Socket& socket, Account& account, QWidget *parent)
    : AbstractDialog(socket, parent), account(account), ui(new Ui::JoinChatUI)
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
    qDebug() << "JoinChatUI::response(" << response << ")";
    /* This REALLY needs to be more state based */
    if (response.startsWith(CommandParser::ROOM + CommandParser::SEP
                                   + CommandParser::SEND)) {
        QString roomStr = response.section(CommandParser::SEP, 2, -1);
        chat = ChatRoom::fromString(roomStr);
        QString join = CommandParser::ROOM + CommandParser::SEP;
        join += CommandParser::JOIN + CommandParser::SEP;
        join += chat.getUUID().toString() + CommandParser::SEP;
        join += account.getUsername();
        getSocket().send(join);
    } else if (response.startsWith(CommandParser::ROOM + CommandParser::SEP
                                   + CommandParser::HISTORY)) {
        //QString history = response.section(CommandParser::SEP, 2, -1);
        //QStringList tokens = history.split(CommandParser::SEP);
    } else if (response.startsWith(CommandParser::ACCEPT)) {
        chat.addUser(account.getUsername());
        accept();
    } else {
        qDebug() << "Something went wrong";
        reject();
    }
}
