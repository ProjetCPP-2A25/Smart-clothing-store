#include <QApplication>
#include <QMessageBox>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include "livraison.h"
#include "mainwindow.h"
#include <QCoreApplication>
#include "arduino.h"

bool initializeDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet2A");
    db.setUserName("rabi3");
    db.setPassword("0000");

    if (!db.open()) {
        qDebug() << "Erreur lors de l'ouverture de la base de données:" << db.lastError().text();
        QMessageBox::critical(nullptr, QObject::tr("Erreur de connexion"),
                              QObject::tr("Échec de la connexion à la base de données.\n"
                                          "Erreur spécifique: ") + db.lastError().text(),
                              QMessageBox::Ok);
        return false;
    }
    qDebug() << "Connexion à la base de données réussie.";

    return true;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Initialize the database connection
    if (!initializeDatabase()) {
        return -1;  // Exit if the database connection fails
    }

    QMessageBox::information(nullptr, QObject::tr("Connexion réussie"),
                             QObject::tr("Connexion à la base de données réussie.\n"
                                         "Cliquez sur Annuler pour fermer."), QMessageBox::Cancel);

    MainWindow w;
    w.show();

    // Create a Livraison object with additional attributes
    Livraison livraison(1, QDate::currentDate().addDays(5), QDate(), "123 Rue de la Paix",
                        "John Doe", "john.doe@example.com");

    // Add the Livraison object to the database
    if (livraison.ajouter()) {
        qDebug() << "Livraison ajoutée avec succès.";
    } else {
        qDebug() << "Échec de l'ajout de la livraison.";
    }

    // Test delete functionality
    int livraisonIdToDelete = 1;  // Example id to delete
    if (livraison.supprimer(livraisonIdToDelete)) {
        qDebug() << "Livraison supprimée avec succès.";
    } else {
        qDebug() << "Échec de la suppression de la livraison.";
    }


     Arduino arduino;

    // Tenter de connecter l'Arduino
    int connectionStatus = arduino.connect_arduino();
    if (connectionStatus == 0) {
        qDebug() << "Connexion réussie!";

        // Envoyer des données à Arduino
        arduino.write_to_arduino("Hello Arduino");

        // Lire les données envoyées par l'Arduino
        QByteArray receivedData = arduino.read_from_arduino();
        qDebug() << "Données reçues : " << receivedData;

        // Fermer la connexion
        arduino.close_arduino();
    } else {
        qDebug() << "Erreur de connexion!";
    }
    return a.exec();
}


//////////////////////////arduino
///
///
///    // Créer une instance de la classe Arduino


