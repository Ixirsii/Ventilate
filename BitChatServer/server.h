#ifndef SERVER_H
#define SERVER_H

#include <unordered_set>
#include <string>
#include <QTcpServer>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    virtual ~Server();

    void changePassword();
    void connectClient(std::string clientAddress);
    void createAccount();
    void disconnectClient(std::string clientAddress);
    void login();
    void startServer();

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    const static std::string CHANGE_PASSWORD_REQUEST = "changePassword";
    const static std::string CREATE_ACCOUNT_REQUEST = "createAccount";
    const static std::string LOGIN_REQUEST = "login";

    std::unordered_set<std::string> connectedClients;
};

#endif // SERVER_H
