#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    virtual ~Server();

    void changePassword();
    void connectClient(qintptr socketDescriptor, QHostAddress clientAddress);
    void createAccount();
    void disconnectClient(qintptr socketDescriptor);
    void login();
    void startServer();

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    const static std::string CHANGE_PASSWORD_REQUEST;
    const static std::string CREATE_ACCOUNT_REQUEST;
    const static std::string LOGIN_REQUEST;

    QMap<qintptr, QHostAddress> connectedClients;
};

#endif // SERVER_H
