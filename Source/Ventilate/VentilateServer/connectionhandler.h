#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QDebug>
#include <QHash>
#include <QTcpSocket>
#include <QThread>

class ConnectionHandler : public QThread
{
    Q_OBJECT
public:
    explicit ConnectionHandler(qintptr ID, QObject *parent);
    virtual ~ConnectionHandler();

    void run();
    void sendPeerList();

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;

    QString serializePeerList(QHash<qintprt, QHostAddress> peerList);
};

#endif // CONNECTIONHANDLER_H
