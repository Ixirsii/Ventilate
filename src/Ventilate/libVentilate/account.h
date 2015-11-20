/*! \file
 * \brief Provides data types for modeling user classes.
 * \author Ryan Porterfield
 * \since 2015-10-30
 * \copyright 2015-11-10
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QByteArray>
#include <QDateTime>
#include <QObject>
#include <QString>
#include <QUuid>
#include "libventilate_global.h"
#include "socket.h"

class LIBVENTILATESHARED_EXPORT Account : public QObject
{
    Q_OBJECT
public:
    Account(const Account& copy);
    Account(Account&& move);

    explicit Account();
    explicit Account(QUuid& uuid, QString& username, QDateTime& creationDate,
                     QObject *parent = 0);

    explicit Account(QString& username, QByteArray& passwordHash,
                     QString& emailAddress, QObject *parent = 0);

    explicit Account(QString& username, QString& password,
                     QString& emailAddress, QObject *parent = 0);

    explicit Account(QUuid& uuid, QString& username, QDateTime& creationDate,
                     QByteArray& password, QString& emailAddress,
                     QObject *parent = 0);

    static bool authenticateUser(QString& username, QByteArray passwordHash);
    static Account fromString(QString& serialized);
    static QByteArray hashPassword(QString& password, QString& username);
    static void requestAccount(Socket& socket, QString& username);

    const QUuid& getUUID() const;
    const QDateTime& getCreationDate() const;
    const QString& getEmailAddress() const;
    const QByteArray& getPasswordHash() const;
    const QString& getUsername() const;
    QString toString() const;

    Account& operator=(const Account& copy);
    Account& operator=(Account&& move);
    friend QDataStream& operator>>(QDataStream& in, Account& account);
    friend QDataStream& operator<<(QDataStream& out, const Account& account);

private:
    QUuid uuid;
    QDateTime creationDate;
    QString emailAddress;
    QByteArray passwordHash;
    QString username;
};

#endif // ACCOUNT_H

/* ************************************************************************* *
 *                                    EOF                                    *
 * ************************************************************************* */
