#include "stock.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

Stock::Stock() {
    idProduit = 0;
    nomProduit = "";
    quantite = 0;
    prix = 0.0;
    marque = "";
    idF=0;
    idL=0;
}

Stock::Stock(int idProduit, QString nomProduit, int quantite, double prix, QString marque,int idF,int idL) {
    this->idProduit = idProduit;
    this->nomProduit = nomProduit;
    this->quantite = quantite;
    this->prix = prix;
    this->marque = marque;
    this->idF = idF;
    this->idL = idL;
}

int Stock::getIdProduit() { return idProduit; }
QString Stock::getNomProduit() { return nomProduit; }
int Stock::getQuantite() { return quantite; }
double Stock::getPrix() { return prix; }
QString Stock::getMarque() { return marque; }

void Stock::setIdProduit(int idProduit) { this->idProduit = idProduit; }
void Stock::setNomProduit(QString nomProduit) { this->nomProduit = nomProduit; }
void Stock::setQuantite(int quantite) { this->quantite = quantite; }
void Stock::setPrix(double prix) { this->prix = prix; }
void Stock::setMarque(QString marque) { this->marque = marque; }

bool Stock::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO STOCK (ID_PRODUIT,NOM_PRODUIT, QUANTITE_PRODUIT, PRIX_PRODUIT, MARQUE_PRODUIT, ID_FOURNISSEUR, ID_LIVRAISON) "
                  "VALUES (:id,:nom, :quantite, :prix, :marque, :idFournisseur, :idLivraison)");
    query.bindValue(":nom", nomProduit);
    query.bindValue(":quantite", quantite);
    query.bindValue(":id", idProduit);
    query.bindValue(":prix", prix);
    query.bindValue(":marque", marque);
    query.bindValue(":idFournisseur", idF);
    query.bindValue(":idLivraison", idL);
    if (query.exec()) {
        enregistrerHistorique("Ajouté");
        return true;
    }


    return query.exec();
}
QSqlQueryModel *Stock::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from Stock");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Quantite"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Prix"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Marque"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("Fournisseur"));
      model->setHeaderData(6,Qt::Horizontal,QObject::tr("Livraison"));
    return model;
}

bool Stock::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from STOCK where ID_PRODUIT=:id");
    query.bindValue(":id",res);
    if (query.exec()) {
        enregistrerHistorique("Supprimé");
        return true;
    }

    return query.exec();

}
bool Stock::modifier(int id){

  QSqlQuery query;
    QString res=QString::number(id);


    query.prepare("UPDATE Stock   SET NOM_PRODUIT=:nom, QUANTITE_PRODUIT=:qt , PRIX_PRODUIT=:prix, MARQUE_PRODUIT=:marque , ID_FOURNISSEUR=:idF, ID_LIVRAISON=:idL where ID_PRODUIT='"+res+"' ");


    query.bindValue(":nom", nomProduit);
    query.bindValue(":qt", quantite);
    query.bindValue(":prix", prix);
    query.bindValue(":marque", marque);
    query.bindValue(":idF", idF);
    query.bindValue(":idL", idL);
    if (query.exec()) {
        enregistrerHistorique("Modifié");
        return true;
    }




    return query.exec();
}


QString Stock::mostProfitableBrand(double &maxProfit) {
    QSqlQuery query;
    QString mostProfitable;

    // Query to calculate profit for each brand
    query.prepare("SELECT MARQUE_PRODUIT, SUM(QUANTITE_PRODUIT * PRIX_PRODUIT) AS PROFIT FROM STOCK GROUP BY MARQUE_PRODUIT ORDER BY PROFIT DESC");

    if (query.exec()) {
        if (query.next()) {
            mostProfitable = query.value(0).toString(); // Get the brand name
            maxProfit = query.value(1).toDouble();      // Get the highest profit
        }
    } else {
        qDebug() << "Error fetching most profitable brand:" << query.lastError().text();
    }

    return mostProfitable;
}

QSqlQueryModel* Stock::rechercherProduit(QString chaine)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Stock WHERE NOM_PRODUIT LIKE '%" + chaine + "%'");
    return model;
}

QSqlQueryModel* Stock::trierStock(const QString& critere, bool croissant) {
    QSqlQueryModel* model = new QSqlQueryModel();

    // Vérification de la valeur de 'croissant'
    qDebug() << "Valeur de 'croissant' reçue :" << croissant;

    // Déterminer l'ordre (ASC ou DESC)
    QString ordre = croissant ? "ASC" : "DESC";

    // Construire la requête SQL
    QString queryStr = QString("SELECT * FROM STOCK ORDER BY %1 %2").arg(critere, ordre);

    // Exécuter la requête
    model->setQuery(queryStr);

    // Vérifier les erreurs et afficher les détails de débogage
    qDebug() << "Requête exécutée:" << queryStr;
    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de l'exécution de la requête de tri:" << model->lastError().text();
    } else {
        qDebug() << "Requête exécutée avec succès.";
    }

    return model;
}

int Stock::getQuantite(int idProduit)
{
    QSqlQuery query;
    // Prepare the SQL statement
    query.prepare("SELECT QUANTITE_PRODUIT FROM STOCK WHERE ID_PRODUIT = :id");
    query.bindValue(":id", idProduit);

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return -1; // Return error code
    }

    // Check if a result is returned
    if (query.next()) {
        return query.value(0).toInt(); // Return the quantity
    } else {
        qDebug() << "Aucun résultat trouvé pour IDP:" << idProduit;
        return -1; // Return error code if no result found
    }
}
void Stock::enregistrerHistorique(const QString& operation) {
    QFile file("stock_historique.txt"); // Nom du fichier historique (stocké dans le répertoire courant)
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        out << timestamp << " - " << operation << " - ID: " << idProduit
            << ", Nom: " << nomProduit << ", Quantité: " << quantite
            << ", Prix: " << prix << ", Marque: " << marque << "\n";
        file.close();
    } else {
        qDebug() << "Impossible d'ouvrir le fichier historique pour écriture.";
    }
}
