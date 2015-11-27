/*! \file
 * \brief Declare data type for handling threaded network connections.
 * \author Ryan Porterfield
 * \since 2015-09-11
 * \copyright BSD 3 Clause
 */

#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <vector>
#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QHostAddress>
#include <QString>
#include <QTcpSocket>
#include "libventilate_global.h"

class LIBVENTILATESHARED_EXPORT ConnectionHandler : public QObject
{
    Q_OBJECT
public:
    ConnectionHandler(ConnectionHandler &&move);
    explicit ConnectionHandler(qintptr ID,
                               std::vector<ConnectionHandler>& clients,
                               QObject *parent = 0);
    virtual ~ConnectionHandler();

    const QHostAddress& getHostAddress() const;
    void run();
    QString serializePeerList();

    ConnectionHandler& operator=(ConnectionHandler &&move);
    friend bool operator==(const ConnectionHandler &ch0,
                           const ConnectionHandler &ch1);
    friend bool operator!=(const ConnectionHandler &ch0,
                           const ConnectionHandler &ch1);

signals:
    void disconnected(ConnectionHandler &handler);

public slots:
    void disconnected();
    void propogate(QString message);
    void readyRead();
    void taskResult(QString result);

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    std::vector<ConnectionHandler> &clients;

    void send(const QString& data) const;
};

#endif // CONNECTIONHANDLER_H
