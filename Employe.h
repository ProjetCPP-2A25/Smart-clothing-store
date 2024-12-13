#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QDate>

class Employe
{
public:
    // Constructors
    Employe();
    Employe(int, QString, QString, QString, QString, int, QString,QString,QDate ,QDate ,int);
    static Employe GetByCIN(int CIN); // Declaration of the method

    // Getters
    int getCIN();
    QString getNOM_E();
    QString getPRENOM_E();
    QString getPOST();
    QString getEMAIL();
    int getTELEPHONE();
    QString getADRESSE();
    QString getLEAVE_TYPE();
    QDate getFIRST_DAY_OF_LEAVE();
    QDate getLAST_DAY_OF_LEAVE();
    int getNBDAYS();

    // Setters
    void setCIN(int);
    void setNOM_E(QString);
    void setPRENOM_E(QString);
    void setPOST(QString);
    void setEMAIL(QString);
    void setTELEPHONE(int);
    void setADRESSE(QString);
    void setLEAVE_TYPE(QString LEAVE_TYPE);
    void setFIRST_DAY_OF_LEAVE(QDate date);
    void setLAST_DAY_OF_LEAVE(QDate date);
    void setNBDAYS(int nbdays);

    // Functions
    bool ajouter();
    bool isValidEmail(const QString &email);

    QSqlQueryModel* afficherEMP();
    QSqlQueryModel* afficherCONG();
    //QSqlQueryModel* afficherfiltre();
    bool supprimer(int);
    bool cinexiste(int CIN);

    bool Modifier();
    bool supprimerCONG(int CIN);

    void stat_bateau();

    QSqlQueryModel*afficherCon();
    void enregistrerHistorique(const QString& operation);

    void enregistrerHistoriqueCong(const QString& operation);

private:
    int CIN;
    QString NOM_E, PRENOM_E, POST, EMAIL;
    int TELEPHONE;
    QString ADRESSE;
    QString LEAVE_TYPE;
    QDate FIRST_DAY_OF_LEAVE;
    QDate LAST_DAY_OF_LEAVE;
     int NBDAYS;
};

#endif // EMPLOYE_H
