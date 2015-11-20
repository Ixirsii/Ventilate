#ifndef JOINCHATUI_H
#define JOINCHATUI_H

#include <QDialog>
#include <QString>
#include "abstractdialog.h"
#include "account.h"
#include "chatroom.h"
#include "socket.h"

namespace Ui {
class JoinChatUI;
}

class JoinChatUI : public AbstractDialog
{
    Q_OBJECT

public:
    explicit JoinChatUI(Socket& socket, Account& account, QWidget *parent = 0);
    ~JoinChatUI();

    ChatRoom getChat();

public slots:
    virtual void response(QString response);

private slots:
    void on_cancelButton_clicked();
    void on_joinButton_clicked();

private:
    Account& account;
    ChatRoom chat;
    Ui::JoinChatUI *ui;
};

#endif // JOINCHATUI_H
