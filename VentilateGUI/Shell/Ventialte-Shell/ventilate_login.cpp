#include "ventilate_login.h"
#include "ui_ventilate_login.h"

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

void ventilate_login::on_btnLogin_clicked()
{

}

void ventilate_login::on_btnNewUser_clicked()
{

}
