#include "connectionhandler.h"
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
    Server server = this->parent();
    server.connectClient(socket->peerAddress());
    qDebug() << "peer address: " << socket->peerAddress();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    qDebug() << "Connected to " << socketDescriptor;

    exec();
}

void ConnectionHandler::readyRead()
{
    QByteArray Data = socket->readAll();
    qDebug() << socketDescriptor << " Data in: " << Data;
    socket->write(Data);
}

void ConnectionHandler::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    Server server = this->parent();
    server.disconnectClient(socket->peerAddress());
    socket->deleteLater();
    exit(0);
}
