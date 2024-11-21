#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "livraison.h"
#include <QDate>
#include <QSqlQuery>
#include <QApplication>
#include <QLineEdit>
#include <QString>
#include <QIntValidator>
#include <QTextEdit>
#include "QSqlError"
#include "mainwindow.h"
#include <QStandardItemModel>
#include <QStandardItem>

#include <QtCore/QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QByteArray>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QSqlQuery>

// Constructor for MainWindow
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    calendar(new QCalendarWidget(this)),
    noteLabel(new QLabel("Cliquez sur une date pour voir les détails.", this)),
    serial(new QSerialPort(this)),
    isArduinoConnected(false)
{
    ui->setupUi(this);


        connectToArduino();

    // Connect the button signals to the slots
    connect(ui->openDoorButton, &QPushButton::clicked, this, &MainWindow::on_openDoorButton_clicked);
        connect(ui->closeDoorButton, &QPushButton::clicked, this, &MainWindow::on_closeDoorButton_clicked);

    // Read data from Arduino when it's available
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readFromArduino);


    // Connect signals and slots
    connect(ui->pushButton_ajouter, SIGNAL(clicked()), this, SLOT(on_pushButton_ajouter_clicked()));
    connect(ui->supprimer, SIGNAL(clicked()), this, SLOT(on_supprimer_Clicked()));
    connect(ui->modifier, SIGNAL(clicked()), this, SLOT(on_modifier_Clicked()));
    connect(ui->boutonTri, SIGNAL(clicked()), this, SLOT(afficherLivraisons()));
    connect(ui->boutonRechercher, SIGNAL(clicked()), this, SLOT(on_rechercher_clicked()));
    connect(ui->boutonExporterCSV, SIGNAL(clicked()), this, SLOT(exporterEnCSV()));
    connect(ui->sendEmailButton, SIGNAL(clicked()), this, SLOT(on_sendMailButton_clicked()));
    connect(ui->pushButton_stats, &QPushButton::clicked, this, &MainWindow::afficherLivraisonsStats);
    connect(ui->boutonTri, &QPushButton::clicked, this, &MainWindow::onTrierClicked);


    // Initialize QNetworkAccessManager
    networkManager = new QNetworkAccessManager(this);

    // Connect the calendar widget to handle date clicks
    connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &MainWindow::onDateClicked);

    afficherLivraisons(); // Display deliveries initially
   // afficherLivraisonsStats();  // Afficher les statistiques dès le démarrage



}

MainWindow::~MainWindow()
{
    if (serial->isOpen()) {
        serial->close();
    }
    delete ui;

}
void MainWindow::connectToArduino()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        arduinoPort = info.portName();
        serial->setPortName(arduinoPort);
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        if (serial->open(QIODevice::ReadWrite)) {
            ui->connectionStatusLabel->setText("Connected to Arduino on " + arduinoPort);
            isArduinoConnected = true;
            return;
        }
    }

    ui->connectionStatusLabel->setText("Failed to connect to Arduino");
}


void MainWindow::on_openDoorButton_clicked()
{
    if (isArduinoConnected) {
        sendCommandToArduino("OPEN");
    }
}

void MainWindow::on_closeDoorButton_clicked()
{
    if (isArduinoConnected) {
        sendCommandToArduino("CLOSE");
    }
}

void MainWindow::sendCommandToArduino(const QByteArray &command)
{
    if (serial->isOpen()) {
        serial->write(command);
        qDebug() << "Sent to Arduino:" << command;
    }
}

void MainWindow::readFromArduino()
{
    QByteArray data = serial->readAll();
    QString distanceData = QString(data);
    ui->distanceTextEdit->setPlainText("Distance: " + distanceData);
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    // Récupération des informations saisies
    int ID_LIVRAISON = ui->lineEdit_id->text().toInt();
    QDate DATE_PREVUE = ui->dateEdit_dateprevue->date();
    QDate DATE_EFFECTUEE = ui->dateEdit_dateeffectuee->date();
    QString ADRESSE_LIVRAISON = ui->lineEdit_adresse->text();
    QString NOM_LIVREUR = ui->lineEdit_nomLivreur->text();
    QString EMAIL_LIVREUR = ui->lineEdit_emailLivreur->text();

    // Vérifications supplémentaires
    if (ADRESSE_LIVRAISON.isEmpty() || NOM_LIVREUR.isEmpty() || EMAIL_LIVREUR.isEmpty()) {
        QMessageBox::warning(this, tr("Champs manquants"),
                             tr("Veuillez remplir tous les champs obligatoires."), QMessageBox::Ok);
        return;
    }

    Livraison livraison(ID_LIVRAISON, DATE_PREVUE, DATE_EFFECTUEE, ADRESSE_LIVRAISON, NOM_LIVREUR, EMAIL_LIVREUR);

    if (livraison.existe(ID_LIVRAISON)) {
        QMessageBox::warning(this, tr("ID déjà existant"),
                             tr("L'ID de livraison existe déjà. Veuillez utiliser un ID unique."),
                             QMessageBox::Ok);
        return;
    }

    bool test = livraison.ajouter();
    if (test) {
        QMessageBox::information(this, tr("Succès"), tr("Ajout réussi."));
        ui->lineEdit_id->clear();
        ui->lineEdit_nomLivreur->clear();
        ui->lineEdit_emailLivreur->clear();
        ui->lineEdit_adresse->clear();
        afficherLivraisons();
        updateCalendar() ;//actualiser calendrier

        // Réactiver le tri pour toutes les colonnes après avoir ajouté la ligne
        ui->table_livraisons->setSortingEnabled(true);  // S'assurer que le tri reste activé
    }
}




void MainWindow::on_supprimer_Clicked()
{
    // Récupérer l'ID de la livraison
    int livraisonId = ui->lineEdit_id2->text().toInt();

    // Validation de l'ID
    if (livraisonId == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    // Vérifier si la livraison existe avant de la supprimer
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM livraisons WHERE ID_LIVRAISON = :ID_LIVRAISON");
    checkQuery.bindValue(":ID_LIVRAISON", livraisonId);
    checkQuery.exec();

    if (checkQuery.next() && checkQuery.value(0).toInt() == 0) {
        // Si aucune livraison n'est trouvée avec cet ID
        QMessageBox::warning(this, "Erreur", "Aucune livraison trouvée avec cet ID.");
        return;
    }

    // Suppression sans confirmation
    QSqlQuery query;
    query.prepare("DELETE FROM livraisons WHERE ID_LIVRAISON = :ID_LIVRAISON");
    query.bindValue(":ID_LIVRAISON", livraisonId);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "La livraison a été supprimée avec succès.");
        afficherLivraisons();  // Rafraîchir l'affichage
        ui->lineEdit_id2->clear(); // Réinitialiser le champ
        updateCalendar() ;//actualiser calendrier

    } else {
        // Erreur détaillée
        QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression de la livraison. Veuillez réessayer.");
        qDebug() << "Erreur SQL : " << query.lastError().text();
    }
}



void MainWindow::afficherLivraisons() {
    ui->table_livraisons->setRowCount(0);
    QSqlQuery query("SELECT ID_LIVRAISON, DATE_PREVUE, DATE_EFFECTUEE, "
                    "ADRESSE_LIVRAISON, NOM_LIVREUR, EMAIL_LIVREUR FROM livraisons");

    QBrush highlightBrush(Qt::green); // Couleur pour les dates prévues

    int row = 0;
    while (query.next()) {
        ui->table_livraisons->insertRow(row);

        QString datePrevue = query.value("DATE_PREVUE").toDate().toString("dd/MM/yyyy");
        QString dateEffectuee = query.value("DATE_EFFECTUEE").toDate().toString("dd/MM/yyyy");

        ui->table_livraisons->setItem(row, 0, new QTableWidgetItem(query.value("ID_LIVRAISON").toString()));
        ui->table_livraisons->setItem(row, 1, new QTableWidgetItem(datePrevue));
        ui->table_livraisons->setItem(row, 2, new QTableWidgetItem(dateEffectuee));
        ui->table_livraisons->setItem(row, 3, new QTableWidgetItem(query.value("ADRESSE_LIVRAISON").toString()));
        ui->table_livraisons->setItem(row, 4, new QTableWidgetItem(query.value("NOM_LIVREUR").toString()));
        ui->table_livraisons->setItem(row, 5, new QTableWidgetItem(query.value("EMAIL_LIVREUR").toString()));

        // Colorer la date prévue dans le calendrier
        QDate prevDate = query.value("DATE_PREVUE").toDate();
        QTextCharFormat format = ui->calendarWidget->dateTextFormat(prevDate);
        format.setBackground(highlightBrush);
        ui->calendarWidget->setDateTextFormat(prevDate, format);

        row++;
    }
}







void MainWindow::on_modifier_Clicked()
{
    // Récupérer l'ID de la livraison à modifier
    int livraisonId = ui->lineEdit_id->text().toInt();

    // Validation de l'ID
    if (livraisonId == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID valide.");
        return;
    }

    // Récupérer les nouvelles valeurs des champs
    QString newAdresse = ui->lineEdit_adresse->text();
    QDate newDatePrevue = ui->dateEdit_dateprevue->date();
    QString newNomLivreur = ui->lineEdit_nomLivreur->text();  // Champ NOM_LIVREUR
    QString newEmailLivreur = ui->lineEdit_emailLivreur->text(); // Champ EMAIL_LIVREUR

    // Validation de base des champs
    if (newAdresse.isEmpty() || newNomLivreur.isEmpty() || newEmailLivreur.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs.");
        return;
    }

    // Vérifier si la livraison existe avant de la modifier
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM livraisons WHERE ID_LIVRAISON = :ID_LIVRAISON");
    checkQuery.bindValue(":ID_LIVRAISON", livraisonId);
    if (!checkQuery.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification de l'ID de la livraison.");
        qDebug() << "Erreur SQL : " << checkQuery.lastError().text();
        return;
    }

    if (checkQuery.next() && checkQuery.value(0).toInt() == 0) {
        // Si aucune livraison n'est trouvée avec cet ID
        QMessageBox::warning(this, "Erreur", "Aucune livraison trouvée avec cet ID.");
        return;
    }

    // Requête SQL pour modifier les informations
    QSqlQuery query;
    query.prepare("UPDATE livraisons SET ADRESSE_LIVRAISON = :ADRESSE_LIVRAISON, "
                  "DATE_PREVUE = :DATE_PREVUE, NOM_LIVREUR = :NOM_LIVREUR, "
                  "EMAIL_LIVREUR = :EMAIL_LIVREUR WHERE ID_LIVRAISON = :ID_LIVRAISON");
    query.bindValue(":ADRESSE_LIVRAISON", newAdresse);
    query.bindValue(":DATE_PREVUE", newDatePrevue);
    query.bindValue(":NOM_LIVREUR", newNomLivreur);
    query.bindValue(":EMAIL_LIVREUR", newEmailLivreur);
    query.bindValue(":ID_LIVRAISON", livraisonId);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "La livraison a été modifiée avec succès.");
        afficherLivraisons();  // Mettre à jour l'affichage après modification
        updateCalendar() ;//actualiser calendrier

        // Réinitialiser les champs uniquement si la modification a réussi
        ui->lineEdit_id->clear();
        ui->lineEdit_adresse->clear();
        ui->lineEdit_nomLivreur->clear();
        ui->lineEdit_emailLivreur->clear();
        // Rafraîchir la table après la suppression
    } else {
        // Erreur détaillée
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification de la livraison.");
        qDebug() << "Erreur SQL : " << query.lastError().text();
    }
}


void MainWindow::on_rechercher_clicked() {
    int id = ui->lineEdit_id->text().toInt();
    if (livraison.rechercher(id)) {
        qDebug() << "La livraison existe.";
        QMessageBox::information(this, "Recherche", "La livraison existe.");

        // Afficher les détails de la livraison, ou mettre à jour l'interface
    } else {
        qDebug() << "La livraison n'existe pas.";
        QMessageBox::critical(this, "Recherche", "La livraison n'existe pas.");
    }
}

void MainWindow::exporterEnCSV() {
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer sous", "", "Fichiers CSV (*.csv)");
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun emplacement sélectionné pour l'exportation.");
        return;
    }

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "\"ID Livraison\",\"Date Prévue\",\"Date Effectuée\",\"Adresse Livraison\",\"Nom Livreur\",\"Email Livreur\"\n";

        QSqlQuery query("SELECT ID_LIVRAISON, DATE_PREVUE, DATE_EFFECTUEE, ADRESSE_LIVRAISON, NOM_LIVREUR, EMAIL_LIVREUR FROM livraisons");
        while (query.next()) {
            out << "\"" << query.value("ID_LIVRAISON").toString() << "\","
                << "\"" << query.value("DATE_PREVUE").toDate().toString("yyyy-MM-dd") << "\","
                << "\"" << query.value("DATE_EFFECTUEE").toDate().toString("yyyy-MM-dd") << "\","
                << "\"" << query.value("ADRESSE_LIVRAISON").toString() << "\","
                << "\"" << query.value("NOM_LIVREUR").toString() << "\","
                << "\"" << query.value("EMAIL_LIVREUR").toString() << "\"\n";
        }

        QMessageBox::information(this, "Exportation réussie", "Les données ont été exportées avec succès en CSV.");
    }
}


void MainWindow::afficherLivraisonsStats()
{
    // Initialisation des compteurs
    int totalLivraisons = 0;
    int effectuees = 0;
    int enRetard = 0;

    // Requête SQL pour récupérer les livraisons avec les dates prévues et effectives
    QSqlQuery query("SELECT DATE_PREVUE, DATE_EFFECTUEE FROM LIVRAISONS");
    while (query.next()) {
        QDate datePrevue = query.value("DATE_PREVUE").toDate();
        QDate dateEffectuee = query.value("DATE_EFFECTUEE").toDate();

        // Vérifier si la livraison est effectuée à temps ou en retard
        if (!dateEffectuee.isNull()) {  // Si la livraison a été effectuée
            totalLivraisons++;
            if (dateEffectuee <= datePrevue) {
                effectuees++;  // Livraison effectuée à temps
            } else {
                enRetard++;  // Livraison en retard
            }
        }
    }

    // Si aucune livraison n'a été trouvée
    if (totalLivraisons == 0) {
        ui->statistiquesLabel->setText("Aucune livraison trouvée.");
        return;
    }

    // Calcul des pourcentages
    float pourcentageLivraisonsEffectuees = (effectuees * 100.0) / totalLivraisons;
    float pourcentageLivraisonsEnRetard = (enRetard * 100.0) / totalLivraisons;

    // Format the message using QString::number()
    QString message = "Livraisons effectuées à temps : " + QString::number(pourcentageLivraisonsEffectuees, 'f', 2) + "%, "
                      + "Livraisons en retard : " + QString::number(pourcentageLivraisonsEnRetard, 'f', 2) + "%";

    // Personnalisation du texte du QLabel avec la couleur et la taille
    ui->statistiquesLabel->setText(message);

    // Appliquer un style pour changer la couleur du texte et agrandir la taille de la police
    ui->statistiquesLabel->setStyleSheet("color: blue; font-size: 18px; font-weight: bold;");

    // Si vous voulez aussi un fond coloré pour le label
    ui->statistiquesLabel->setStyleSheet("color: blue; font-size: 14px; font-weight: bold; background-color: lightyellow; padding: 5px;");
}





void MainWindow::onTrierClicked() {
    QString critere = ui->comboBox->currentText(); // Récupère le critère sélectionné

    // Appeler la méthode de tri en fonction du critère
    afficherLivraisonsTriées(critere);
}


void MainWindow::afficherLivraisonsTriées(const QString& critere) {
    ui->table_livraisons->setRowCount(0);

    QString orderBy;
    if (critere == "ID") {
        orderBy = "ID_LIVRAISON";
    } else if (critere == "Nom") {
        orderBy = "NOM_LIVREUR";
    } else if (critere == "Date Prévue") {
        orderBy = "DATE_PREVUE";
    } else {
        return; // Aucun critère valide sélectionné
    }

    QSqlQuery query("SELECT ID_LIVRAISON, DATE_PREVUE, DATE_EFFECTUEE, "
                    "ADRESSE_LIVRAISON, NOM_LIVREUR, EMAIL_LIVREUR FROM livraisons "
                    "ORDER BY " + orderBy);

    QBrush highlightBrush(Qt::green); // Couleur pour les dates prévues

    int row = 0;
    while (query.next()) {
        ui->table_livraisons->insertRow(row);

        QString datePrevue = query.value("DATE_PREVUE").toDate().toString("dd/MM/yyyy");
        QString dateEffectuee = query.value("DATE_EFFECTUEE").toDate().toString("dd/MM/yyyy");

        ui->table_livraisons->setItem(row, 0, new QTableWidgetItem(query.value("ID_LIVRAISON").toString()));
        ui->table_livraisons->setItem(row, 1, new QTableWidgetItem(datePrevue));
        ui->table_livraisons->setItem(row, 2, new QTableWidgetItem(dateEffectuee));
        ui->table_livraisons->setItem(row, 3, new QTableWidgetItem(query.value("ADRESSE_LIVRAISON").toString()));
        ui->table_livraisons->setItem(row, 4, new QTableWidgetItem(query.value("NOM_LIVREUR").toString()));
        ui->table_livraisons->setItem(row, 5, new QTableWidgetItem(query.value("EMAIL_LIVREUR").toString()));

        // Colorer la date prévue dans le calendrier
        QDate prevDate = query.value("DATE_PREVUE").toDate();
        QTextCharFormat format = ui->calendarWidget->dateTextFormat(prevDate);
        format.setBackground(highlightBrush);
        ui->calendarWidget->setDateTextFormat(prevDate, format);

        row++;
    }
}



////////////////////////////////////////////////////////////////////////////////////////////////////debut de 1er metier:notfier livreur
void MainWindow::on_sendMailButton_clicked() {
    int currentRow = ui->table_livraisons->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a delivery row before sending an email.");
        return;
    }

    // Get recipient email (from column 5, zero-based index)
    QTableWidgetItem *emailItem = ui->table_livraisons->item(currentRow, 5);
    if (!emailItem) {
        QMessageBox::warning(this, "Invalid Data", "Email address not found in the selected row.");
        return;
    }

    // Fetch data from the selected row
    QTableWidgetItem *idItem = ui->table_livraisons->item(currentRow, 0);         // Column 0: Delivery ID
    QTableWidgetItem *scheduledDateItem = ui->table_livraisons->item(currentRow, 1); // Column 1: Scheduled Date
    QTableWidgetItem *assignmentDateItem = ui->table_livraisons->item(currentRow, 2); // Column 2: Assignment Date
    QTableWidgetItem *addressItem = ui->table_livraisons->item(currentRow, 3);      // Column 3: Delivery Address

    // Validate data
    if (!emailItem) {
        QMessageBox::warning(this, "Invalid Data", "Email address not found in the selected row.");
        return;
    }

    QString deliveryID = idItem ? idItem->text() : "Unknown ID";
    QString scheduledDate = scheduledDateItem ? scheduledDateItem->text() : "Unknown Scheduled Date";
    QString assignmentDate = assignmentDateItem ? assignmentDateItem->text() : "Unknown Assignment Date";
    QString address = addressItem ? addressItem->text() : "Unknown Address";
    QString recipientEmail = emailItem->text();

    // Compose email
    QString subject = "Upcoming Delivery Notification";
    QString body = QString(
                       "Subject: Upcoming Delivery Notification\n\n"
                       "Dear Delivery Partner,\n\n"
                       "We hope this email finds you well.\n\n"
                       "This is to inform you about your next delivery assignment for Resilients, our clothing store. "
                       "Please find the details below:\n\n"
                       "Delivery ID: %1\n"
                       "Scheduled Date: %2\n"
                       "Assignment Date: %3\n"
                       "Delivery Address: %4\n\n"
                       "We appreciate your dedication and punctuality in ensuring timely deliveries. Should you have any questions "
                       "or require further assistance, please feel free to reach out to us.\n\n"
                       "Thank you for your continued commitment to our team.\n\n"
                       "Best regards,\n"
                       "RABIE JLASSI\n"
                       "Resilients Clothing Store\n"
                       "our Contact Information: +216 23251512"
                       ).arg(deliveryID, scheduledDate, assignmentDate, address);

    // Send email
    sendEmail(recipientEmail, subject, body);
}

void MainWindow::sendEmail(const QString &to, const QString &subject, const QString &body) {
    // Create a secure socket
    QSslSocket *smtpSocket = new QSslSocket(this);

    // Connect to Gmail's SMTP server
    smtpSocket->connectToHostEncrypted("smtp.gmail.com", 465);
    if (!smtpSocket->waitForConnected(5000)) {
        QMessageBox::warning(this, "Connection Error", "Failed to connect to the SMTP server.");
        delete smtpSocket;
        return;
    }

    QTextStream stream(smtpSocket);

    // SMTP Communication
    auto sendCommand = [&](const QString &cmd) -> bool {
        stream << cmd << "\r\n";
        stream.flush();
        if (!smtpSocket->waitForReadyRead(5000)) {
            qDebug() << "Command Timeout:" << cmd;
            return false;
        }
        QString response = smtpSocket->readAll();
        qDebug() << "SMTP Server Response:" << response;
        return response.startsWith("2") || response.startsWith("3");
    };
    ;

    // Authenticate and send the email
    if (!sendCommand("EHLO smtp.gmail.com")) return;
    if (!sendCommand("AUTH LOGIN")) return;
    if (!sendCommand(QByteArray("jlassirabie9@gmail.com").toBase64())) return;
    if (!sendCommand(QByteArray("laka vkzm tprn czng").toBase64())) return;
    if (!sendCommand("MAIL FROM:<jlassirabie9@gmail.com>")) return;
    if (!sendCommand("RCPT TO:<" + to + ">")) return;
    if (!sendCommand("DATA")) return;

    // Email content
    stream << "Subject: " << subject.toUtf8() << "\r\n";
    stream << "To: " << to.toUtf8() << "\r\n";
    stream << "Content-Type: text/plain; charset=utf-8\r\n";
    stream << "\r\n" << body.toUtf8() << "\r\n";
    stream << ".\r\n";
    stream.flush();
    if (!smtpSocket->waitForReadyRead(5000)) {
        QMessageBox::warning(this, "Error", "Failed to send email.");
        delete smtpSocket;
        return;
    }

    // Close the connection
    sendCommand("QUIT");

    // Confirm success
    QMessageBox::information(this, "Success", "Email sent successfully.");
    smtpSocket->close();
    delete smtpSocket;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////fin de 1er metier
void MainWindow::onDateClicked(const QDate &date) {
    QString selectedDate = date.toString("dd/MM/yyyy");
    QString details;

    // Parcours des livraisons dans le tableau
    for (int row = 0; row < ui->table_livraisons->rowCount(); ++row) {
        QTableWidgetItem *dateItem = ui->table_livraisons->item(row, 1); // Colonne "DATE_PREVUE"
        if (dateItem && dateItem->text() == selectedDate) {
            // Récupération des informations de la livraison
            QString id = ui->table_livraisons->item(row, 0)->text();
            QString adresse = ui->table_livraisons->item(row, 3)->text();
            QString livreur = ui->table_livraisons->item(row, 4)->text();
            QString email = ui->table_livraisons->item(row, 5)->text(); // Email du livreur
            QString effectuee = ui->table_livraisons->item(row, 2)->text();

            // Construction des détails de la livraison à afficher
            details += QString("<b style='color: #2E8B57;'>ID:</b> <span style='color: #4682B4;'>%1</span><br>"
                               "<b style='color: #2E8B57;'>Adresse:</b> <span style='color: #4682B4;'>%2</span><br>"
                               "<b style='color: #2E8B57;'>Livreur:</b> <span style='color: #4682B4;'>%3</span><br>"
                               "<b style='color: #2E8B57;'>Email:</b> <span style='color: #4682B4;'>%4</span><br>"
                               "<b style='color: #2E8B57;'>Date Effectuée:</b> <span style='color: #4682B4;'>%5</span><br><br>")
                           .arg(id)
                           .arg(adresse)
                           .arg(livreur)
                           .arg(email) // Affichage de l'email
                           .arg(effectuee.isEmpty() ? "Non effectuée" : effectuee);
        }
    }

    // Affichage des détails dans le label
    if (details.isEmpty()) {
        ui->noteLabel->setText("<span style='color: red;'>Aucune livraison prévue pour cette date.</span>");
    } else {
        ui->noteLabel->setText(details);
    }

    // Appliquer une feuille de style pour améliorer l'apparence générale du label
    ui->noteLabel->setStyleSheet("background-color: #f0f8ff; border: 1px solid #87ceeb; padding: 10px;");
}



void MainWindow::updateCalendar() {
    // Réinitialiser tous les formats des dates dans le calendrier
    QDate startDate = ui->calendarWidget->minimumDate();
    QDate endDate = ui->calendarWidget->maximumDate();

    QTextCharFormat defaultFormat; // Format par défaut
    for (QDate date = startDate; date <= endDate; date = date.addDays(1)) {
        ui->calendarWidget->setDateTextFormat(date, defaultFormat);
    }

    // Appliquer un format spécifique aux dates prévues
    QBrush highlightBrush(Qt::green); // Couleur verte pour les dates prévues
    for (int row = 0; row < ui->table_livraisons->rowCount(); ++row) {
        QTableWidgetItem *dateItem = ui->table_livraisons->item(row, 1); // Colonne "DATE_PREVUE"
        if (dateItem) {
            QDate prevDate = QDate::fromString(dateItem->text(), "dd/MM/yyyy");
            if (prevDate.isValid()) {
                QTextCharFormat format = ui->calendarWidget->dateTextFormat(prevDate);
                format.setBackground(highlightBrush);
                ui->calendarWidget->setDateTextFormat(prevDate, format);
            }
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////fin 2eme metier





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////arduino
/*void MainWindow::update_label()
{
    data=A.read_from_arduino();
    if(data=="1")
        ui->label_3->setText("ON"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON
    else if (data=="0")
        ui->label_3->setText("OFF"); // si les données reçues de arduino via la liaison série sont égales à 0
    //alors afficher ON
}*/
