#include "connectionhandler.h"
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include "server.h"

/*!
 * \brief Create a new ConnectionHandler.
 * \param ID Identification number of the connecting socket.
 * \param parent The calling TcpServer.
 */
ConnectionHandler::ConnectionHandler(qintptr ID, QObject *parent)
    : QThread(parent), socketDescriptor(ID)
{
}

/*!
 * \brief   Cleans up allocated resources.
 * \details Destructor called at the end of a ConnectionHandler's life cycle.
 *          Clean up all allocated resources so we don't leak memory.
 */
ConnectionHandler::~ConnectionHandler()
{
}


/*!
 * \brief Called when a client disconnects from the Server.
 */
void ConnectionHandler::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    Server *server = static_cast<Server*>(this->parent());
    server->disconnectClient(socketDescriptor);
    socket->deleteLater();
    exit(0);
}


/*!
 * \brief Connect to a client.
 */
void ConnectionHandler::run()
{
    qDebug() << "Opened a new ConnectionHandler";
    socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        emit error(socket->error());
        return;
    }
    Server *server = static_cast<Server*>(this->parent());
    server->connectClient(socketDescriptor, socket->peerAddress());
    qDebug() << "peer address: " << socket->peerAddress();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    qDebug() << "Connected to " << socketDescriptor;

    exec();
}

void ConnectionHandler::readyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_0);
    QString data;
    in >> data;
    qDebug() << data;
}



/**
 * @brief Sends a message to the client.
 * @param data A preformatted message ready to be written directly to the client.
 */
void ConnectionHandler::sendToClient(QByteArray data) const
{
    socket->write(data);
}
