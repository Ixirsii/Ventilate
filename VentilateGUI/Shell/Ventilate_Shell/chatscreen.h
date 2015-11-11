#ifndef CHATSCREEN_H
#define CHATSCREEN_H

#include <QWidget>

namespace Ui {
class chatscreen;
}

class chatscreen : public QWidget
{
    Q_OBJECT

public:
    explicit chatscreen(QWidget *parent = 0);
    ~chatscreen();

private slots:
    void on_btnSend_clicked();

    void on_btnClear_clicked();

private:
    Ui::chatscreen *ui;
};

#endif // CHATSCREEN_H
