#include "ventilate_login.h"
#include <QAbstractButton>
#include <QByteArray>
#include <QDataStream>
#include <QDialog>
#include <QIODevice>
#include <QString>
#include <QMessageBox>
#include <QUuid>
#include "account.h"
#include "ui_ventilate_login.h"
#include "ventilate_newuser.h"
#include "server/commandparser.h"

ventilate_login::ventilate_login(Socket& socket, QWidget *parent) :
    AbstractDialog(socket, parent), ui(new Ui::ventilate_login)
{
    ui->setupUi(this);
}

ventilate_login::~ventilate_login()
{
    delete ui;
}

Account ventilate_login::getAccount()
{
    return std::move(account);
}

void ventilate_login::on_newUserButton_clicked()
{
    ventilate_newuser vNewUser(getSocket());
    vNewUser.setModal(true);
    if(vNewUser.exec() == QDialog::Accepted){

    } else {

    }
}

void ventilate_login::response(QString response)
{
    qDebug() << "ventilate_login::response(" << response << ")";
    /* This REALLY needs to be more state based */
    if (response == CommandParser::ACCEPT) {
        QString username = ui->usernameText->text();
        Account::requestAccount(getSocket(), username);
    } else if (response.startsWith(
                   CommandParser::ACCOUNT + " " + CommandParser::SEND)) {
        QString accountStr = response.section(' ', 2, -1);
        account = Account::fromString(accountStr);
        accept();
    } else {
        qDebug() << "Something went wrong";
    }
}

void ventilate_login::on_loginButton_clicked()
{

    QString username = ui->usernameText->text();
    QString password = ui->passwordText->text();
    QByteArray phash = Account::hashPassword(password, username);
    QString data = CommandParser::ACCOUNT + " " + CommandParser::LOGIN + " ";
    data += username + " " + QString(phash.data());
    getSocket().send(data);
}

void ventilate_login::on_cancelButton_clicked()
{
    reject();
}
