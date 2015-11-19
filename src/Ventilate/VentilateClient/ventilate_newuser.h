#ifndef VENTILATE_NEWUSER_H
#define VENTILATE_NEWUSER_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QAbstractButton>
#include "socket.h"

namespace Ui {
class ventilate_newuser;
}

class ventilate_newuser : public QDialog
{
    Q_OBJECT

public:
    explicit ventilate_newuser(Socket& socket, QWidget *parent = 0);
    ~ventilate_newuser();

private slots:

    void on_buttonBox_clicked(QAbstractButton *button);
    void on_buttonBox_accepted();

private:
    Socket& socket;
    Ui::ventilate_newuser *ui;
};

#endif // VENTILATE_NEWUSER_H
