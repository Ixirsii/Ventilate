#ifndef SOCKETLISTENER_H
#define SOCKETLISTENER_H

#include <QHostAddress>
#include <QObject>
#include <QString>
#include <QTcpSocket>

class SocketListener : public QObject
{
    Q_OBJECT
public:
    SocketListener(SocketListener &&move);
    explicit SocketListener(qintptr socketDescriptor, QObject *parent = 0);
    virtual ~SocketListener();

    const QHostAddress& getHostAddress() const;
    void send(const QString& data) const;

signals:
    void response(QString response);

public slots:
    void listen();

protected:
    QTcpSocket *&socket();
    const QTcpSocket *&socket() const;

private:
    QTcpSocket *socket_;
};

#endif // SOCKETLISTENER_H
