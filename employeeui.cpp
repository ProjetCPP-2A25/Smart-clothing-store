#include "employeeui.h"
#include "ui_employeeui.h"

employeeUI::employeeUI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::employeeUI)
{
    ui->setupUi(this);
}

employeeUI::~employeeUI()
{
    delete ui;
}

void employeeUI::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    ui->tableView->setModel(e.afficher());
}

void employeeUI::on_ajouter_clicked()
{
    int id = ui->id->text().toInt();
    QString nom = ui->nom->text();
    QDate date_n = ui->date_n->date();
    QString adresse = ui->adresse->text();
    int numtel = ui->numtel->text().toInt();
    QString email = ui->email->text();
    int cin = ui->cin->text().toInt();
    QDate date_e = ui->date_e->date();
    QTime horaire_d = ui->h_d->time();
    QTime horaire_f = ui->h_f->time();
    int conge = ui->conge->text().toInt();
    int absence = ui->absennce->text().toInt();
    float salaire = ui->salaire->text().toFloat();
    float prime = ui->prime->text().toFloat();
    QString mdp = ui->mdp->text();

    employee e(id,nom, date_n, adresse, numtel, email, cin, date_e, horaire_d, horaire_f, conge, absence, salaire, prime, mdp);

    bool test;
    test = e.Ajouter();
    if(test==true){
        ui->tableView->setModel(e.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Error !!"),
                              QObject::tr(""
                                          "Can not add employee."), QMessageBox::Cancel);
    }
}


void employeeUI::on_modifier_clicked()
{
    int id = ui->id->text().toInt();
    QString nom = ui->nom->text();
    QDate date_n = ui->date_n->date();
    QString adresse = ui->adresse->text();
    int numtel = ui->numtel->text().toInt();
    QString email = ui->email->text();
    int cin = ui->cin->text().toInt();
    QDate date_e = ui->date_e->date();
    QTime horaire_d = ui->h_d->time();
    QTime horaire_f = ui->h_f->time();
    int conge = ui->conge->text().toInt();
    int absence = ui->absennce->text().toInt();
    float salaire = ui->salaire->text().toFloat();
    float prime = ui->prime->text().toFloat();
    QString mdp = ui->mdp->text();

    employee e(id,nom, date_n, adresse, numtel, email, cin, date_e, horaire_d, horaire_f, conge, absence, salaire, prime, mdp);

    bool test;
    test = e.modifier();
    if(test==true){
        ui->tableView->setModel(e.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Error !!"),
                              QObject::tr(""
                                          "Can not edit employee."), QMessageBox::Cancel);
    }

}


void employeeUI::on_del_clicked()
{
    employee E1;
    E1.setId(ui->del_line->text().toInt());
    E1.Supprimer(E1.getId());
    ui->tableView->setModel(e.afficher());
}

