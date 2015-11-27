/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-10-30
 * \copyright 2015-11-10
 */

#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <QDataStream>
#include <QString>
#include <QTcpServer>
#include "connectionhandler.h"
#include "libventilate_global.h"

class LIBVENTILATESHARED_EXPORT Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    virtual ~Server();

    void startServer();

public slots:
    void disconnected(ConnectionHandler &handler);

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    std::vector<ConnectionHandler> clients;
};

#endif // SERVER_H
