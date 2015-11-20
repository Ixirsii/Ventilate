#ifndef VENTILATE_LOGIN_H
#define VENTILATE_LOGIN_H

#include <QDialog>
#include "abstractdialog.h"
#include "account.h"
#include "socket.h"

namespace Ui {
class ventilate_login;
}

class ventilate_login : public AbstractDialog
{
    Q_OBJECT

public:
    explicit ventilate_login(Socket& socket, QWidget *parent = 0);
    ~ventilate_login();

    Account getAccount();

public slots:
    void response(QString response);

private slots:
    void on_newUserButton_clicked();
    void on_loginButton_clicked();

    void on_cancelButton_clicked();

private:
    Account account;
    Ui::ventilate_login *ui;
};

#endif // VENTILATE_LOGIN_H
