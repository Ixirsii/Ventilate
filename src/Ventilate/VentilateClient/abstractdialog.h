#ifndef ABSTRACTDIALOG_H
#define ABSTRACTDIALOG_H

#include <QDialog>
#include <QObject>

#include "socket.h"

class AbstractDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AbstractDialog(Socket& socket, QWidget *parent = 0);
    virtual ~AbstractDialog();

signals:

public slots:
    virtual void response(QString response) = 0;

protected:
    Socket& getSocket();

private:
    Socket& socket;
};

#endif // ABSTRACTDIALOG_H
