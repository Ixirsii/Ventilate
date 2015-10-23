#include "ventilate_joinchat.h"
#include "ui_ventilate_joinchat.h"

ventilate_joinchat::ventilate_joinchat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventilate_joinchat)
{
    ui->setupUi(this);
}

ventilate_joinchat::~ventilate_joinchat()
{
    delete ui;
}
