#ifndef CLIENT_H
#define CLIENT_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>



class Client
{
    int id;
        QString nom;
        QString prenom;
        QString email;
        int  telephone;
        QString adresse;
       int   prix;
     int   totalAchats;

    public:
        // Constructors
        Client() ;
       Client(int id, QString nom, QString prenom, QString email, int telephone, QString adresse, int prix,int  totalAchats);

        int getId()   ;
        QString getNom() ;
        QString getPrenom()  ;
        QString getEmail()  ;
        int getTelephone()  ;
        QString getAdresse() ;
        int getprix();
        int gettotalAchats();


        // Setters
        void setId(int ) ;
        void setNom( QString ) ;
        void setPrenom( QString ) ;
        void setEmail( QString ) ;
        void setTelephone( int ) ;
        void setAdresse(QString ) ;
        void setprix(int prix ) ;
        void settotalAchats(int totalAchats ) ;


        // CRUD functionalities
        bool ajouter();
        QSqlQueryModel * afficher();
        bool modifier(int id);
        bool supprimer(int id);

    };





#endif // CLIENT_H
