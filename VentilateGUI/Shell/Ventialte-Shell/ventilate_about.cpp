#include "ventilate_about.h"
#include "ui_ventilate_about.h"

ventilate_about::ventilate_about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventilate_about)
{
    ui->setupUi(this);
}

ventilate_about::~ventilate_about()
{
    delete ui;
}
