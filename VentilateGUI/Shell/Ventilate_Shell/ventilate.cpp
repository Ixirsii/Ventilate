#include "ventilate.h"
#include "ui_ventilate.h"
#include "ventilate_createchat.h"
#include "ventilate_login.h"
#include "chatroom.h"
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QDateTime>
#include <QWidget>

Ventilate::Ventilate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ventilate)
{
    ui->setupUi(this);
    ui->tbwChatrooms->setCurrentIndex(0);
    ui->t0->setWindowTitle("Public");
}

Ventilate::~Ventilate()
{
    delete ui;
}

void Ventilate::on_actionCreate_Chat_room_triggered()
{
    ventilate_createchat createchat;
    createchat.setModal(true);
    if(createchat.exec() == QDialog::Accepted){
        chatroom cr = createchat.getinfo(UserID);
        int index = ui->tbwChatrooms->count() + 1;
        switch (index) {
        case 1:
            QListWidget *lst_t1;
            lst_t1->setObjectName("lst_t1");
            lst_t1->setStyleSheet("background-color:rgb(255,255,255);\ncolor:rgb(0,0,0);");
            ui->tbwChatrooms->addTab( new QWidget(lst_t1) , "t1");
            break;
        default:
            break;
        }
    }else{

    }
}

void Ventilate::on_actionLogin_triggered()
{
    ventilate_login vlogin;
    vlogin.setModal(true);
    if(vlogin.exec() == QDialog::Accepted){
        UserID = vlogin.getUser();
        QMessageBox::information(this,"UserID", "User ID: " + UserID.toString());
    }else{

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
    int index = ui->tbwChatrooms->currentIndex();

}

void Ventilate::on_btnClear_clicked()
{
    ui->ptxtMessageBox->clear();
    ui->ptxtMessageBox->setFocus();
}

void Ventilate::on_btnAddTab_clicked()
{

}

void Ventilate::on_btnTabInfo_clicked()
{

}
