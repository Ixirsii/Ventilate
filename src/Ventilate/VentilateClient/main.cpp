/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-09-18
 * \copyright BSD 3 Clause
 */

#include "mainwindow.h"
#include <QApplication>
#include "server/server.h"
#include "socket.h"

/*!
 * \brief Start Ventilate
 * \details Initializes and starts the program. Makes the main window visible,
 *          connects to the central server, and starts listening for peer
 *          connections.
 * \param argc The number of command line arguments passed.
 * \param argv The command line arguments.
 * \return 0 if the program terminated successfully, otherwise an error code.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Connect to the central server
    //Socket s("127.0.0.1", 37377, w);
    // Test for now, gets the peer list
    //s.send("PEER LIST REQUEST");

    return a.exec();
}
