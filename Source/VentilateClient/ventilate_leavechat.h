#ifndef VENTILATE_LEAVECHAT_H
#define VENTILATE_LEAVECHAT_H

#include <QDialog>

namespace Ui {
class ventilate_leavechat;
}

class ventilate_leavechat : public QDialog
{
    Q_OBJECT

public:
    explicit ventilate_leavechat(QWidget *parent = 0);
    ~ventilate_leavechat();

private:
    Ui::ventilate_leavechat *ui;
};

#endif // VENTILATE_LEAVECHAT_H
