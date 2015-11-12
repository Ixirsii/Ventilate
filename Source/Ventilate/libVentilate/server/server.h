/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-10-30
 * \copyright 2015-11-10
 */

#ifndef SERVER_H
#define SERVER_H

#include <QHash>
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

    void connectClient(qintptr socketDescriptor, QHostAddress clientAddress);
    void disconnectClient(qintptr socketDescriptor);
    void onClientRequest(const ConnectionHandler& handler, QString& request);
    QString serializePeerList();
    void startServer();

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    QHash<qintptr, QHostAddress> connectedClients;
};

#endif // SERVER_H
