#include "ventilate_login.h"
#include <QAbstractButton>
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QUuid>
#include "account.h"
#include "ui_ventilate_login.h"
#include "ventilate_newuser.h"

ventilate_login::ventilate_login(Socket& socket, QWidget *parent) :
    QDialog(parent), socket(socket), ui(new Ui::ventilate_login)
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
    ventilate_newuser vNewUser(socket);
    vNewUser.setModal(true);
    if(vNewUser.exec() == QDialog::Accepted){

    } else {

    }
}

void ventilate_login::on_buttonBox_accepted()
{
    QString username = ui->usernameText->text();
    QString password = ui->passwordText->text();
    QByteArray phash = Account::hashPassword(password, username);
    if (Account::authenticateUser(username, phash)) {
        account = Account::getAccount(socket, username);
        this->accept();
    } else {
        this->reject();
    }
}
