#include "ventilate_changepassword.h"
#include "ui_ventilate_changepassword.h"

ventilate_changepassword::ventilate_changepassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ventilate_changepassword)
{
    ui->setupUi(this);
}

ventilate_changepassword::~ventilate_changepassword()
{
    delete ui;
}
