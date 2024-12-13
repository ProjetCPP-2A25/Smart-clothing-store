#include "client.h"
#include <QDebug>
#include "connection.h"
#include "mainwindow.h"
  Client::Client ()
  {
   id =0;
    nom="";
    prenom="";
     email="";
    telephone=0;
    adresse="";
    prix = 0;
    totalAchats = 0;


}
// Constructor parametre
Client::Client(int id, QString nom, QString prenom, QString email, int telephone, QString adresse,int  prix,int totalAchats )

{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->telephone=telephone;
    this->adresse=adresse;
    this->prix=prix;
    this->totalAchats=totalAchats;

}

 int Client:: getId(){return id ;}
  QString Client::getNom(){return nom ;}
  QString Client::getPrenom(){return prenom ;}
  QString Client::getEmail(){return email ;}
  int Client::getTelephone(){return telephone ;}
  QString Client::getAdresse(){return adresse ;}
  int Client::getprix() { return prix; }
  int Client::gettotalAchats() { return totalAchats; }



  void Client::setId(int id) { this->id = id; }
  void Client:: setNom(QString nom) { this->nom = nom; }
  void Client:: setPrenom( QString prenom) { this->prenom = prenom; }
  void Client::setEmail( QString email) { this->email = email; }
  void Client::setTelephone( int telephone) { this->telephone = telephone; }
  void Client::setAdresse( QString adresse) { this->adresse = adresse; }
  void Client::setprix(int prix) { this->prix = prix; }
  void Client::settotalAchats(int totalAchats) { this->totalAchats = totalAchats; }

// Add a new client to the database
bool Client::ajouter() {
    // Création d'un objet requête SQL
    QSqlQuery query;

    // Conversion de l'identifiant (entier) en chaîne de caractères
    QString res = QString::number(id );

    // Préparation de la requête SQL d'insertion
    // Les valeurs seront liées plus tard pour éviter les injections SQL
    query.prepare("INSERT INTO CLIENTS (id, nom, prenom, email, telephone, adresse, prix, totalachats) "
                  "VALUES (:id, :nom, :prenom, :email, :telephone, :adresse, :prix , :totalAchats)");

    // Liaison des valeurs aux paramètres de la requête
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":adresse", adresse);
    query.bindValue(":prix", prix);
    query.bindValue(":totalAchats", totalAchats);
    // Exécution de la requête et retour du résultat
    return query.exec(); // Renvoie true si l'insertion a réussi, false sinon
}


QSqlQueryModel* Client::afficher() {
    // Create a new query model
    QSqlQueryModel* model = new QSqlQueryModel();

    // Set the SQL query to select all columns from the "client" table
    model->setQuery("SELECT * FROM CLIENTS");

    // Set the headers for each column in the model
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("prix"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("totalAchats"));

    // Return the created model
    return model;
}



bool Client::modifier(int id) {
    QSqlQuery query;

    // Check if the client exists
    query.prepare("SELECT nom, prenom, email, telephone, adresse,  prix,totalAchats FROM CLIENTS WHERE id=:id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to retrieve existing client:" << query.lastError().text();
        return false;
    }

    if (!query.next()) {
        // Client with the specified ID doesn't exist
        qDebug() << "Client with ID" << id << "does not exist.";
        return false;
    }

    // Retrieve existing values
    QString currentNom = query.value(0).toString();
    QString currentPrenom = query.value(1).toString();
    QString currentEmail = query.value(2).toString();
    int currentTelephone = query.value(3).toInt();
    QString currentAdresse = query.value(4).toString();
    int currentprix = query.value(5).toInt();
    int currenttotalAchats = query.value(6).toInt();


    // Check if new values are the same as existing values
    if (nom == currentNom && prenom == currentPrenom && email == currentEmail &&
        telephone == currentTelephone && adresse == currentAdresse && prix == prix && totalAchats == totalAchats) {
        qDebug() << "No changes detected for client with ID" << id;
        return false;
    }

    // Proceed to update the client if changes were made
    query.prepare("UPDATE CLIENTS SET nom=:nom, prenom=:prenom, email=:email, telephone=:telephone, adresse=:adresse , prix=:prix WHERE id=:id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":adresse", adresse);
    query.bindValue(":prix", prix);
    query.bindValue(":totalAchats", totalAchats);

    if (!query.exec()) {
        qDebug() << "Failed to modify client:" << query.lastError().text();
        return false;
    }

    qDebug() << "Client with ID" << id << "successfully modified.";
    return true;
}



bool Client::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM clients WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        return false; // Query execution failed
    }

    // Check if any rows were affected by the delete operation
    return query.numRowsAffected() > 0;
}


