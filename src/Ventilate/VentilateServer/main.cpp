/*! \file
 * \brief Initialize and run the program.
 * \author Ryan Porterfield
 * \since 2015-09-18
 * \copyright BSD 3 Clause
 */

#include <QCoreApplication>
#include "server/server.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    server.startServer();

    return a.exec();
}
