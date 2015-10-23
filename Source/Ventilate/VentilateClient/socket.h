#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "mainwindow.h"
#include "message.h"

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QString host, qint16 port, MainWindow& mw, QObject *parent = 0);
    virtual ~Socket();

    void propogateMessage(QString data);
    // Temporary function for testing
    void send(QString data);

public slots:
    void listen();

private:
    QMainWindow& mw;
    QTcpSocket *socket;
};

#endif // SOCKET_H
