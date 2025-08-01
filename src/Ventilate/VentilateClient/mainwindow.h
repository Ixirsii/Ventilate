/*! \file
 * \brief Main window UI behavior.
 *
 * Declares the MainWindow class which defines behavior for the main chat
 * window.
 *
 * \author Ryan Porterfield
 * \since 2015-12-01
 * \copyright BSD 3 Clause
 */

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
    void on_inputText_returnPressed();
    void on_sendButton_pressed();

private:
    Ui::MainWindow *ui;

    void send();
};

#endif // MAINWINDOW_H
