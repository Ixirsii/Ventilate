#ifndef VENTILATE_NEWUSER_H
#define VENTILATE_NEWUSER_H

#include <QDialog>

namespace Ui {
class ventilate_newuser;
}

class ventilate_newuser : public QDialog
{
    Q_OBJECT

public:
    explicit ventilate_newuser(QWidget *parent = 0);
    ~ventilate_newuser();

private slots:
    void on_lnedUsername_textChanged(const QString &arg1);

    void on_lnedPassword_textChanged(const QString &arg1);

    void on_lnedConfirmPass_textChanged(const QString &arg1);

    void on_btnSubmit_clicked();

    void on_btnCancel_clicked();

private:
    Ui::ventilate_newuser *ui;
};

#endif // VENTILATE_NEWUSER_H
