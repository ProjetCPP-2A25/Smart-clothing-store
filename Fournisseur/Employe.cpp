#include "Employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QRegularExpression>
#include <QDate>
#include <QFile>

Employe::Employe()
{
    CIN = 0;
    NOM_E = " ";
    PRENOM_E = " ";
    POST = " ";
    EMAIL = " ";
    TELEPHONE = 0;
    ADRESSE = " ";
    LEAVE_TYPE = "None";
    FIRST_DAY_OF_LEAVE = QDate();
    LAST_DAY_OF_LEAVE = QDate();
    NBDAYS = 0;
}

Employe::Employe(int CIN, QString NOM_E, QString PRENOM_E, QString POST, QString EMAIL, int TELEPHONE, QString ADRESSE, QString LEAVE_TYPE,QDate FIRST_DAY_OF_LEAVE,
                 QDate LAST_DAY_OF_LEAVE,int NBDAYS)
{
    this->CIN = CIN;
    this->NOM_E = NOM_E;
    this->PRENOM_E = PRENOM_E;
    this->POST = POST;
    this->EMAIL = EMAIL;
    this->TELEPHONE = TELEPHONE;
    this->ADRESSE = ADRESSE;
    this->LEAVE_TYPE = LEAVE_TYPE;
    this->FIRST_DAY_OF_LEAVE = FIRST_DAY_OF_LEAVE;
    this->LAST_DAY_OF_LEAVE = LAST_DAY_OF_LEAVE;
    this->NBDAYS = NBDAYS;


}

int Employe::getCIN() { return CIN; }
QString Employe::getNOM_E() { return NOM_E; }
QString Employe::getPRENOM_E() { return PRENOM_E; }
QString Employe::getPOST() { return POST; }
QString Employe::getEMAIL() { return EMAIL; }
int Employe::getTELEPHONE() { return TELEPHONE; }
QString Employe::getADRESSE() { return ADRESSE; }
QString Employe::getLEAVE_TYPE() { return LEAVE_TYPE; }
QDate Employe::getFIRST_DAY_OF_LEAVE() { return FIRST_DAY_OF_LEAVE; }
QDate Employe::getLAST_DAY_OF_LEAVE() { return LAST_DAY_OF_LEAVE; }
int Employe::getNBDAYS() { return NBDAYS; }

// Setters
void Employe::setCIN(int CIN) { this->CIN = CIN; }
void Employe::setNOM_E(QString NOM_E) { this->NOM_E = NOM_E; }
void Employe::setPRENOM_E(QString PRENOM_E) { this->PRENOM_E = PRENOM_E; }
void Employe::setPOST(QString POST) { this->POST = POST; }
void Employe::setEMAIL(QString EMAIL) { this->EMAIL = EMAIL; }
void Employe::setTELEPHONE(int TELEPHONE) { this->TELEPHONE = TELEPHONE; }
void Employe::setADRESSE(QString ADRESSE) { this->ADRESSE = ADRESSE; }
void Employe::setLEAVE_TYPE(QString LEAVE_TYPE) { this->LEAVE_TYPE = LEAVE_TYPE; }
void Employe::setFIRST_DAY_OF_LEAVE(QDate date) { this->FIRST_DAY_OF_LEAVE = date; }
void Employe::setLAST_DAY_OF_LEAVE(QDate date) { this->LAST_DAY_OF_LEAVE = date; }
void Employe::setNBDAYS(int nbdays) { this->NBDAYS = nbdays; }



bool Employe::ajouter() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database not open!";
        if (!db.open()) {
            qDebug() << "Failed to open database: " << db.lastError().text();
            return false;
        }
    }

    // Check for existing CIN
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM EMPLOYEE WHERE CIN = :CIN");
    checkQuery.bindValue(":CIN", CIN);
    if (!checkQuery.exec()) {
        qDebug() << "Error checking CIN existence: " << checkQuery.lastError().text();
        return false;
    }

    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        qDebug() << "CIN already exists. Cannot insert.";
        return false; // Indicate failure
    }

    // Prepare the insert query
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYEE (CIN, NOM_E, PRENOM_E, POST, EMAIL, TELEPHONE, ADRESSE, LEAVE_TYPE, FIRST_DAY_OF_LEAVE, LAST_DAY_OF_LEAVE, NBDAYS) "
                  "VALUES (:CIN, :NOM_E, :PRENOM_E, :POST, :EMAIL, :TELEPHONE, :ADRESSE, :LEAVE_TYPE, :FIRST_DAY_OF_LEAVE, :LAST_DAY_OF_LEAVE, :NBDAYS)");

    // Log input values
    qDebug() << "Inserting values:";
    qDebug() << "CIN:" << CIN
             << "NOM_E:" << NOM_E
             << "PRENOM_E:" << PRENOM_E
             << "POST:" << POST
             << "EMAIL:" << EMAIL
             << "TELEPHONE:" << TELEPHONE
             << "ADRESSE:" << ADRESSE
             << "LEAVE_TYPE:" << LEAVE_TYPE
    << "FIRST_DAY_OF_LEAVE:" << FIRST_DAY_OF_LEAVE.toString("yyyy-MM-dd")  // Convert QDate to QString
                 << "LAST_DAY_OF_LEAVE:" << LAST_DAY_OF_LEAVE.toString("yyyy-MM-dd")
    << "NBDAYS:" << QString::number(NBDAYS);

    // Bind values
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM_E", NOM_E);
    query.bindValue(":PRENOM_E", PRENOM_E);
    query.bindValue(":POST", POST);
    query.bindValue(":EMAIL", EMAIL);
    if (!isValidEmail(EMAIL)) {
        qDebug() << "Invalid email address: " << EMAIL;
        return false;
    }
    query.bindValue(":TELEPHONE", TELEPHONE);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":LEAVE_TYPE", LEAVE_TYPE); // Bind the leave type
    query.bindValue(":FIRST_DAY_OF_LEAVE", FIRST_DAY_OF_LEAVE);
    query.bindValue(":LAST_DAY_OF_LEAVE", LAST_DAY_OF_LEAVE);
    query.bindValue(":NBDAYS", NBDAYS);

    /* Execute the query
    if (!query.exec()) {
        qDebug() << "SQL Error: " << query.lastError().text();
        return false;
    } else {
        qDebug() << "Record added successfully.";
    }

    return true; // Indicate success*/
    bool success = query.exec();
            if (success) {
                enregistrerHistorique("Ajout d'un employe");
                if (!LEAVE_TYPE.isEmpty() && !FIRST_DAY_OF_LEAVE.isNull() && !LAST_DAY_OF_LEAVE.isNull() && NBDAYS > 0) {
                        enregistrerHistoriqueCong("Added vacation for employee with CIN: " + QString::number(CIN) +
                                                  " Leave Type: " + LEAVE_TYPE +
                                                  " From: " + FIRST_DAY_OF_LEAVE.toString("yyyy-MM-dd") +
                                                  " To: " + LAST_DAY_OF_LEAVE.toString("yyyy-MM-dd") +
                                                  " Days: " + QString::number(NBDAYS));
                    }
            }
            return success;
}


bool Employe::isValidEmail(const QString &email) {
    QRegularExpression regex(R"((^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$))");
    return regex.match(email).hasMatch();
}


bool Employe::supprimer(int CIN)
{
    QSqlQuery query;
    query.prepare("DELETE from EMPLOYEE where CIN=:CIN");
    query.bindValue(0, CIN);
    bool success = query.exec();
            if (success) {
                // Enregistrer l'historique de la suppression
                enregistrerHistorique("Suppression d'un employe avec ID: " + QString::number(CIN));
            }
            return success;
}



bool Employe::supprimerCONG(int CIN) {
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEE SET LEAVE_TYPE = NULL, FIRST_DAY_OF_LEAVE = NULL, LAST_DAY_OF_LEAVE = NULL, NBDAYS = NULL WHERE CIN = :CIN");
    query.bindValue(":CIN", CIN);
    bool success = query.exec();
    if (success) {
        enregistrerHistoriqueCong("Deleted vacation leave for CIN " + QString::number(CIN));
    }
    return success;
}


QSqlQueryModel* Employe::afficherEMP()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT CIN, NOM_E, PRENOM_E, POST, EMAIL, TELEPHONE, ADRESSE FROM EMPLOYEE;");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_E"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_E"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("POST"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("ADRESSE"));

    return model;
}

QSqlQueryModel* Employe::afficherCONG()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT CIN, NOM_E, PRENOM_E, FIRST_DAY_OF_LEAVE,LAST_DAY_OF_LEAVE,LEAVE_TYPE,NBDAYS  FROM EMPLOYEE;");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_E"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_E"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("FIRST_DAY_OF_LEAVE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("LAST_DAY_OF_LEAVE"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("LEAVE_TYPE"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("NBDAYS"));

    return model;
}
bool Employe::cinexiste(int CIN)
{
    QSqlQuery query;
    query.prepare("SELECT CIN FROM EMPLOYEE WHERE CIN=:CIN");
    query.bindValue(":CIN",CIN);
    if(query.exec()&&query.next())
    {
        return true;
}
    else
    {
        return false;

    }
}
bool Employe::Modifier() {
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        /*qDebug() << "Database not open!";
        if (!db.open()) {
            qDebug() << "Failed to open database: " << db.lastError().text();
            return false;*/
        bool success = query.exec();
                if (success) {
                    // Enregistrer l'historique de la modification
                    enregistrerHistorique("Modification d'un employe avec ID: " + QString::number(CIN));

                return success;
                }
    }

    // Prepare the update query

    query.prepare("UPDATE EMPLOYEE SET NOM_E = :NOM_E, PRENOM_E = :PRENOM_E, POST = :POST, "
                  "EMAIL = :EMAIL, TELEPHONE = :TELEPHONE, ADRESSE = :ADRESSE, LEAVE_TYPE = :LEAVE_TYPE, "
                  "FIRST_DAY_OF_LEAVE = :FIRST_DAY_OF_LEAVE, LAST_DAY_OF_LEAVE = :LAST_DAY_OF_LEAVE, NBDAYS = :NBDAYS "
                  "WHERE CIN = :CIN");

    // Bind the values to the placeholders
    query.bindValue(":CIN", CIN);
    query.bindValue(":NOM_E", NOM_E);
    query.bindValue(":PRENOM_E", PRENOM_E);
    query.bindValue(":POST", POST);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":TELEPHONE", TELEPHONE);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":LEAVE_TYPE", LEAVE_TYPE);
    query.bindValue(":FIRST_DAY_OF_LEAVE", FIRST_DAY_OF_LEAVE);
    query.bindValue(":LAST_DAY_OF_LEAVE", LAST_DAY_OF_LEAVE);
    query.bindValue(":NBDAYS", NBDAYS);

    // Execute the query
    if (!query.exec()) {
        qDebug() << "SQL Error: " << query.lastError().text();
        return false;
    }

    qDebug() << "Employee record updated successfully.";
    return true;
}








Employe Employe::GetByCIN(int cin) {
    Employe emp;
    QSqlQuery query;

    query.prepare("SELECT * FROM employees WHERE CIN = :cin");
    query.bindValue(":cin", cin);

    if (query.exec() && query.next()) {
        // Assuming you have a constructor that allows setting all attributes
        emp = Employe(query.value("CIN").toInt(),
                       query.value("NOM_E").toString(),
                       query.value("PRENOM_E").toString(),
                       query.value("POST").toString(),
                       query.value("EMAIL").toString(),
                       query.value("TELEPHONE").toInt(),
                       query.value("ADRESSE").toString(),
                       query.value("LEAVE_TYPE").toString(),
                       query.value("FIRST_DAY_OF_LEAVE").toDate(),
                       query.value("LAST_DAY_OF_LEAVE").toDate(),
                       query.value("NBDAYS").toInt());
    }

    return emp;
}



#include <QtCharts/QPieSeries>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>


void Employe::stat_bateau() {
    QSqlQueryModel *model = new QSqlQueryModel();

    // Requête pour compter les types de leave
    model->setQuery("SELECT LEAVE_TYPE, COUNT(*) as count FROM EMPLOYEE GROUP BY LEAVE_TYPE");

    // Calculer le nombre total d'employés
    int totalCount = 0;
    for (int i = 0; i < model->rowCount(); i++) {
        totalCount += model->record(i).value("count").toInt();
    }

    // Création de la série pour le graphique
    QPieSeries *series = new QPieSeries();

    // Parcours des résultats pour construire la série
    for (int i = 0; i < model->rowCount(); i++) {
        QString leaveType = model->record(i).value("LEAVE_TYPE").toString();
        int count = model->record(i).value("count").toInt();

        // Calcul du pourcentage pour chaque type de leave
        double percentage = (totalCount > 0) ? (static_cast<double>(count) / totalCount) * 100 : 0;

        // Ajout du label et du pourcentage à la série
        series->append(leaveType + ": " + QString::number(percentage, 'f',0) + "%", count);
    }

    // Personnalisation des étiquettes et des couleurs
    for (int i = 0; i < series->slices().size(); i++) {
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
        slice->setBrush(QColor::fromHsl((i * 360 / series->slices().size()), 150, 200));
    }

    // Création du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Leaves Vacation types");
    chart->legend()->setVisible(true);

    // Affichage du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 500);
    chartView->show();
}








void Employe::enregistrerHistorique(const QString& operation) {
    QFile file("C:\\Users\\MSI GP76\\OneDrive - ESPRIT\\Bureau\\employe.txt");

    // Ouvrir le fichier en mode ajout
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // Écrire les informations dans le fichier
        out << timestamp << " - " << operation << " - "
            << "CIN: " << CIN << ", "
            << "NOM_E: " << NOM_E << ", "
               << "PRENOM_E: " << PRENOM_E << ", "
            << "ADRESSE: " << ADRESSE << ", "
            << "EMAIL: " << EMAIL << ", "
            << "POST: " << POST << ", "
            << "TELEPHONE: " << TELEPHONE << "," // Ajoutez d'autres attributs si nécessaire
        << "LEAVE_TYPE: " << LEAVE_TYPE << ", "
            << "NBDAYS: " << NBDAYS << "\n";
        file.close();
    } else {
        qDebug() << "Impossible d'ouvrir le fichier historique pour écriture.";
    }
}


void Employe::enregistrerHistoriqueCong(const QString& operation) {
    QFile file("C:\\Users\\MSI GP76\\OneDrive - ESPRIT\\Bureau\\Cong.txt");

    // Ouvrir le fichier en mode ajout
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // Écrire les informations dans le fichier
        out << timestamp << " - " << operation << " - "
            << "CIN: " << CIN << ", "
            << "NOM_E: " << NOM_E << ", "
               << "PRENOM_E: " << PRENOM_E << ", "
            << "ADRESSE: " << ADRESSE << ", "
            << "EMAIL: " << EMAIL << ", "
            << "POST: " << POST << ", "
            << "TELEPHONE: " << TELEPHONE << "," // Ajoutez d'autres attributs si nécessaire
        << "LEAVE_TYPE: " << LEAVE_TYPE << ", "
            << "NBDAYS: " << NBDAYS << "\n";
        file.close();
    } else {
        qDebug() << "Impossible d'ouvrir le fichier historique pour écriture.";
    }
}







