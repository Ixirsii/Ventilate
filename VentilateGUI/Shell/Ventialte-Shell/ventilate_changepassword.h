#ifndef VENTILATE_CHANGEPASSWORD_H
#define VENTILATE_CHANGEPASSWORD_H

#include <QDialog>

namespace Ui {
class ventilate_changepassword;
}

class ventilate_changepassword : public QDialog
{
    Q_OBJECT

public:
    explicit ventilate_changepassword(QWidget *parent = 0);
    ~ventilate_changepassword();

private:
    Ui::ventilate_changepassword *ui;
};

#endif // VENTILATE_CHANGEPASSWORD_H
