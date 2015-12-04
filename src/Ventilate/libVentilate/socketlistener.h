#ifndef SOCKETLISTENER_H
#define SOCKETLISTENER_H

#include <QObject>
#include <QTcpSocket>

class SocketListener : public QObject
{
    Q_OBJECT
public:
    explicit SocketListener(QTcpSocket *socket, QObject *parent = 0);

    void send(const QString& data) const;

signals:
    void response(QString response);

public slots:
    void listen();

private:
    QTcpSocket *socket;
};

#endif // SOCKETLISTENER_H
