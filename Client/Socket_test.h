#ifndef SOCKET_TEST_H
#define SOCKET_TEST_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class Socket_test : public QObject
{
    Q_OBJECT
public:
    explicit Socket_test(QObject *parent = 0);

    void Connect();
signals:

public slots:

private:
       QTcpSocket *socket;
};

#endif // SOCKET_TEST_H
