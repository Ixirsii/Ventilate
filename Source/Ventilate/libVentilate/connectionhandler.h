#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QHash>
#include <QString>
#include <QTcpSocket>
#include <QThread>
#include "libventilate_global.h"

class LIBVENTILATESHARED_EXPORT ConnectionHandler : public QThread
{
    Q_OBJECT
public:
    explicit ConnectionHandler(qintptr ID, QObject *parent = 0);

    void run();
    void write(QString data);
signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;

    void sendToClient(QByteArray data) const;
};

#endif // CONNECTIONHANDLER_H
