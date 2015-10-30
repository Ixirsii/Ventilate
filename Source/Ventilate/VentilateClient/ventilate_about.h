#ifndef VENTILATE_ABOUT_H
#define VENTILATE_ABOUT_H

#include <QDialog>

namespace Ui {
class ventilate_about;
}

class ventilate_about : public QDialog
{
    Q_OBJECT

public:
    explicit ventilate_about(QWidget *parent = 0);
    ~ventilate_about();

private:
    Ui::ventilate_about *ui;
};

#endif // VENTILATE_ABOUT_H
