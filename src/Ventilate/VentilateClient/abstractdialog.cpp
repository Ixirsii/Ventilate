#include "abstractdialog.h"
#include "socket.h"

AbstractDialog::AbstractDialog(Socket& socket, QWidget *parent)
    : QDialog(parent), socket(socket)
{
    connect(&(this->socket), SIGNAL(response(QString)), this, SLOT(response(QString)));
}

AbstractDialog::~AbstractDialog()
{
    disconnect(&(this->socket), SIGNAL(response(QString)), this, SLOT(response(QString)));
}

Socket &AbstractDialog::getSocket()
{
    return socket;
}
