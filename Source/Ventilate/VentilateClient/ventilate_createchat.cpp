#include "ventilate_createchat.h"
#include "ui_ventilate_createchat.h"
#include "chatroom.h"
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <cstdlib>
#include <QListWidgetItem>
#include <QList>
#include <QUuid>

ventilate_createchat::ventilate_createchat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventilate_createchat)
{
    ui->setupUi(this);
}

ventilate_createchat::~ventilate_createchat()
{
    delete ui;
}

void ventilate_createchat::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button->text() == "Reset") reset();
}

void ventilate_createchat::reset()
{
    // Public
    ui->lnedChatName_Pb->clear();
    ui->lnedModerator_Pb->clear();
    ui->lstModerators_Pb->clear();
    // Private
    ui->lnedChatName_Pv->clear();
    ui->lnedModerator_Pv->clear();
    ui->lnedUser_Pv->clear();
    ui->lstModerators_Pv->clear();
    ui->lstUsers_Pv->clear();
    if(!ui->cboPb_Pv->currentIndex()) ui->lnedChatName_Pb->setFocus();
    if(ui->cboPb_Pv->currentIndex()) ui->lnedChatName_Pv->setFocus();
}

chatroom ventilate_createchat::getinfo(QUuid ownerID){
    if(!ui->cboPb_Pv->currentIndex()){
        QList<QString> ql;
        for(int i = 0; i < ui->lstModerators_Pb->count(); i++){
            ql.push_back(ui->lstModerators_Pb->item(i)->text());
        }
        chatroom cr = chatroom(ui->lnedChatName_Pb->text(), QUuid::createUuid());
        cr.setOwnerID(ownerID);
        cr.setMods(ql);
        ql.clear();
        cr.setUsers(ql);
        return cr;
    }else{
        QList<QString> qlm, qlu;
        for(int i = 0; i < ui->lstModerators_Pv->count(); i++){
            qlm.push_back(ui->lstModerators_Pv->item(i)->text());
        }
        for(int i = 0; i < ui->lstUsers_Pv->count(); i++){
            qlu.push_back(ui->lstUsers_Pv->item(i)->text());
        }
        chatroom cr = chatroom(ui->lnedChatName_Pv->text(), QUuid::createUuid());
        cr.setMods(qlm);
        cr.setUsers(qlu);
        return cr;
    }
}

void ventilate_createchat::on_cboPb_Pv_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

/*
 *
 *  Private
 *
 *
 */
void ventilate_createchat::on_btnMtR_Pv_clicked()
{
    if(ui->lstModerators_Pv->currentItem() != NULL){
        QListWidgetItem *item = ui->lstModerators_Pv->currentItem();
        ui->lstUsers_Pv->addItem(item->text());
        ui->lstModerators_Pv->takeItem(ui->lstModerators_Pv->currentIndex().row());
    }
}

void ventilate_createchat::on_btnRtM_Pv_clicked()
{
    if(ui->lstUsers_Pv->currentItem() != NULL){
        QListWidgetItem *item = ui->lstUsers_Pv->currentItem();
        ui->lstModerators_Pv->addItem(item->text());
        ui->lstUsers_Pv->takeItem(ui->lstUsers_Pv->currentIndex().row());
    }
}

void ventilate_createchat::on_btnAddModerator_Pv_clicked()
{
    bool found = false;
    if(ui->lnedModerator_Pv->text() == "" || ui->lnedModerator_Pv->text() == NULL){
        QMessageBox::warning(this, "Input Error", "<font color='#FFFFFF'>The moderator text box must be filled before pressing add<font/>");
    }else{
        for(int i = 0; i < ui->lstModerators_Pv->count(); i++){
            if(ui->lstModerators_Pv->item(i)->text() == ui->lnedModerator_Pv->text()){
                found = true;
                break;
            }
        }
        for(int i = 0; i < ui->lstUsers_Pv->count(); i++){
            if(ui->lstUsers_Pv->item(i)->text() == ui->lnedModerator_Pv->text()){
                found = true;
                break;
            }
        }
        if(found){
            QMessageBox::information(this, "Invalid Input", "<font color='#FFFFFF'>Username already in a list" + ui->lnedModerator_Pv->text() + ", was already entered.<font/>");
        }else{
            ui->lstModerators_Pv->addItem(ui->lnedModerator_Pv->text());
        }
    }
}

void ventilate_createchat::on_btnRemoveModerator_Pv_clicked()
{
    bool found = false;
    if(ui->lnedModerator_Pv->text() != "" || ui->lnedModerator_Pv->text() != NULL){
        for(int i = 0; i < ui->lstModerators_Pv->count();i++){
            if(ui->lstModerators_Pv->item(i)->text() == ui->lnedModerator_Pv->text()){
                ui->lstModerators_Pv->takeItem(i);
                found = true;
            }
        }
        if(!found) QMessageBox::information(this, "Invalid Input", "User not found", "<font color='#FFFFFF'>" + ui->lnedModerator_Pv->text() + ", was not found in the moderators list.<font/>");
    }else{
        QMessageBox::warning(this, "Input Error", "<font color='#FFFFFF'>The moderator text box must be filled before pressing add<font/>");
    }

}

void ventilate_createchat::on_btnAddUser_Pv_clicked()
{
    bool found = false;
    if(ui->lnedUser_Pv->text() == "" || ui->lnedUser_Pv->text() == NULL){
        QMessageBox::warning(this, "Input Error", "<font color='#FFFFFF'>The user text box must be filled before pressing add<font/>");
    }else{
        for(int i = 0; i < ui->lstModerators_Pv->count(); i++){
            if(ui->lstModerators_Pv->item(i)->text() == ui->lnedUser_Pv->text()){
                found = true;
                break;
            }
        }
        for(int i = 0; i < ui->lstUsers_Pv->count(); i++){
            if(ui->lstUsers_Pv->item(i)->text() == ui->lnedUser_Pv->text()){
                found = true;
                break;
            }
        }
        if(found){
            QMessageBox::information(this, "Invalid Input", "<font color='#FFFFFF'>Username already in a list" + ui->lnedUser_Pv->text() + ", was already entered.<font/>");
        }else{
            ui->lstUsers_Pv->addItem(ui->lnedUser_Pv->text());
        }
    }
}

void ventilate_createchat::on_btnRemoveUser_Pv_clicked()
{
    bool found = false;
    for(int i = 0; i < ui->lstUsers_Pv->count();i++){
        if(ui->lstUsers_Pv->item(i)->text() == ui->lnedUser_Pv->text()){
            ui->lstUsers_Pv->takeItem(i);
            found = true;
        }
    }
    if(!found) QMessageBox::information(this, "User not found", "<font color='#FFFFFF'>" + ui->lnedUser_Pv->text() + ", was not found in the users list.<font/>");
}

/*
 *
 *  Public
 *
 *
 */

void ventilate_createchat::on_btnAddModerator_Pb_clicked()
{
    if(ui->lnedModerator_Pb->text() != ""){
        ui->lstModerators_Pb->addItem(ui->lnedModerator_Pb->text());
    }else{
        QMessageBox::warning(this, "Input Error", "<font color='#FFFFFF'>The moderator text box must be filled before pressing add<font/>");
    }
}

void ventilate_createchat::on_btnRemoveModerator_Pb_clicked()
{
    bool found = false;
    if(ui->lnedModerator_Pb->text() != ""){
        for(int i = 0; i < ui->lstModerators_Pb->count();i++){
            if(ui->lstModerators_Pb->item(i)->text() == ui->lnedModerator_Pb->text()){
                ui->lstModerators_Pb->takeItem(i);
                found = true;
            }
        }
        if(!found) QMessageBox::information(this, "User not found", ui->lnedModerator_Pb->text() + ", was not found in the moderators list.");
    }else{
        QMessageBox::information(this, "Invalid Input", "<font color='#FFFFFF'>The moderator textbox requires a username.<font/>");
    }
}

void ventilate_createchat::on_lnedModerator_Pb_returnPressed()
{
    on_btnAddModerator_Pb_clicked();
    ui->lnedModerator_Pb->clear();
    ui->lnedModerator_Pb->setFocus();
}

void ventilate_createchat::on_lnedModerator_Pv_returnPressed()
{
    on_btnAddModerator_Pv_clicked();
    ui->lnedModerator_Pv->clear();
    ui->lnedModerator_Pv->setFocus();
}
