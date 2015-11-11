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


QByteArray hashPassword(QString& password, QString& username);


class LIBVENTILATESHARED_EXPORT Account : public QObject
{
    Q_OBJECT
public:
    Account(Account&& move);

    explicit Account(QUuid& uuid, QString& username, QDateTime& creationDate,
                     QObject *parent = 0);

    explicit Account(QString& username, QString& password,
                     QString& emailAddress, QObject *parent = 0);

    explicit Account(QUuid& uuid, QString& username, QDateTime& creationDate,
                     QByteArray& password, QString& emailAddress,
                     QObject *parent = 0);

    static bool authenticateUser(QString& username, QByteArray passwordHash);
    const QUuid& getUUID() const;
    const QDateTime& getCreationDate() const;
    const QString& getEmailAddress() const;
    const QByteArray& getPasswordHash() const;
    const QString& getUsername() const;

    friend QDataStream& operator<<(QDataStream& out, const Account& account);
    friend QDataStream& operator>>(QDataStream& in, Account& account);

private:
    const QUuid uuid;
    const QDateTime creationDate;
    QString emailAddress;
    QByteArray passwordHash;
    QString username;
};

#endif // ACCOUNT_H

/* ************************************************************************* *
 *                                    EOF                                    *
 * ************************************************************************* */
