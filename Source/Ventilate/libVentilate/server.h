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
    void startServer();

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    QHash<qintptr, QHostAddress> connectedClients;

    void changePassword(const ConnectionHandler& handler, QString& command);
    void createAccount(const ConnectionHandler& handler, QString& command);
    void createRoom(const ConnectionHandler& handler, QString& command);
    void login(const ConnectionHandler& handler, QString& command);
    void parseAccountCommand(const ConnectionHandler& handler, QString& command);
    void parseRoomCommand(const ConnectionHandler& handler, QString& command);
    void parsePeerCommand(const ConnectionHandler& handler, QString& command);
    void sendPeerList(const ConnectionHandler& handler);
    QString serializePeerList();
};

#endif // SERVER_H
