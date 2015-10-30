#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QHash>
#include <QTcpSocket>
#include <QThread>

class ConnectionHandler : public QThread
{
    Q_OBJECT
public:
    explicit ConnectionHandler(qintptr ID, QObject *parent = 0);

    void run();
    void sendToClient(QByteArray data) const;
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
