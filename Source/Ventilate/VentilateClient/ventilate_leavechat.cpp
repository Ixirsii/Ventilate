#include "ventilate_leavechat.h"
#include "ui_ventilate_leavechat.h"

ventilate_leavechat::ventilate_leavechat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventilate_leavechat)
{
    ui->setupUi(this);
}

ventilate_leavechat::~ventilate_leavechat()
{
    delete ui;
}
