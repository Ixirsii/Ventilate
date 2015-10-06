#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QByteArray>
#include <QDateTime>
#include <QObject>
#include <QString>
#include <QUuid>

enum ServiceProvider {
    ATT,
    METRO_PCS,
    SPRINT,
    TMOBILE,
    VERIZON,
};

class Account : public QObject
{
    Q_OBJECT
public:
    explicit Account(QString accountName, QString password,
                     QString emailAddress, QObject *parent = 0);
    // OPTIONAL
    explicit Account(QString accountName, QString password,
                     QString emailAddress, QString phoneNumber,
                     ServiceProvider serviceProvider, QObject *parent = 0);
    virtual ~Account();

    bool authenticateUser(QString username, QByteArray passwordHash);
    QUuid getUUID();
    QDateTime getCreationDate();
    QString getEmailAddress();
    QString getUsername();

    QDataStream& operator<<(QDataStream& out, const Account& account);
    QDataStream& operator>>(QDataStream& in, Account& account);

    // OPTIONAL
    QString getPhoneNumber();
    ServiceProvider getServiceProvider();

private:
    const QUuid uuid;
    const QDateTime creationDate;
    QString emailAddress;
    QByteArray passwordHash;
    QString username;
    // OPTIONAL
    QString phoneNumber;
    ServiceProvider serviceProvider;
};

#endif // ACCOUNT_H
