#ifndef SERVER_H
#define SERVER_H

#include <QHash>
#include <QString>
#include <QTcpServer>
#include "connectionhandler.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    const static QString CHANGE_PASSWORD_REQUEST;
    const static QString CREATE_ACCOUNT_REQUEST;
    const static QString LOGIN;
    const static QString PASSWORD;
    const static QString PEER;
    const static QString PEER_LIST;
    const static QString PEER_LIST_REQUEST;

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

    void changePassword();
    void createAccount();
    void login();
    void parsePeerCommand(const ConnectionHandler& handler, QString& command);
    void sendPeerList(const ConnectionHandler& handler);
    QString serializePeerList();
};

#endif // SERVER_H
