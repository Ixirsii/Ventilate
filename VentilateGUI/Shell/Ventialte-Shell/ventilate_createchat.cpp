#include "ventilate_createchat.h"
#include "ui_ventilate_createchat.h"

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

void ventilate_createchat::on_cboPBorPV_currentIndexChanged(int index)
{

}

void ventilate_createchat::on_rbtnPBUattnYes_clicked()
{

}

void ventilate_createchat::on_rbtnPBUattnNo_clicked()
{

}

void ventilate_createchat::on_rbtnPBExitYes_clicked()
{

}

void ventilate_createchat::on_rbtnPBExitNo_clicked()
{

}
