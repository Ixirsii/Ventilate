#include "ventilate_login.h"
#include "ui_ventilate_login.h"
#include "ventilate_newuser.h"
#include <QAbstractButton>
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QUuid>

ventilate_login::ventilate_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventilate_login)
{
    ui->setupUi(this);
}

ventilate_login::~ventilate_login()
{
    delete ui;
}

QUuid ventilate_login::getUser(){
    return QUuid::createUuid();
}

void ventilate_login::on_btnNewUser_clicked()
{
    ventilate_newuser vNewUser;
    vNewUser.setModal(true);
    if(vNewUser.exec() == QDialog::Accepted){

    }else{

    }
}
