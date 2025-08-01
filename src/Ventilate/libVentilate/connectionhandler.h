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
#include "socketlistener.h"

class LIBVENTILATESHARED_EXPORT ConnectionHandler : public SocketListener
{
    Q_OBJECT
public:
    ConnectionHandler(ConnectionHandler &&move);
    explicit ConnectionHandler(qintptr socketDescriptor,
                               std::vector<ConnectionHandler>& clients,
                               QObject *parent = 0);
    virtual ~ConnectionHandler();

    QString serializePeerList();

    ConnectionHandler& operator=(ConnectionHandler &&move);

signals:
    void disconnected(ConnectionHandler &handler);

public slots:
    void disconnected();
    void propogate(QString message);
    void taskResult(QString result);

private slots:
    void processResponse(QString cmd);

private:
    std::vector<ConnectionHandler> &clients;

};

#endif // CONNECTIONHANDLER_H
