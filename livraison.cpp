#include "livraison.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDate>
#include <QSqlError>
#include <QDebug>
#include <QString>

// Constructors
Livraison::Livraison()
{
    ID_LIVRAISON = 0;
    DATE_EFFECTUEE = QDate::currentDate();
    DATE_PREVUE = QDate::currentDate();
    ADRESSE_LIVRAISON = "";
    NOM_LIVREUR = "";
    EMAIL_LIVREUR = "";
}

Livraison::Livraison(int id, QDate datePrevue, QDate dateEffectuee, QString adresse, QString nomLivreur, QString emailLivreur)
    : ID_LIVRAISON(id), DATE_PREVUE(datePrevue), DATE_EFFECTUEE(dateEffectuee), ADRESSE_LIVRAISON(adresse),
    NOM_LIVREUR(nomLivreur), EMAIL_LIVREUR(emailLivreur) {}

// Getters and Setters
int Livraison::getIdLivraison() const { return ID_LIVRAISON; }
void Livraison::setIdLivraison(int id) { ID_LIVRAISON = id; }

QDate Livraison::getDatePrevue() const { return DATE_PREVUE; }
void Livraison::setDatePrevue(QDate date) { DATE_PREVUE = date; }

QDate Livraison::getDateEffectuee() const { return DATE_EFFECTUEE; }
void Livraison::setDateEffectuee(QDate date) { DATE_EFFECTUEE = date; }

QString Livraison::getAdresseLivraison() const { return ADRESSE_LIVRAISON; }
void Livraison::setAdresseLivraison(QString adresse) { ADRESSE_LIVRAISON = adresse; }

QString Livraison::getNomLivreur() const { return NOM_LIVREUR; }
void Livraison::setNomLivreur(QString nom) { NOM_LIVREUR = nom; }

QString Livraison::getEmailLivreur() const { return EMAIL_LIVREUR; }
void Livraison::setEmailLivreur(QString email) { EMAIL_LIVREUR = email; }

// CRUD Methods
bool Livraison::ajouter() {
    QSqlQuery query;
    QString res = QString::number(ID_LIVRAISON);

    query.prepare("INSERT INTO livraisons (ID_LIVRAISON, DATE_PREVUE, DATE_EFFECTUEE, ADRESSE_LIVRAISON, NOM_LIVREUR, EMAIL_LIVREUR) "
                  "VALUES (:ID_LIVRAISON, :DATE_PREVUE, :DATE_EFFECTUEE, :ADRESSE_LIVRAISON, :NOM_LIVREUR, :EMAIL_LIVREUR)");
    query.bindValue(":ID_LIVRAISON", res);

    query.bindValue(":DATE_PREVUE", DATE_PREVUE);
    query.bindValue(":DATE_EFFECTUEE", DATE_EFFECTUEE);
    query.bindValue(":ADRESSE_LIVRAISON", ADRESSE_LIVRAISON);
    query.bindValue(":NOM_LIVREUR", NOM_LIVREUR);
    query.bindValue(":EMAIL_LIVREUR", EMAIL_LIVREUR);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de la livraison : " << query.lastError().text();
        return false;
    }
    return true;
}

bool Livraison::supprimer(int ID_LIVRAISON) {
    QSqlQuery query;
    QString res = QString::number(ID_LIVRAISON);

    query.prepare("DELETE FROM livraisons WHERE ID_LIVRAISON = :ID_LIVRAISON");
    query.bindValue(":ID_LIVRAISON", res);
    return query.exec();
}

bool Livraison::existe(int id) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM livraisons WHERE ID_LIVRAISON = :ID_LIVRAISON");
    query.bindValue(":ID_LIVRAISON", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la vérification de l'ID :" << query.lastError().text();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();
    return (count > 0);
}

bool Livraison::rechercher(int idLivraison) {
    QSqlQuery query;
    query.prepare("SELECT ID_LIVRAISON FROM livraisons WHERE ID_LIVRAISON = :ID_LIVRAISON");
    query.bindValue(":ID_LIVRAISON", idLivraison);

    if (query.exec() && query.next()) {
        return true;
    } else {
        return false;
    }
}
