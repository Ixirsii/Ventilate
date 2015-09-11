#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QDebug>
#include <QTcpSocket>
#include <QThread>

class ConnectionHandler : public QThread
{
    Q_OBJECT
public:
    explicit ConnectionHandler(qintptr ID, QObject *parent);
    virtual ~ConnectionHandler();

    void run();

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif // CONNECTIONHANDLER_H
