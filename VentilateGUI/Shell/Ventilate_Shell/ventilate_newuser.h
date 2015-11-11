#ifndef VENTILATE_NEWUSER_H
#define VENTILATE_NEWUSER_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QAbstractButton>

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
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_lnedUsername_textChanged(const QString &arg1);

    void on_lnedConfirmPassword_textChanged(const QString &arg1);

    void on_lnedConfirmEmail_textChanged(const QString &arg1);

private:
    Ui::ventilate_newuser *ui;
};

#endif // VENTILATE_NEWUSER_H
