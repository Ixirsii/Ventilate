#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLogin_triggered();

    void on_ptxtMessageBox_textChanged();

    void on_actionLogout_triggered();

    void on_actionChange_Password_triggered();

    void on_actionExit_triggered();

    void on_actionJoin_Chatroom_triggered();

    void on_actionLeave_Chatroom_triggered();

    void on_actionCreate_Chatroom_triggered();

    void on_actionReport_Chatroom_triggered();

    void on_actionHelp_triggered();

    void on_actionAbout_triggered();

    void on_btnClear_clicked();

    void on_btnEnter_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
