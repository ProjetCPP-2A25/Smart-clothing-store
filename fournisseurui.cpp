#include "fournisseurui.h"
#include "ui_fournisseurui.h"
#include "statistique.h"
#include <QFile>
#include <QPixmap>
#include <QPainter>
#include <QPrinter>
#include <QMessageBox>
#include "chatgptclient.h"

fournisseurUI::fournisseurUI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::fournisseurUI)
{
    ui->setupUi(this);
    client = new ChatGPTClient(this);

    // Connect the responseReceived signal to a slot to display responses in the UI
    connect(client, &ChatGPTClient::responseReceived, this, [this](const QString &response) {
        // Append the response from the model to the text edit
        ui->output->append("GPT: " + response);
    });
}

fournisseurUI::~fournisseurUI()
{
    delete ui;
}

void fournisseurUI::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    QSqlQueryModel* model = f.afficher();
    ui->tableView->setModel(model);
}

void fournisseurUI::clearFields()
{
    ui->ID->clear();
    ui->NAME->clear();
    ui->ADRESSE->clear();
    ui->EMAIL->clear();
    ui->TELEPHONE->clear();
    ui->CONTACT->clear();
}

void fournisseurUI::on_add_clicked()
{
    int id = ui->ID->text().toInt();
    QString name = ui->NAME->text();
    QString adresse = ui->ADRESSE->text();
    QString email = ui->EMAIL->text();
    QString contact = ui->CONTACT->text();
    int telephone = ui->TELEPHONE->text().toInt();

    fournisseur f(id, name, adresse, email, contact, telephone);

    bool test = f.Ajouter();
    if (test) {
        clearFields();
        ui->tableView->setModel(f.afficher());
        QMessageBox::information(nullptr, QObject::tr("Sucsess !!"),
                              QObject::tr("fournisseur ajouté."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error !!"),
                              QObject::tr("Cannot add fournisseur."), QMessageBox::Cancel);
    }
}


void fournisseurUI::on_update_clicked()
{
    int id = ui->ID->text().toInt();
    QString name = ui->NAME->text();
    QString adresse = ui->ADRESSE->text();
    QString email = ui->EMAIL->text();
    QString contact = ui->CONTACT->text();
    int telephone = ui->TELEPHONE->text().toInt();

    fournisseur f(id, name, adresse, email, contact, telephone);

    bool test = f.modifier();
    if (test) {
        clearFields();
        ui->tableView->setModel(f.afficher());
        QMessageBox::information(nullptr, QObject::tr("Sucsess !!"),
                                 QObject::tr("fournisseur modifié."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error !!"),
                              QObject::tr("Cannot edit fournisseur."), QMessageBox::Cancel);
    }

}


void fournisseurUI::on_deletebt_clicked()
{
    fournisseur f1;
    f1.Supprimer(ui->IDS->text().toInt());
    ui->tableView->setModel(f.afficher());
}


void fournisseurUI::on_pushButton_rech_clicked()
{
    QString val=ui->lineEdit_rech->text();
    QString option=ui->comboBox_rech->currentText();

    if((val!="")&&(option=="Nom"))
    {        ui->tableView->setModel(f.afficher_name(val));}
    else if((val!="")&&(option=="Adresse"))
    {
        ui->tableView->setModel(f.afficher_adresse(val));
    }
    else if((val!="")&&(option=="Email"))
    {
        ui->tableView->setModel(f.afficher_email(val));
    }
}


void fournisseurUI::on_comboBox_tri_currentIndexChanged(int index)
{
    QString choix=ui->comboBox_tri->currentText();
    ui->tableView->setModel(f.afficher_choix(choix));
}


void fournisseurUI::on_pushButton_stat_clicked()
{
    statistique S;
    S.exec();
}


void fournisseurUI::on_pushButton_pdf_clicked()
{
    // Assuming 'id' comes from the input field as in the original code
    int id = ui->lineEdit_pdf->text().toInt();

    // Create a fournisseur pointer and fetch data from the database
    fournisseur *Four = f.readfournisseur(id);

    // Retrieve the supplier details (from the fournisseur object)
    QString id_string = QString::number(Four->getId());
    QString name_string = Four->getName();
    QString adresse_string = Four->getAdresse();
    QString email_string = Four->getEmail();
    QString contact_string = Four->getContact();
    QString telephone_string = QString::number(Four->getTelephone());

    // Define the PDF file path
    QString pdfFilePath = "C:/Users/IBRI/Desktop/interface/pdf/" + name_string + "_" + id_string + ".pdf";

    // Create a printer and configure it
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(pdfFilePath);

    // Create a painter for drawing on the PDF
    QPainter painter;
    if (!painter.begin(&printer))
    {
        qWarning() << "Failed to open PDF file for writing";
        return;
    }

    // Set font and styling for the PDF
    painter.setFont(QFont("Bahnschrift Light", 25));
    painter.setPen(Qt::blue);

    // Draw the header information on the PDF
    painter.drawText(130, 230, "Fournisseur Information");
    painter.setPen(Qt::black);
    painter.drawText(120, 150, "Fournisseur Management System");

    // Draw the supplier details
    painter.drawText(150, 300, "ID: " + id_string);
    painter.drawText(150, 400, "Name: " + name_string);
    painter.drawText(150, 500, "Adresse: " + adresse_string);
    painter.drawText(150, 600, "Email: " + email_string);
    painter.drawText(150, 700, "Contact: " + contact_string);
    painter.drawText(150, 800, "Telephone: " + telephone_string);

    // End the drawing process
    painter.end();

}



void fournisseurUI::on_send_clicked()
{
    QString userInput = ui->input->text(); // Retrieve user input from lineEdit
    if (!userInput.isEmpty()) {
        // Send the user input to ChatGPT
        client->sendRequest(userInput);
        // Display the user input in the text edit
        ui->output->append("You: " + userInput);
        // Clear the input field
        ui->input->clear();
    }
}
