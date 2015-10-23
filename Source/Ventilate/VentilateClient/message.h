#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDateTime>
#include <QObject>
#include <QString>
#include <QUuid>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QDateTime timestamp, QString username, QString message,
                     QObject *parent = 0);
    explicit Message(QUuid messageID, QDateTime timestamp, QString username,
                     QString message, QObject *parent = 0);

    const QString getMessage() const;
    const QDateTime getTimeStamp() const;
    const QString getUsername() const;

    QDataStream& operator<<(const Message& msg);
    QDataStream& operator>>(Message& msg);

private:
    const QUuid messageID;
    const QDateTime timestamp;
    const QString username;
    const QString message;
};

#endif // MESSAGE_H
