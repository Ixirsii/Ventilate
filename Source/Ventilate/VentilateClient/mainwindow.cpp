#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLogin_triggered()
{

}

void MainWindow::on_ptxtMessageBox_textChanged()
{

}

void MainWindow::on_actionLogout_triggered()
{

}

void MainWindow::on_actionChange_Password_triggered()
{

}

void MainWindow::on_actionExit_triggered()
{

}

void MainWindow::on_actionJoin_Chatroom_triggered()
{

}

void MainWindow::on_actionLeave_Chatroom_triggered()
{

}

void MainWindow::on_actionCreate_Chatroom_triggered()
{

}

void MainWindow::on_actionReport_Chatroom_triggered()
{

}

void MainWindow::on_actionHelp_triggered()
{

}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_btnClear_clicked()
{

}

void MainWindow::on_btnEnter_clicked()
{

}
