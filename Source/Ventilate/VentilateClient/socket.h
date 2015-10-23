#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "message.h"

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QString host, qint16 port, QObject *parent = 0);

    void propogateMessage(QString data);
    // Temporary function for testing
    void send(QString data);

public slots:
    void listen();

private:
    QTcpSocket *socket;
};

#endif // SOCKET_H
