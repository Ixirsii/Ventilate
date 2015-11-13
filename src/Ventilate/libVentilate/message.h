/*! \file
 * \brief Provides data types for modeling messages.
 * \author Ryan Porterfield
 * \since 2015-10-06
 * \copyright BSD 3 Clause
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDateTime>
#include <QObject>
#include <QString>
#include <QUuid>
#include "libventilate_global.h"

class LIBVENTILATESHARED_EXPORT Message : public QObject
{
    Q_OBJECT
public:
    Message(const Message& copy);
    Message(Message&& move);
    explicit Message(const QUuid& roomID, const QString& username,
                     const QString& message, QObject *parent = 0);
    explicit Message(const QUuid& uuid, const QUuid& roomID,
                     const QDateTime& timestamp, const QString& username,
                     const QString& message, QObject *parent = 0);

    QString getFormattedMessage() const;
    QString getSanitizedMessage() const;
    const QString& getMessage() const;
    const QUuid& getRoomID() const;
    const QDateTime& getTimeStamp() const;
    const QString& getUsername() const;
    const QUuid& getUUID() const;

    Message& operator=(const Message& msg);
    Message& operator=(Message&& msg);
    QDataStream& operator<<(const Message& msg);
    QDataStream& operator>>(Message& msg);

private:
    QUuid uuid;
    QUuid roomID;
    QDateTime timestamp;
    QString username;
    QString message;

    QString getHeader() const;
};

#endif // MESSAGE_H
