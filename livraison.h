#ifndef LIVRAISON_H
#define LIVRAISON_H

#include <QString>
#include <QDate>
#include <QList>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QVariant>

class Livraison
{
public:
    Livraison();
    Livraison(int id, QDate datePrevue, QDate dateEffectuee, QString adresse, QString nomLivreur, QString emailLivreur);

    // Getters and Setters
    int getIdLivraison() const;
    void setIdLivraison(int id);

    QDate getDatePrevue() const;
    void setDatePrevue(QDate date);

    QDate getDateEffectuee() const;
    void setDateEffectuee(QDate date);

    QString getAdresseLivraison() const;
    void setAdresseLivraison(QString adresse);

    QString getNomLivreur() const; // Getter for NOM_LIVREUR
    void setNomLivreur(QString nom); // Setter for NOM_LIVREUR

    QString getEmailLivreur() const; // Getter for EMAIL_LIVREUR
    void setEmailLivreur(QString email); // Setter for EMAIL_LIVREUR

    // CRUD Methods
    bool ajouter();
    bool modifier();
    bool supprimer(int ID_LIVRAISON);
    void afficherLivraisons(); // afficher
    void on_modifier_Clicked(); // Slot pour le bouton Modifier
    bool existe(int id);
    bool rechercher(int idLivraison);
    void exporterEnCSV();

private:
    int ID_LIVRAISON;
    QDate DATE_PREVUE;
    QDate DATE_EFFECTUEE;
    QString ADRESSE_LIVRAISON;
    QString NOM_LIVREUR; // Nouveau attribut
    QString EMAIL_LIVREUR; // Nouveau attribut
};

#endif // LIVRAISON_H
