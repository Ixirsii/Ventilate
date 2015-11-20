#ifndef VENTILATE_H
#define VENTILATE_H

#include <QMainWindow>
#include <QUuid>
#include <QSet>
#include <QString>
#include <QStringList>
#include "account.h"
#include "chatroom.h"

namespace Ui {
class Ventilate;
}

class Ventilate : public QMainWindow
{
    Q_OBJECT
private:
    QUuid UserID;
public:
    explicit Ventilate(Socket& socket, QWidget *parent = 0);
    ~Ventilate();

public slots:
    void response(QString response);

private slots:
    void on_actionCreate_Chat_room_triggered();
    void on_actionLogin_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionLogout_triggered();
    void on_actionAbout_Ventilate_triggered();
    void on_actionLeave_Chat_room_triggered();
    void on_actionJoin_Chat_room_triggered();
    void on_sendButton_clicked();

private:
    Account account;
    ChatRoom chat;
    Socket& socket;
    Ui::Ventilate *ui;
    QSet<QUuid> received;

    void onChatRoomChanged();
    void publishMessage(Message& msg);
    void setChatRoom(ChatRoom chat);
};

#endif // VENTILATE_H
