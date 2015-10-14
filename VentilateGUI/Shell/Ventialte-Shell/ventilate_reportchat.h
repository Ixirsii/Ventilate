#ifndef VENTILATE_REPORTCHAT_H
#define VENTILATE_REPORTCHAT_H

#include <QDialog>

namespace Ui {
class ventilate_reportchat;
}

class ventilate_reportchat : public QDialog
{
    Q_OBJECT

public:
    explicit ventilate_reportchat(QWidget *parent = 0);
    ~ventilate_reportchat();

private:
    Ui::ventilate_reportchat *ui;
};

#endif // VENTILATE_REPORTCHAT_H
