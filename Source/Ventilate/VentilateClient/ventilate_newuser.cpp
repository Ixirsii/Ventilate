#include "ventilate_newuser.h"
#include "ui_ventilate_newuser.h"

ventilate_newuser::ventilate_newuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventilate_newuser)
{
    ui->setupUi(this);
}

ventilate_newuser::~ventilate_newuser()
{
    delete ui;
}

void ventilate_newuser::on_lnedUsername_textChanged(const QString &arg1)
{

}

void ventilate_newuser::on_lnedPassword_textChanged(const QString &arg1)
{

}

void ventilate_newuser::on_lnedConfirmPass_textChanged(const QString &arg1)
{

}

void ventilate_newuser::on_btnSubmit_clicked()
{

}

void ventilate_newuser::on_btnCancel_clicked()
{
    this->close();
}
