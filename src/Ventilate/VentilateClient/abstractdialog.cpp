#include "abstractdialog.h"

AbstractDialog::AbstractDialog(QWidget *parent)
    : QDialog(parent)
{
    connect(&(this->socket), SIGNAL(response(QString)), this, SLOT(response(QString)));
}

AbstractDialog::~AbstractDialog()
{
    QObject::disconnect(&(this->socket), SIGNAL(response(QString)), this, SLOT(response(QString)));
}
