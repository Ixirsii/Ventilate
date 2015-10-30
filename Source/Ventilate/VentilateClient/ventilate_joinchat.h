#ifndef VENTILATE_JOINCHAT_H
#define VENTILATE_JOINCHAT_H

#include <QDialog>

namespace Ui {
class ventilate_joinchat;
}

class ventilate_joinchat : public QDialog
{
    Q_OBJECT

public:
    explicit ventilate_joinchat(QWidget *parent = 0);
    ~ventilate_joinchat();

private:
    Ui::ventilate_joinchat *ui;
};

#endif // VENTILATE_JOINCHAT_H
