#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>

class fournisseur
{
private:
    int id;
    QString name;
    QString adresse;
    QString email;
    QString contact;
    int telephone;

public:
    // Constructors
    fournisseur();
    fournisseur(int id, QString name, QString adresse, QString email, QString contact, int telephone);

    // Getters
    int getId();
    QString getName();
    QString getAdresse();
    QString getEmail();
    QString getContact();
    int getTelephone();

    // Setters
    void setId(int id);
    void setName(QString name);
    void setAdresse(QString adresse);
    void setEmail(QString email);
    void setContact(QString contact);
    void setTelephone(int telephone);

    // CRUD Operations
    bool Ajouter();
    QSqlQueryModel* afficher();
    bool Supprimer(int id);
    bool modifier();

    /*Recherche*/
    QSqlQueryModel *afficher_name(QString ch);
    QSqlQueryModel *afficher_adresse(QString ch);
    QSqlQueryModel *afficher_email(QString ch);
    /*Tri*/
    QSqlQueryModel *afficher_choix(QString choix);
    /*Statistique*/
    int statistique1();
    int statistique2();
    /*PDF*/
    fournisseur* readfournisseur (int val);
    public:
    void enregistrerHistorique(const QString& operation);
};

#endif // FOURNISSEUR_H
