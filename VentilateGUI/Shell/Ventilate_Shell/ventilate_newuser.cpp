#include "ventilate_newuser.h"
#include "ui_ventilate_newuser.h"
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QAbstractButton>

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

void ventilate_newuser::on_buttonBox_clicked(QAbstractButton *button)
{

}



void ventilate_newuser::on_lnedUsername_textChanged(const QString &arg1)
{
    if(arg1.length() >= 50){
         ui->lblUsernameContextInfo->setText("<font color='#FFFFFF'>" + QString::number(64-arg1.length()) + " characters left.<font/>");
    }else{
        ui->lblUsernameContextInfo->setText("");
    }
}

void ventilate_newuser::on_lnedConfirmPassword_textChanged(const QString &arg1)
{
    if(arg1 != ui->lnedPassword->text()) ui->lblConfirmPasswordContextInfo->setText("<font color='#FFFFFF'>Passwords don't match.<font/>");
    if(arg1 == ui->lnedPassword->text()) ui->lblConfirmPasswordContextInfo->setText("<font color='#FFFFFF'>Passwords match.<font/>");
}

void ventilate_newuser::on_lnedConfirmEmail_textChanged(const QString &arg1)
{
    if(arg1 != ui->lnedEmail->text()) ui->lblConfirmEmailContextInfo->setText("<font color='#FFFFFF'>Emails don't match.<font/>");
    if(arg1 == ui->lnedEmail->text()) ui->lblConfirmEmailContextInfo->setText("<font color='#FFFFFF'>Emails match.<font/>");
}
