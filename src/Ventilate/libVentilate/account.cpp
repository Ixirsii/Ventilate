/*! \file
 * \brief Account class defininitions.
 * \author Ryan Porterfield
 * \since 2015-10-30
 * \copyright BSD 3 Clause
 */

#include "account.h"
#include <QByteArray>
#include <QCryptographicHash>
#include <QDataStream>
#include <QDateTime>
#include <QIODevice>
#include <QObject>
#include <QString>
#include "database/accountdatabase.h"
#include "server/commandparser.h"


Account::Account()
{
}


/*!
 * \brief Copy constructor
 * \param copy Account being copied.
 */
Account::Account(const Account& copy)
    : QObject(copy.parent()), uuid(copy.uuid), creationDate(copy.creationDate),
      emailAddress(copy.emailAddress), passwordHash(copy.passwordHash),
      username(copy.username)
{
}


/*!
 * \brief Move constructor.
 * \param move Account object being moved.
 */
Account::Account(Account &&move)
    : QObject(std::move(move.parent())), uuid(move.uuid),
      creationDate(move.creationDate),
      emailAddress(std::move(move.emailAddress)),
      passwordHash(std::move(move.passwordHash)),
      username(std::move(move.username))
{
}

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
 *
 * This constructor is useful for creating a brand new Account object
 * associated with a brand new user account. The creation date is calculated at
 * the time this constructor is called.
 *
 * \param username The account username. This needs to be unique.
 * \param passwordHash The salted and hashed account password.
 * \param emailAddress User's email address, used for account verification and
 * password resets.
 * \param parent Parent QObject passed to this classes parent, QObject for Qt
 * internal functions.
 */
Account::Account(QString& username, QByteArray& passwordHash,
                 QString& emailAddress, QObject *parent)
    : QObject(parent), uuid(QUuid::createUuid()),
      creationDate(QDateTime::currentDateTime()), emailAddress(emailAddress),
      passwordHash(passwordHash), username(username)
{
}


/*!
 * \brief Create a new user account.
 *
 * This constructor is useful for creating a brand new Account object
 * associated with a brand new user account. The password is hashed from its
 * QString form, and the creation date is calculated at the time this
 * constructor is called.
 *
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
    passwordHash = hashPassword(password, username);
}

/*!
 * \brief Create a complete Account specifying all values.
 *
 * This constructor is useful for creating an Account object that was read from
 * the database. All internal variables are set in the constructor as opposed
 * to other constructors which calculate certain variables such as
 * Account::passwordHash and Account::creationDate themselves.
 *
 * \param uuid The unique ID for the user account.
 * \param username The account username. This needs to be unique.
 * \param creationDate
 * \param password The already salted and hashed account password.
 * \param emailAddress User's email address, used for account verification and
 * password resets.
 * \param parent Parent QObject passed to this classes parent, QObject for Qt
 * internal functions.
 */
Account::Account(QUuid &uuid, QString &username, QDateTime &creationDate,
                 QByteArray &password, QString &emailAddress, QObject *parent)
    : QObject(parent), uuid(uuid),
      creationDate(creationDate), emailAddress(emailAddress),
      passwordHash(password), username(username)
{
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
    AccountDatabase db;
    Account acc = db.find(username);
    return passwordHash == acc.passwordHash;
}


Account Account::getAccount(Socket& socket, QString& username)
{
    QString cmd = CommandParser::ACCOUNT + " " + CommandParser::GET + " ";
    cmd += username;
    socket.send(cmd);
    socket.waitForResponse();
    Account acc = socket.get<Account>();
    return std::move(acc);
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

const QByteArray& Account::getPasswordHash() const
{
    return passwordHash;
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
QByteArray Account::hashPassword(QString& password, QString& username)
{
    QByteArray saltedArray;
    QDataStream out(&saltedArray, QIODevice::WriteOnly);
    out << username;
    out << password;
    return QCryptographicHash::hash(saltedArray, QCryptographicHash::Sha3_512);
}


/*!
 * \brief Copy operator.
 * \param copy
 * \return this.
 */
Account& Account::operator=(const Account& copy)
{
    uuid = copy.uuid;
    creationDate = copy.creationDate;
    emailAddress = copy.emailAddress;
    passwordHash = copy.passwordHash;
    username = copy.username;
    return *this;
}


/*!
 * \brief Move operator.
 * \param move
 * \return this.
 */
Account& Account::operator=(Account&& move)
{
    uuid = std::move(move.uuid);
    creationDate = std::move(move.creationDate);
    emailAddress = std::move(move.emailAddress);
    passwordHash = std::move(move.passwordHash);
    username = std::move(move.username);
    return *this;
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
    out << account.username;
    out << account.creationDate;
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
    in >> account.uuid;
    in >> account.username;
    in >> account.creationDate;
    return in;
}

/* ************************************************************************* *
 *                                    EOF                                    *
 * ************************************************************************* */
