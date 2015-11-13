/*! \file
 * \brief Declare data type for handling threaded network connections.
 * \author Ryan Porterfield
 * \since 2015-09-11
 * \copyright BSD 3 Clause
 */

#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QHostAddress>
#include <QString>
#include <QTcpSocket>
#include <QThread>
#include "libventilate_global.h"

class LIBVENTILATESHARED_EXPORT ConnectionHandler : public QThread
{
    Q_OBJECT
public:
    explicit ConnectionHandler(qintptr ID, QObject *parent = 0);

    const QHostAddress& getHostAddress() const;
    void run();
    void write(QString data) const;

    friend bool operator==(const ConnectionHandler& ch0,
                           const ConnectionHandler& ch1);
    friend bool operator!=(const ConnectionHandler& ch0,
                           const ConnectionHandler& ch1);

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
