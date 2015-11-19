#include "ventilate_newuser.h"
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QAbstractButton>
#include "account.h"
#include "ui_ventilate_newuser.h"
#include "server/commandparser.h"

ventilate_newuser::ventilate_newuser(Socket& socket, QWidget *parent)
    : QDialog(parent), socket(socket), ui(new Ui::ventilate_newuser)
{
    ui->setupUi(this);
}

ventilate_newuser::~ventilate_newuser()
{
    delete ui;
}

void ventilate_newuser::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button->text() == "Reset"){
        //ui->confirmEmailText->clear();
        //ui->confirmPasswordText->clear();
        ui->emailText->clear();
        ui->passwordText->clear();
        ui->usernameText->clear();
        ui->usernameText->setFocus();
    }
}

void ventilate_newuser::on_buttonBox_accepted()
{
    QString username = ui->usernameText->text();
    QString password = ui->passwordText->text();
    QString email = ui->emailText->text();
    Account acc(username, password, email);
    QString cmd = CommandParser::ACCOUNT + " " + CommandParser::CREATE + " ";
    cmd += acc.getUUID().toString() + " " + acc.getUsername() + " ";
    cmd += acc.getCreationDate().time().toString() + " ";
    cmd += acc.getPasswordHash() + " ";
    cmd += acc.getEmailAddress();
    socket.send(cmd);
    socket.waitForResponse();
}
