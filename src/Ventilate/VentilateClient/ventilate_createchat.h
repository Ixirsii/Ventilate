#ifndef VENTILATE_CREATECHAT_H
#define VENTILATE_CREATECHAT_H

#include <QDialog>
#include <QMessageBox>
#include <QAbstractButton>
#include "chatroom.h"

namespace Ui {
class ventilate_createchat;
}

class ventilate_createchat : public QDialog
{
    Q_OBJECT

public:
    explicit ventilate_createchat(QWidget *parent = 0);
    ~ventilate_createchat();
    //ChatRoom getinfo(QUuid ownerID);
private slots:

    void reset();
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_cboPb_Pv_currentIndexChanged(int index);
    void on_btnMtR_Pv_clicked();

    void on_btnRtM_Pv_clicked();

    void on_btnAddModerator_Pv_clicked();

    void on_btnRemoveModerator_Pv_clicked();

    void on_btnAddUser_Pv_clicked();

    void on_btnRemoveUser_Pv_clicked();

    void on_btnAddModerator_Pb_clicked();

    void on_btnRemoveModerator_Pb_clicked();

    void on_lnedModerator_Pb_returnPressed();

    void on_lnedModerator_Pv_returnPressed();

private:
    Ui::ventilate_createchat *ui;
};

#endif // VENTILATE_CREATECHAT_H
