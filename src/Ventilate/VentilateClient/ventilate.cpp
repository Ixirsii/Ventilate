/*! \file
 * \brief
 * \author Jacob Pebworth
 * \author Ryan Porterfield
 * \since 2015-11-11
 * \copyright BSD 3 Clause
 */

#include "ventilate.h"
#include "ui_ventilate.h"
#include "createchatui.h"
#include "ventilate_login.h"
#include "chatroom.h"
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QDateTime>
#include <QWidget>
#include <vector>

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
    CreateChatUI createchat;
    createchat.setModal(true);
    if (createchat.exec() == QDialog::Accepted) {
        //chatroom cr = createchat.getinfo(UserID);
    } else {

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
