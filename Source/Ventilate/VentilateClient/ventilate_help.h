#ifndef VENTILATE_HELP_H
#define VENTILATE_HELP_H

#include <QDialog>

namespace Ui {
class ventilate_help;
}

class ventilate_help : public QDialog
{
    Q_OBJECT

public:
    explicit ventilate_help(QWidget *parent = 0);
    ~ventilate_help();

private:
    Ui::ventilate_help *ui;
};

#endif // VENTILATE_HELP_H
