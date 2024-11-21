#include "connexion.h"

connexion::connexion()
{

}

bool connexion::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source25");
    db.setUserName("youssef");//inserer nom de l'utilisateur
    db.setPassword("esprit2024");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;

    return  test;
}
