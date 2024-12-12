#include "connection.h"
#include <QDebug>
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source25");//inserer le nom de la source de données
db.setUserName("youssef");//inserer nom de l'utilisateur
db.setPassword("esprit2024");//inserer mot de passe de cet utilisateur

if (db.open()){
test=true;

qDebug() << "Connection successful!";
    } else {
        qDebug() << "Connection failed:" << db.lastError().text(); // Log the error message
    }



    return  test;
}

void Connection::closeConnection(){db.close();}
