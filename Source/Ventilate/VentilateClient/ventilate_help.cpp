#include "ventilate_help.h"
#include "ui_ventilate_help.h"

ventilate_help::ventilate_help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventilate_help)
{
    ui->setupUi(this);
}

ventilate_help::~ventilate_help()
{
    delete ui;
}
