#ifndef VENTILATE_CREATECHAT_H
#define VENTILATE_CREATECHAT_H

#include <QDialog>
#include <QMessageBox>
#include <QAbstractButton>
#include "abstractdialog.h"
#include "account.h"
#include "chatroom.h"
#include "socket.h"

namespace Ui {
class CreateChatUI;
}

class CreateChatUI : public AbstractDialog
{
    Q_OBJECT

public:
    explicit CreateChatUI(Account& account, Socket& socket,
                          QWidget *parent = 0);
    ~CreateChatUI();

    ChatRoom getChat();

public slots:
    virtual void response(QString response);

private slots:
    void on_cancelButton_clicked();
    void on_createButton_clicked();

private:
    Account& account;
    ChatRoom chat;
    Ui::CreateChatUI *ui;
};

#endif // VENTILATE_CREATECHAT_H
