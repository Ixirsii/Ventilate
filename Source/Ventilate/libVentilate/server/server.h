/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-10-30
 * \copyright 2015-11-10
 */

#ifndef SERVER_H
#define SERVER_H

#include <QDataStream>
#include <QList>
#include <QString>
#include <QTcpServer>
#include "accountparser.h"
#include "connectionhandler.h"
#include "libventilate_global.h"
#include "passwordparser.h"
#include "peerparser.h"
#include "roomparser.h"

class LIBVENTILATESHARED_EXPORT Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    virtual ~Server();

    void disconnectClient(ConnectionHandler* handler);
    const QList<ConnectionHandler*>& getClientList() const;
    void onClientRequest(const ConnectionHandler& handler, QDataStream& stream);
    QString serializePeerList();
    void startServer();

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    QList<ConnectionHandler*> clientList;
    AccountParser accountParser;
    PasswordParser passwordParser;
    PeerParser peerParser;
    RoomParser roomParser;
};

#endif // SERVER_H
