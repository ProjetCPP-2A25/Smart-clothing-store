#ifndef STOCK_H
#define STOCK_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QSqlError>
#include <QDebug>


class Stock {


    int idProduit;
    QString nomProduit;
    int quantite;
    double prix;
    QString marque;
    int idF;
    int idL;
    int stockFaible;

public:
    // Constructors
    Stock();
    Stock(int idProduit, QString nomProduit, int quantite, double prix, QString marque,int,int);
    int getQuantite(int idProduit);


    // Getters
    int getIdProduit();
    QString getNomProduit();
    int getQuantite();
    double getPrix();
    QString getMarque();


    // Setters
    void setIdProduit(int);
    void setNomProduit(QString);
    void setQuantite(int);
    void setPrix(double);
    void setMarque(QString);

    // CRUD functionalities
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int id);
    QSqlQueryModel* rechercherProduit(QString chaine);
    QSqlQueryModel* trierStock(const QString& critere, bool croissant);
    void enregistrerHistorique(const QString& operation);
    QString mostProfitableBrand(double &maxProfit);



};

#endif // STOCK_H

