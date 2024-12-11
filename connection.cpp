#include "connection.h"
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

void Connection::closeConnection(){db.close();}
