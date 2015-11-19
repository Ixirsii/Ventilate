/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-09-18
 * \copyright BSD 3 Clause
 */

#include <QApplication>
#include "ventilate.h"
#include "socket.h"
#include "server/server.h"

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
    Socket s("127.0.0.1", 37377);
    Ventilate v(s);
    v.show();

    // Connect to the central server
    // Test for now, gets the peer list
    //s.send("PEER LIST REQUEST");

    return a.exec();
}
