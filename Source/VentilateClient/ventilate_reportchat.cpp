#include "ventilate_reportchat.h"
#include "ui_ventilate_reportchat.h"

ventilate_reportchat::ventilate_reportchat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventilate_reportchat)
{
    ui->setupUi(this);
}

ventilate_reportchat::~ventilate_reportchat()
{
    delete ui;
}
