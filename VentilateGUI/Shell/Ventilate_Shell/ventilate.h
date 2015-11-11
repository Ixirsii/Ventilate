#ifndef VENTILATE_H
#define VENTILATE_H

#include <QMainWindow>
#include<QUuid>
namespace Ui {
class Ventilate;
}

class Ventilate : public QMainWindow
{
    Q_OBJECT
private:
    QUuid UserID;
public:
    explicit Ventilate(QWidget *parent = 0);
    ~Ventilate();

private slots:
    void on_actionCreate_Chat_room_triggered();
    void on_actionLogin_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionLogout_triggered();

    void on_btnSend_clicked();

    void on_btnClear_clicked();

    void on_btnAddTab_clicked();

    void on_btnTabInfo_clicked();

private:
    Ui::Ventilate *ui;
};

#endif // VENTILATE_H
