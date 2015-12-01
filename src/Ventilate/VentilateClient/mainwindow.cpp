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

/*!
 * \brief Calls MainWindow::send
 */
void MainWindow::on_inputText_returnPressed()
{
    send();
}

/*!
 * \brief Calls MainWindow::send
 */
void MainWindow::on_sendButton_pressed()
{
    send();
}

/*!
 * \brief Send a message in the current ChatRoom
 */
void MainWindow::send()
{
    QString text = ui->inputText->text();
    ui->inputText->clear();
}
