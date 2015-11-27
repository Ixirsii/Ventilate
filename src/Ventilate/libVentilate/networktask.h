#ifndef NETWORKTASK_H
#define NETWORKTASK_H

#include <QObject>
#include <QRunnable>
#include <QString>
#include <QStringList>
#include "connectionhandler.h"

class NetworkTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit NetworkTask(ConnectionHandler& handler,
                         QString fullcmd,
                         std::vector<ConnectionHandler>& clients,
                         QObject *parent = 0);

signals:
    void result(QString result);

public slots:

protected:
    void run() Q_DECL_OVERRIDE;

private:
    ConnectionHandler &handler;
    QString fullcmd;
    std::vector<ConnectionHandler> &clients;

    void parseRequest(QString& cmd, QString& subcmd, QStringList& tokens);
};

#endif // NETWORKTASK_H
