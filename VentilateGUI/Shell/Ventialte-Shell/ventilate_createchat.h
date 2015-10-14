#ifndef VENTILATE_CREATECHAT_H
#define VENTILATE_CREATECHAT_H

#include <QDialog>

namespace Ui {
class ventilate_createchat;
}

class ventilate_createchat : public QDialog
{
    Q_OBJECT

public:
    explicit ventilate_createchat(QWidget *parent = 0);
    ~ventilate_createchat();

private slots:
    void on_cboPBorPV_currentIndexChanged(int index);

    void on_rbtnPBUattnYes_clicked();

    void on_rbtnPBUattnNo_clicked();

    void on_rbtnPBExitYes_clicked();

    void on_rbtnPBExitNo_clicked();

private:
    Ui::ventilate_createchat *ui;
};

#endif // VENTILATE_CREATECHAT_H
