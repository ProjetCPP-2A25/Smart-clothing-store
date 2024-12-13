#include "fournisseur.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include "fournisseur.h"

fournisseur::fournisseur() {
    id = 0;
    name = "";
    adresse = "";
    email = "";
    contact = "";
    telephone = 0;
}

fournisseur::fournisseur(int Id, QString Name, QString Adresse, QString Email, QString Contact, int Telephone) {
    id = Id;
    name = Name;
    adresse = Adresse;
    email = Email;
    contact = Contact;
    telephone = Telephone;
}

// Getters
int fournisseur::getId()
{
    return id;  // Assuming 'id' is a private member variable of type int
}

QString fournisseur::getName()
{
    return name;  // Assuming 'name' is a private member variable of type QString
}

QString fournisseur::getAdresse()
{
    return adresse;  // Assuming 'adresse' is a private member variable of type QString
}

QString fournisseur::getEmail()
{
    return email;  // Assuming 'email' is a private member variable of type QString
}

QString fournisseur::getContact()
{
    return contact;  // Assuming 'contact' is a private member variable of type QString
}

int fournisseur::getTelephone()
{
    return telephone;  // Assuming 'telephone' is a private member variable of type int
}

// Setters
void fournisseur::setId(int id)
{
    this->id = id;  // Assign the provided 'id' to the private member variable 'id'
}

void fournisseur::setName(QString name)
{
    this->name = name;  // Assign the provided 'name' to the private member variable 'name'
}

void fournisseur::setAdresse(QString adresse)
{
    this->adresse = adresse;  // Assign the provided 'adresse' to the private member variable 'adresse'
}

void fournisseur::setEmail(QString email)
{
    this->email = email;  // Assign the provided 'email' to the private member variable 'email'
}

void fournisseur::setContact(QString contact)
{
    this->contact = contact;  // Assign the provided 'contact' to the private member variable 'contact'
}

void fournisseur::setTelephone(int telephone)
{
    this->telephone = telephone;  // Assign the provided 'telephone' to the private member variable 'telephone'
}


bool fournisseur::Ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO fournisseur (id, name, adresse, email, contact, telephone) "
                  "VALUES (:id, :name, :adresse, :email, :contact, :telephone)");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":contact", contact);
    query.bindValue(":telephone", telephone);
    bool success = query.exec();
        if (success) {
            enregistrerHistorique("Ajout d'un fournisseur");
        }
        return success;
}

QSqlQueryModel* fournisseur::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT id, name, adresse, email, contact, telephone FROM fournisseur");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));

    return model;
}

bool fournisseur::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE fournisseur SET name = :name, adresse = :adresse, email = :email, "
                  "contact = :contact, telephone = :telephone WHERE id = :id");

    query.bindValue(":name", name);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":contact", contact);
    query.bindValue(":telephone", telephone);
    query.bindValue(":id", id);

    bool success = query.exec();
        if (success) {
            // Enregistrer l'historique de la modification
            enregistrerHistorique("Modification d'un fournisseur avec ID: " + QString::number(id));
        }
        return success;
}

bool fournisseur::Supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM fournisseur WHERE id = :id");
    query.bindValue(":id", id);
    bool success = query.exec();
        if (success) {
            // Enregistrer l'historique de la suppression
            enregistrerHistorique("Suppression d'un fournisseur avec ID: " + QString::number(id));
        }
        return success;
}

// recherche
QSqlQueryModel *fournisseur::afficher_name(QString ch)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT id, name, adresse, email, contact, telephone FROM fournisseur where name = '"+ch+"'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));

    return model;
}

QSqlQueryModel *fournisseur::afficher_adresse(QString ch)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT id, name, adresse, email, contact, telephone FROM fournisseur where adresse = '"+ch+"'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));

    return model;
}

QSqlQueryModel *fournisseur::afficher_email(QString ch)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT id, name, adresse, email, contact, telephone FROM fournisseur where email = '"+ch+"'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));

    return model;
}

// ## Tri ## //

QSqlQueryModel *fournisseur:: afficher_choix(QString choix)
{
    QSqlQueryModel * model =new QSqlQueryModel();

    if(choix=="id croissants")
    {
        model->setQuery("SELECT id, name, adresse, email, contact, telephone FROM fournisseur ORDER BY id ASC");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
    }
    else if(choix=="id decroissants")
    {
        model->setQuery("SELECT id, name, adresse, email, contact, telephone FROM fournisseur ORDER BY id DESC");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
    }
    else if(choix=="nom decroissants")
    {
        model->setQuery("SELECT id, name, adresse, email, contact, telephone FROM fournisseur ORDER BY name DESC");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
    }
    else if(choix=="nom croissants")
    {
        model->setQuery("SELECT id, name, adresse, email, contact, telephone FROM fournisseur ORDER BY name ASC");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));

    }
    else if(choix=="contact decroissants")
    {
        model->setQuery("SELECT id, name, adresse, email, contact, telephone FROM fournisseur ORDER BY contact DESC");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));
    }
    else if(choix=="contact croissants")
    {
        model->setQuery("SELECT id, name, adresse, email, contact, telephone FROM fournisseur ORDER BY contact ASC");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Telephone"));

    }
    return model ;
}

// ## Statistique ## //

int fournisseur::statistique1(){
    int count = 0;

    QSqlQuery requete("SELECT * FROM fournisseur WHERE adresse like 'tunis'");

    while(requete.next()) {
        count++;
    }

    return count;
}

int fournisseur::statistique2(){
    int count = 0;

    QSqlQuery requete("SELECT * FROM fournisseur WHERE adresse like 'etranger'");

    while(requete.next()) {
        count++;
    }

    return count;
}

// PDF
fournisseur* fournisseur::readfournisseur(int val)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM fournisseur WHERE id = :val");

    query.bindValue(":val", val);

    if (query.exec())
    {
        while (query.next())
        {
            setId(query.value(0).toInt());
            setName(query.value(1).toString());
            setAdresse(query.value(2).toString());
            setEmail(query.value(3).toString());
            setContact(query.value(4).toString());
            setTelephone(query.value(5).toInt());
        }
    }
    return this;
}
void fournisseur::enregistrerHistorique(const QString& operation) {
    QFile file("C:\\Users\\MSI GP76\\OneDrive - ESPRIT\\Bureau\\ibri\\fournisseur_historique.txt");

    // Ouvrir le fichier en mode ajout
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // Écrire les informations dans le fichier
        out << timestamp << " - " << operation << " - "
            << "ID: " << id << ", "
            << "Nom: " << name << ", "
            << "Adresse: " << adresse << ", "
            << "Email: " << email << ", "
            << "Contact: " << contact << ", "
            << "Téléphone: " << telephone << "\n"; // Ajoutez d'autres attributs si nécessaire

        file.close();
    } else {
        qDebug() << "Impossible d'ouvrir le fichier historique pour écriture.";
    }
}
