/*#include "connection.h"
#include <QDebug>
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données
db.setUserName("XE");//inserer nom de l'utilisateur
db.setPassword("0000");//inserer mot de passe de cet utilisateur

if (db.open()){
test=true;

qDebug() << "Connection successful!";
    } else {
        qDebug() << "Connection failed:" << db.lastError().text(); // Log the error message
    }



    return  test;
}

void Connection::closeConnection(){db.close();}*/
#include "connection.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>

Connection::Connection() {}

bool Connection::createconnect() {
    bool test = false;

    // Check if the connection already exists
    QString connectionName = "qt_sql_default_connection";
    if (QSqlDatabase::contains(connectionName)) {
        QSqlDatabase db = QSqlDatabase::database(connectionName);
        if (db.isOpen()) {
            qDebug() << "Using existing database connection.";
            return true; // Connection already exists and is open
        }
    }

    // Create a new connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", connectionName);
    db.setDatabaseName("Source_Projet2A"); // Set the database source name
    db.setUserName("XE");                 // Set the username
    db.setPassword("0000");               // Set the password

    if (db.open()) {
        test = true;
        qDebug() << "Connection successful!";
    } else {
        qDebug() << "Connection failed:" << db.lastError().text(); // Log the error message
    }

    return test;
}

void Connection::closeConnection() {
    QString connectionName = "qt_sql_default_connection";
    if (QSqlDatabase::contains(connectionName)) {
        QSqlDatabase db = QSqlDatabase::database(connectionName);
        db.close();
        QSqlDatabase::removeDatabase(connectionName); // Properly remove the connection
        qDebug() << "Connection closed.";
    } else {
        qDebug() << "No connection to close.";
    }
}

