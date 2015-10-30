/* Copyright (C) 2015 Ryan Porterfield
 *
 * This file defines all networking commands.
 *
 * $QT_BEGIN_LICENSE:BSD$
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of The Qt Company Ltd nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 *
 * $QT_END_LICENSE$
 */

/*! \file
 * \brief Account class defininitions.
 * \author Ryan Porterfield
 * \copyright BSD 3 Clause
 * \since 2015-10-30
 */

#include "account.h"
#include <QByteArray>
#include <QCryptographicHash>
#include <QDataStream>
#include <QDateTime>
#include <QIODevice>
#include <QObject>
#include <QString>


/*!
 * \brief Create a user account from a serialized Account.
 *
 * Not all Account information gets serialized. This is to prevent malicious
 * attackers snooping on the network from gaining sensitive user information.
 * An Account created from the information that was serialized will be
 * incomplete, but has all the necessary information to authenticate the
 * account.
 *
 * \param uuid The unique ID for the user account.
 * \param username The username for the user account.
 * \param creationDate The date and time that the user account was created.
 * \param parent Parent QObject passed to this classes parent, QObject for Qt
 * internal functions.
 */
Account::Account(QUuid& uuid, QString& username, QDateTime& creationDate,
                 QObject *parent)
    : QObject(parent), uuid(uuid), creationDate(creationDate),
      username(username)
{

}


/*!
 * \brief Create a new user account.
 * \param username The account username. This needs to be unique.
 * \param password The account password. This will get salted and hashed,
 * plain text passwords are not stored.
 * \param emailAddress User's email address, used for account verification and
 * password resets.
 * \param parent Parent QObject passed to this classes parent, QObject for Qt
 * internal functions.
 */
Account::Account(QString& username, QString& password, QString& emailAddress,
                 QObject *parent)
    : QObject(parent), uuid(QUuid::createUuid()),
      creationDate(QDateTime::currentDateTime()),
      emailAddress(emailAddress), username(username)
{
    passwordHash = hashPassword(password);
}


/*!
 * \brief Create a new user account.
 * \param username The account username. This needs to be unique.
 * \param password The account password. This will get salted and hashed,
 * plain text passwords are not stored.
 * \param emailAddress User's email address, used for account verification and
 * password resets.
 * \param phoneNumber User's phone number, used for 2 factor authentication.
 * \param serviceProvider  User's phone service provider, used for 2 factor
 * authentication.
 * \param parent Parent QObject passed to this classes parent, QObject for Qt
 * internal functions.
 */
Account::Account(QString& username, QString& password, QString& emailAddress,
                 QString& phoneNumber, ServiceProvider serviceProvider,
                 QObject *parent)
    : QObject(parent), uuid(QUuid::createUuid()),
      creationDate(QDateTime::currentDateTime()),
      emailAddress(emailAddress), username(username),
      phoneNumber(phoneNumber), serviceProvider(serviceProvider)
{
    passwordHash = hashPassword(password);
}


/*!
 * \brief Salt and hash a password so we can store it.
 *
 * Storing plain text or passwords encrypted with a common encryption key is
 * a poor security practice. Anyone who recovers a plain text password file has
 * access to all user passwords, and if someone recovers both the encrypted
 * table and the encryption key they also have access to all user passwords.
 * By storing salted hashes even if an attacker gets the table of passwords
 * there's no way to find out any individual user's password.
 *
 * \param password String password that is being salted and hashed.
 * \return A cryptographic hash of the user's password.
 */
QByteArray Account::hashPassword(QString& password) const
{
    QByteArray saltedArray;
    QDataStream out(&saltedArray, QIODevice::WriteOnly);
    out << creationDate;
    out << password;
    return QCryptographicHash::hash(saltedArray, QCryptographicHash::Sha3_512);
}


/*!
 * \brief Check that a user's username and password are valid.
 * \param username A user's account username.
 * \param passwordHash The cryptographic salted hash of the user's password.
 * \return true if the username and password are a valid combination, otherwise
 * false.
 */
bool Account::authenticateUser(QString& username, QByteArray passwordHash)
{
    return false;
}


/*!
 * \brief Get the unique ID for the user account.
 * \return  unique ID for the user account.
 */
const QUuid& Account::getUUID() const
{
    return uuid;
}


/*!
 * \brief Get the date and time the user account was created.
 * \return the date and time the user account was created.
 */
const QDateTime& Account::getCreationDate() const
{
    return creationDate;
}


/*!
 * \brief Get the email address used to verify the user account.
 * \return the email address used to verify the user account.
 */
const QString& Account::getEmailAddress() const
{
    return emailAddress;
}


/*!
 * \brief Get the username for the user account.
 * \return the username for the user account.
 */
const QString& Account::getUsername() const
{
    return username;
}


/*!
 * \brief Serialize the Account to a QDataStream.
 * \param out QDataStream the Account is being serialized to.
 * \param account the Account being serialized.
 * \return a modified version of out with the account in it.
 */
QDataStream& operator<<(QDataStream& out, const Account& account)
{
    out << account.uuid;
    out << account.creationDate;
    out << account.username;
    return out;
}


/*!
 * \brief Get an account that was serialized.
 * \param in
 * \param account
 * \return
 */
QDataStream& operator>>(QDataStream& in, Account& account)
{
    return in;
}

// OPTIONAL
/*!
 * \brief Get the phone number used for 2 factor authentication.
 * \return the phone number used for 2 factor authentication.
 */
const QString& Account::getPhoneNumber() const
{
    return phoneNumber;
}


/*!
 * \brief Get the phone service provider used for 2 factor authentication.
 * \return the phone service provider used for 2 factor authentication.
 */
const ServiceProvider Account::getServiceProvider() const
{
    return serviceProvider;
}

/* ************************************************************************* *
 *                                    EOF                                    *
 * ************************************************************************* */
