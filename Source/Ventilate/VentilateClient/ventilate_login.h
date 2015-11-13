#ifndef VENTILATE_LOGIN_H
#define VENTILATE_LOGIN_H

#include <QDialog>

namespace Ui {
class ventilate_login;
}

class ventilate_login : public QDialog
{
    Q_OBJECT

public:
    explicit ventilate_login(QWidget *parent = 0);
    QUuid getUser();
    ~ventilate_login();

private slots:
    void on_btnNewUser_clicked();

private:
    Ui::ventilate_login *ui;
};

#endif // VENTILATE_LOGIN_H
