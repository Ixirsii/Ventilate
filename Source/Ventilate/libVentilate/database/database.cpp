/*! \file
 * \brief
 * \author Ryan Porterfield
 * \since 2015-11-11
 * \copyright BSD 3 Clause
 */

#include "database.h"
#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

const QString Database::ID_KEY = "id";
const QString Database::DATABASE_NAME = "ventilate";
const QString Database::DATE_KEY = "date";
const QString Database::EMAIL_KEY = "email";
const QString Database::MESSAGE_KEY = "message";
const QString Database::MODERATOR_KEY = "moderator";
const QString Database::NAME_KEY = "name";
const QString Database::OWNER_KEY = "owner";
const QString Database::PASSWORD_KEY = "password";
const quint32 Database::RETURN_RANGE = 50;
const QString Database::ROOM_KEY = "room";
const QString Database::USER_KEY = "user";
const QString Database::ACCOUNT_TABLE = "accounts";
const QString Database::MESSAGE_TABLE = "messages";
const QString Database::MOD_TABLE = "mods";
const QString Database::ROOM_TABLE = "rooms";
const QString Database::USER_TABLE = "users";
quint32 Database::counter = 0;

Database::Database()
    : connection_name(DATABASE_NAME + QString(counter++))
{
    db = QSqlDatabase::addDatabase("QSQLITE", connection_name);
    openDB(db);
}

Database::~Database()
{
    if (db.isOpen())
        db.close();
    QSqlDatabase::removeDatabase(DATABASE_NAME);
}

void Database::createAccountDB(QSqlDatabase& db)
{
    qDebug() << "Creating account database";
    db.transaction();
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS " + ACCOUNT_TABLE + "("
               + ID_KEY + " BLOB NOT NULL UNIQUE PRIMARY KEY, "
               + DATE_KEY + " DATETIME NOT NULL, "
               + EMAIL_KEY + " TEXT NOT NULL UNIQUE, "
               + PASSWORD_KEY + " BLOB NOT NULL, "
               + NAME_KEY + " TEXT NOT NULL UNIQUE);");
    runQuery(query);
    db.commit();
}

void Database::createMessageDB(QSqlDatabase& db)
{
    qDebug() << "Creating message database";
    db.transaction();
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS " + MESSAGE_TABLE + "("
                  + ID_KEY + " BLOB NOT NULL UNIQUE PRIMARY KEY, "
                  + ROOM_KEY + " BLOB NOT NULL, "
                  + DATE_KEY + " DATETIME NOT NULL, "
                  + MESSAGE_KEY + " TEXT NOT NULL, "
                  + NAME_KEY + " TEXT NOT NULL, "
                  + "FOREIGN KEY(" + ROOM_KEY + ") REFERENCES "
                  + ROOM_TABLE + "(" + ID_KEY + ") ON UPDATE CASCADE, "
                  + "FOREIGN KEY(" + NAME_KEY + ") REFERENCES "
                  + ACCOUNT_TABLE + "(" + NAME_KEY + ") ON UPDATE CASCADE);");
    runQuery(query);
    db.commit();
}

void Database::createModeratorDB(QSqlDatabase& db)
{
    qDebug() << "Creating moderator database";
    db.transaction();
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS " + MOD_TABLE + "("
        + NAME_KEY + " TEXT NOT NULL, "
        + ID_KEY + " BLOB NOT NULL, "
        + "PRIMARY KEY(" + NAME_KEY + ", " + ID_KEY + "), "
        + "FOREIGN KEY(" + NAME_KEY + ") REFERENCES "
        + ACCOUNT_TABLE + "(" + NAME_KEY + ") ON UPDATE CASCADE, "
        + "FOREIGN KEY(" + ID_KEY + ") REFERENCES "
        + ROOM_TABLE + "(" + ID_KEY + ") ON UPDATE CASCADE);"
    );
    runQuery(query);
    db.commit();
}

void Database::createRoomDB(QSqlDatabase& db)
{
    qDebug() << "Creating room database";
    db.transaction();
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS " + ROOM_TABLE + "("
        + ID_KEY + " BLOB NOT NULL UNIQUE PRIMARY KEY, "
        + OWNER_KEY + " TEXT NOT NULL, "
        + NAME_KEY + " TEXT NOT NULL, "
        + "FOREIGN KEY(" + OWNER_KEY + ") REFERENCES "
        + ACCOUNT_TABLE + "(" + NAME_KEY + ") ON UPDATE CASCADE);"
    );
    runQuery(query);
    db.commit();
}

void Database::createUserDB(QSqlDatabase& db)
{
    qDebug() << "Creating user database";
    db.transaction();
    QSqlQuery query(db);
    query.prepare("CREATE TABLE IF NOT EXISTS " + USER_TABLE + "("
        + NAME_KEY + " TEXT NOT NULL, "
        + ID_KEY + " BLOB NOT NULL, "
        + "PRIMARY KEY(" + NAME_KEY + ", " + ID_KEY + "), "
        + "FOREIGN KEY(" + NAME_KEY + ") REFERENCES "
        + ACCOUNT_TABLE + "(" + NAME_KEY + ") ON UPDATE CASCADE, "
        + "FOREIGN KEY(" + ID_KEY + ") REFERENCES "
        + ROOM_TABLE + "(" + ID_KEY + ") ON UPDATE CASCADE);"
    );
    runQuery(query);
    db.commit();
}

void Database::init()
{
    QSqlDatabase db(QSqlDatabase::addDatabase("QSQLITE", DATABASE_NAME));
    openDB(db);
    createAccountDB(db);
    createRoomDB(db);
    createMessageDB(db);
    createModeratorDB(db);
    createUserDB(db);
    db.close();
    QSqlDatabase::removeDatabase(DATABASE_NAME);
}

void Database::openDB(QSqlDatabase& db)
{
    QString path = QCoreApplication::applicationDirPath() + "/ventilate.sqlite";
    qDebug() << "Database path: " << path;
    db.setDatabaseName(path);
    if (!db.open()) {
        qDebug() << "DATABASE NOT OPENED: " << db.lastError().text();
        qDebug() << "";
    } else {
        qDebug() << "DATABASE OPENED";
        qDebug() << "";
    }
}

bool Database::runQuery(QSqlQuery& query)
{
    bool flag = query.exec();
    if (!flag)
        qDebug() << query.lastError().text();
    return flag;
}
