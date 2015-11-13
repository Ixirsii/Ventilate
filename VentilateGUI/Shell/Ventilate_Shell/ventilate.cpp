#include "ventilate.h"
#include "ui_ventilate.h"
#include "ventilate_createchat.h"
#include "ventilate_login.h"
#include "chatroom.h"
#include "chatscreen.h"
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QDateTime>
#include <QWidget>
#include <vector>

Ventilate::Ventilate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ventilate)
{
    ui->setupUi(this);
    for(int i = 1; i < 6; i++){
        ui->tbwChatrooms->setTabText(i, "");
    }
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
    switch (index) {
    case 0:
        ui->lst0->addItem(+ "<" + QDateTime::currentDateTime().toString("MM/dd/yyyy") + "> " + ui->ptxtMessageBox->toPlainText());
        break;
    case 1:
        ui->lst1->addItem(+ "<" + QDateTime::currentDateTime().toString("MM/dd/yyyy") + "> " + ui->ptxtMessageBox->toPlainText());
        break;
    case 2:
        ui->lst2->addItem(+ "<" + QDateTime::currentDateTime().toString("MM/dd/yyyy") + "> " + ui->ptxtMessageBox->toPlainText());
        break;
    case 3:
        ui->lst3->addItem(+ "<" + QDateTime::currentDateTime().toString("MM/dd/yyyy") + "> " + ui->ptxtMessageBox->toPlainText());
        break;
    case 4:
        ui->lst4->addItem(+ "<" + QDateTime::currentDateTime().toString("MM/dd/yyyy") + "> " + ui->ptxtMessageBox->toPlainText());
        break;
    case 5:
        ui->lst5->addItem(+ "<" + QDateTime::currentDateTime().toString("MM/dd/yyyy") + "> " + ui->ptxtMessageBox->toPlainText());
        break;
    default:
        break;
    }

}

void Ventilate::on_btnClear_clicked()
{
    ui->ptxtMessageBox->clear();
    ui->ptxtMessageBox->setFocus();
}

void Ventilate::on_btnAddTab_clicked()
{
    if(ui->tbwChatrooms->count() <= 6){
        ui->tbwChatrooms->addTab(new chatscreen, tr("Tab %0").arg(QString::number(ui->tbwChatrooms->count())));
    }else{
        QMessageBox::warning(this, "Too Many Open Tabs", "Please leave a chat-room if you wish to open another");
    }
}

void Ventilate::on_btnTabInfo_clicked()
{
    QString msg = "Tab Texts";
    for(int i = 1; i < 6; i++){
        msg += ui->tbwChatrooms->tabText(i) + "\n";
    }
    msg += QString::number(ui->tbwChatrooms->count());
    QMessageBox::information(this, "Tab texts", msg);
}

void Ventilate::on_tbwChatrooms_tabCloseRequested(int index)
{
    ui->tbwChatrooms->setTabText(index, "");
    ui->tbwChatrooms->removeTab(index);
}
