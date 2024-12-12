#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "connection.h"
#include <QMessageBox>
#include <QObject>
#include <QString>
#include <QStack>
#include <QFocusEvent>
#include <QSortFilterProxyModel>
#include <QFileDialog>
#include <QFileInfo>
#include <QPrinter>
#include <QTextStream>
#include <QTextDocument>
#include <QDateTime>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QKeyEvent>
#include <QPdfWriter>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QPieSlice>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>
#include <QHorizontalBarSeries>
#include <QSslSocket>
#include <QUuid>
#include "client.h"
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
#include <QVBoxLayout>
#include <QPushButton>

#include <QFile>
#include <QPixmap>
#include <QPainter>
#include <QPrinter>
#include <QMessageBox>
#include "chatgptclient.h"

#include <QFile>
#include <QPixmap>
#include <QPainter>
#include <QPrinter>
#include <QMessageBox>
#include "chatgptclient.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),serialPort(new QSerialPort(this)),
    ui(new Ui::MainWindow)
{
    setupSerialPort();
    ui->setupUi(this);

    QSettings settings("UrbanElegance", "UrbanElegance");



    ui->jobECombo->addItems({
            "Store Manager",
            "Assistant Manager",
            "Sales Associates",
            "Merchandisers",
            "Stock Room/Inventory Associates",
            "Customer Service Representatives"
        });
    connect(ui->AddEmp, &QPushButton::clicked, this, &MainWindow::on_AddEmp_clicked);
    ui->IDEMP->setValidator(new QIntValidator(100000, 99999999, this));
    ui->phone_E->setValidator(new QIntValidator(0, 99999999, this));
    ui->list_emp->setModel(e.afficherEMP());
    ui->list_cong->setModel(e.afficherCONG());;
    ui->affichage_2->setModel(c.afficher());
    //connect(ui->Exportlist_btn, &QPushButton::clicked, this, &MainWindow::on_Exportlist_btn_clicked);
    //connect(ui->Exportlist_btn_2, &QPushButton::clicked, this, &MainWindow::on_Exportlist_btn_2_clicked);
    connect(ui->seach_list, &QLineEdit::textChanged, this, &MainWindow::searchInListEmp);
    connect(ui->seach_list2, &QLineEdit::textChanged, this, &MainWindow::searchInListEmployee2);
    connect(ui->seach_cong, &QLineEdit::textChanged, this, &MainWindow::searchInListCong);
    connect(ui->seach_cong2, &QLineEdit::textChanged, this, &MainWindow::searchInListCong2);
    //connect(ui->stat, &QPushButton::clicked, this, &MainWindow::on_stat_clicked);
    connect(ui->rechercher, SIGNAL(clicked()), this, SLOT(on_rechercher_clicked()));
    connect(ui->refrech_3, &QPushButton::clicked, this, &MainWindow::on_refrech_3_clicked);







    connect(ui->Home, &QTabWidget::currentChanged, this, &MainWindow::on_tabBarClicked);


    //ui->Home->setCurrentIndex(0); // Assuming the login page is at index 0
ui->login->show();
ui->lesgestion->hide();

    //connect(ui->downloadLeaveHistory, &QPushButton::clicked, this, &MainWindow::on_downloadLeaveHistory_clicked);


//client
ui->id_client_2->setValidator(new QIntValidator(10000000,99999999,this));

ui->telephone_client_2->setValidator(new QIntValidator(10000000,99999999,this));


//livraison
  afficherLivraisons();
//connectToArduino();
  //connect(serial, &QSerialPort::readyRead, this, &MainWindow::readFromArduino);

networkManager = new QNetworkAccessManager(this);



//fournisseur
client = new ChatGPTClient(this);

// Connect the responseReceived signal to a slot to display responses in the UI
connect(client, &ChatGPTClient::responseReceived, this, [this](const QString &response) {
    // Append the response from the model to the text edit
    ui->output->append("GPT: " + response);
});

}


MainWindow::~MainWindow()
{
    if (serialPort->isOpen()) {
        serialPort->close(); // Close if open
    }
    delete ui;

}




////////////////////////////////////////////////////////////////////////////////////////////////////




void MainWindow::on_AddEmp_clicked()
{
    // Collect data from the form fields
    int CIN = ui->IDEMP->text().toInt();
    QString NOM_E = ui->nameE->text();
    QString PRENOM_E = ui->prenomE->text();
    QString POST = ui->jobECombo->currentText();
    QString EMAIL = ui->mailE->text();
    int TELEPHONE = ui->phone_E->text().toInt();
    QString ADRESSE = ui->adresse_E->text();

    // Use placeholder values for leave-related attributes
    QString LEAVE_TYPE = "";               // Default leave type
    QDate FIRST_DAY_OF_LEAVE = QDate();    // Default (null) date
    QDate LAST_DAY_OF_LEAVE = QDate();     // Default (null) date
    int NBDAYS = 0;                        // Default leave days count

    // Create the employee object with placeholders for unused attributes
    Employe e(CIN, NOM_E, PRENOM_E, POST, EMAIL, TELEPHONE, ADRESSE, LEAVE_TYPE, FIRST_DAY_OF_LEAVE, LAST_DAY_OF_LEAVE, NBDAYS);

    // Call the ajouter method to add the employee
    bool test = e.ajouter();
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Successful"),
                                 QObject::tr("Employee added successfully.\nClick Cancel to exit."), QMessageBox::Cancel);

        // Send a welcome email to the new employee
        QString subject = "Welcome to Our Company!";
        QString body = QString(
            "Dear %1 %2,\n\n"
            "We are thrilled to welcome you to Urban Elegance. Here are your employee details:\n\n"
            "Email: %3\n"
            "Password: %4\n\n"
            "Feel free to reach out if you have any questions. We look forward to your contributions!\n\n"
            "Best regards,\n"
            "Asma Messaoudi,\n"
            "Urban Elegance Team"
        ).arg(NOM_E, PRENOM_E, EMAIL, QString::number(CIN));

        if (sendEmail(EMAIL, subject, body)) {
            QMessageBox::information(this, "Email Sent", "Welcome email sent successfully to " + EMAIL + "!");
        } else {
            QMessageBox::critical(this, "Email Error", "Failed to send welcome email to " + EMAIL + ".");
        }

        // Clear UI fields after successful addition
        ui->IDEMP->clear();
        ui->nameE->clear();
        ui->prenomE->clear();
        ui->jobECombo->setCurrentIndex(0);
        ui->mailE->clear();
        ui->phone_E->clear();
        ui->adresse_E->clear();
    }
    /*else
    {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Failed to add employee.\nClick Cancel to exit."), QMessageBox::Cancel);
    }*/
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////fin de 1er metier
///////////////////////////////////////////////////////////////////////////



bool MainWindow::sendEmail(const QString &to, const QString &subject, const QString &body) {

    QSslSocket smtpSocket;
    smtpSocket.connectToHostEncrypted("smtp.gmail.com", 465);
    if (!smtpSocket.waitForConnected(5000)) {
        qDebug() << "SMTP Error: Unable to connect to server.";
        return false;
    }

    QTextStream stream(&smtpSocket);
    auto sendCommand = [&](const QString &cmd) -> bool {
        stream << cmd << "\r\n";
        stream.flush();
        if (!smtpSocket.waitForReadyRead(5000)) {
            qDebug() << "SMTP Error: Timeout waiting for server response to" << cmd;
            return false;
        }
        QString response = smtpSocket.readAll();
        qDebug() << "SMTP Response:" << response;
        return response.startsWith("2") || response.startsWith("3");
    };

    // Authenticate
    if (!sendCommand("EHLO smtp.gmail.com")) return false;
    if (!sendCommand("AUTH LOGIN")) return false;
    if (!sendCommand(QByteArray("jlassirabie9@gmail.com").toBase64())) return false; // Replace with secure retrieval
    if (!sendCommand(QByteArray("laka vkzm tprn czng").toBase64())) return false;

    // Mail headers
    if (!sendCommand("MAIL FROM:<hellourbanelegance@gmail.com>")) return false;
    if (!sendCommand("RCPT TO:<" + to + ">")) return false;
    if (!sendCommand("DATA")) return false;

    // Mail body
    stream << "Subject: " << subject << "\r\n";
    stream << "To: " << to << "\r\n";
    stream << "Content-Type: text/plain; charset=utf-8\r\n";
    stream << "\r\n" << body << "\r\n.\r\n";
    stream.flush();

    if (!smtpSocket.waitForReadyRead(5000)) {
        qDebug() << "SMTP Error: Failed to send email content.";
        return false;
    }

    // Close session
    sendCommand("QUIT");
    smtpSocket.close();

    return true;
}

///////////////////////////////////////////////////////////////////////////














void MainWindow::readFromArduino()
{
    QByteArray data = serial->readAll();
    QString distanceData = QString(data);

    if (isAutoMode) {
        // Update distanceTextEdit only in automatic mode
        ui->distanceTextEdit->setText(distanceData);
        qDebug() << "Auto Mode: Displayed distance:" << distanceData;
    } else {
        // Clear distanceTextEdit in manual mode
        ui->distanceTextEdit->clear();
        qDebug() << "Manual Mode: Cleared distance label.";
    }

    qDebug() << "Received from Arduino:" << distanceData;
}

























void MainWindow::on_Updatelist_btn2_clicked() {
    int CIN = ui->IDEMP->text().toInt();
    QString NOM_E = ui->nameE->text();
    QString PRENOM_E = ui->prenomE->text();
    QString POST = ui->jobECombo->currentText();
    QString EMAIL = ui->mailE->text();
    int TELEPHONE = ui->phone_E->text().toInt();
    QString ADRESSE = ui->adresse_E->text();
    QString LEAVE_TYPE=""; // Example: if you have a combo box for leave type
    QDate FIRST_DAY_OF_LEAVE = QDate();        // Default (null) date
    QDate LAST_DAY_OF_LEAVE = QDate();         // Default (null) date
    int NBDAYS = 0; // Replace with actual value, e.g., the difference between dates

    // Create the Employe object
    Employe e(CIN, NOM_E, PRENOM_E, POST, EMAIL, TELEPHONE, ADRESSE, LEAVE_TYPE, FIRST_DAY_OF_LEAVE, LAST_DAY_OF_LEAVE, NBDAYS);

    // Call update instead of ajouter (since CIN already exists)
    bool test = e.Modifier();
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Successful"),
                                 QObject::tr("Employee details updated successfully.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                              QObject::tr("Update failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}






void MainWindow::on_deletelist_btn_6_clicked()
{
    Employe E1;E1.setCIN(ui->IDEMP->text().toInt());
    bool test=E1.supprimer(E1.getCIN());
    QMessageBox msgBox;
    if(test)
    {msgBox.setText("Suppression avec succes.");
    ui->list_emp->setModel(e.afficherEMP());
    ui->list_emp->setModel(e.afficherEMP());

    ui->IDEMP->clear();
    ui->nameE->clear();
    ui->prenomE->clear();

    ui->mailE->clear();
    ui->phone_E->clear();
    ui->adresse_E->clear();
    }

    else
        msgBox.setText("Echec de suppression");
        msgBox.exec();
}





void MainWindow::searchInListEmp(const QString &searchText)
{
    QAbstractItemModel *model = e.afficherEMP(); // Assuming e is an instance that provides the employee model

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    if (searchText.isEmpty()) {
        proxyModel->setFilterWildcard(QString()); // Clear filter if the search text is empty
    } else {
        if (isNumeric(searchText)) {
            proxyModel->setFilterFixedString(searchText); // Set filter for ID column
            proxyModel->setFilterKeyColumn(0); // Filter by ID column (0)
        } else {
            proxyModel->setFilterWildcard("*" + searchText + "*"); // Set wildcard filter for Name
            proxyModel->setFilterKeyColumn(1); // Filter by Name column (1)
        }
    }

    ui->list_emp->setModel(proxyModel); // Set the filtered model to the table view
}

bool MainWindow::isNumeric(const QString &searchText) {
    for (const QChar &c : searchText) {
        if (!c.isDigit()) {
            return false; // Return false if any character is not a digit
        }
    }
    return true; // Return true if all characters are digits
}


void MainWindow::searchInListEmployee2(const QString &searchText)
{
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
proxyModel->setSourceModel(ui->list_employee->model());
    proxyModel->setFilterKeyColumn(0);
    proxyModel->setFilterFixedString((searchText));

    ui->list_employee->setModel(proxyModel);
}


void MainWindow::on_Sort_btn_clicked()
{
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(ui->list_emp->model()); // Définir le modèle source


        int nameColumn = 1;
        proxyModel->setSortRole(Qt::DisplayRole);
        proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
        proxyModel->sort(nameColumn, Qt::AscendingOrder);


        ui->list_emp->setModel(proxyModel);
}




void MainWindow::on_refrech_clicked()
{
    ui->list_emp->setModel(e.afficherEMP());;
}
void MainWindow::on_refrech_4_clicked()
{
    ui->list_employee->setModel(e.afficherEMP());;
}

//*****buttons yhezouk
//emp
void MainWindow::on_employee_pushButton2_clicked()
{
    ui->Home->setCurrentIndex(1);
}

void MainWindow::on_employee_pushButton_clicked()
{
    ui->Home->setCurrentIndex(1);
}

void MainWindow::on_employee_pushButton_3_clicked()
{
    ui->Home->setCurrentIndex(2);
}

void MainWindow::on_employee_pushButton_4_clicked()
{
    ui->Home->setCurrentIndex(2);
}

void MainWindow::on_employee_pushButton_5_clicked()
{
    ui->Home->setCurrentIndex(2);
}


//view emp
void MainWindow::on_viewListe_clicked()
{
    ui->Home->setCurrentIndex(3);
}

//add emp
void MainWindow::on_AddList_btn_clicked()
{
    ui->Home->setCurrentIndex(4);
}
//update emp
void MainWindow::on_Uapdatelist_btn_clicked()
{
    ui->Home->setCurrentIndex(4);
}

//delete
void MainWindow::on_deletelist_btn_3_clicked()
{
    ui->Home->setCurrentIndex(5);
}

void MainWindow::on_deletelist_btn_clicked()
{
    ui->Home->setCurrentIndex(5);
}


//home
void MainWindow::on_home_pushButton_2_clicked()
{
    ui->Home->setCurrentIndex(0);
}

void MainWindow::on_home_pushButton_3_clicked()
{
    ui->Home->setCurrentIndex(0);
}
void MainWindow::on_home_pushButton_4_clicked()
{
    ui->Home->setCurrentIndex(1);
}

void MainWindow::on_home_pushButton_5_clicked()
{
    ui->Home->setCurrentIndex(1);
}

//logout
void MainWindow::on_log_pushButton_2_clicked()
{
    ui->Home->setCurrentIndex(0);
}

void MainWindow::on_log_pushButton_clicked()
{
    ui->Home->setCurrentIndex(0);
}

void MainWindow::on_log_pushButton_3_clicked()
{
    ui->Home->setCurrentIndex(0);
}

void MainWindow::on_log_pushButton_4_clicked()
{
    ui->Home->setCurrentIndex(0);
}

void MainWindow::on_log_pushButton_5_clicked()
{
    ui->Home->setCurrentIndex(0);
}
void MainWindow::on_log_pushButton_8_clicked()
{
    ui->Home->setCurrentIndex(0);
}

void MainWindow::on_log_pushButton_9_clicked()
{
    ui->Home->setCurrentIndex(0);
}

void MainWindow::on_log_pushButton_10_clicked()
{
    ui->Home->setCurrentIndex(0);
}


void MainWindow::on_log_pushButton_11_clicked()
{
    ui->Home->setCurrentIndex(0);
}






























//login
void MainWindow::on_pushButton_Login_clicked()
{
    QString email = ui->mailLogin->text();
    QString cin = ui->PwLogin->text();
    Connection conn;

    if (conn.createconnect()) { // Call the static method to create the connection
        QSqlQuery query;
        query.prepare("SELECT * FROM EMPLOYEE WHERE EMAIL = :email AND CIN = :cin");
        query.bindValue(":email", email);
        query.bindValue(":cin", cin);

        if (query.exec() && query.next()) {
            isAuthenticated = true; // Set authentication flag

            // Retrieve employee's first and last name
            QString firstName = query.value("NOM_E").toString();
            QString lastName = query.value("PRENOM_E").toString();
            QString fullName = firstName + " " + lastName;

            // Display the full name on the UI (assuming you have a QLabel for this)
            ui->welcomeLabel->setText("Welcome, " + fullName);
            ui->welcomeLabel_2->setText("Welcome, " + fullName);
            ui->welcomeLabel_3->setText("Welcome, " + fullName);
            ui->welcomeLabel_4->setText("Welcome, " + fullName);

            ui->Home->setCurrentIndex(0); // Navigate to the home page
            ui->login->hide();
            ui->lesgestion->show();
        } else {
            QMessageBox::warning(this, "Login Failed", "Invalid email or CIN. Please try again.");
        }
    } else {
        QMessageBox::critical(this, "Database Error", "Could not connect to the database.");
    }
}


void MainWindow::on_tabBarClicked(int index)
{
    if (!isAuthenticated && index != 0) { // Block navigation to other tabs
            QMessageBox::warning(this, "Access Denied", "You must log in to access this page.");
            ui->Home->setCurrentIndex(0); // Redirect back to the login page
        }
}





//Cong



void MainWindow::on_refrech_Con_clicked()
{

        ui->list_cong->setModel(e.afficherCONG());;

}

void MainWindow::on_deletelist_btn_7_clicked()
{
    Employe E1;
    E1.setCIN(ui->IDEMP_4->text().toInt());
    bool test = E1.supprimerCONG(E1.getCIN()); // Call supprimerCONG
    QMessageBox msgBox;
    if (test) {
        msgBox.setText("Suppression des congés avec succès.");
        ui->list_cong->setModel(e.afficherCONG());
        ui->IDEMP_4->clear();
        ui->nameE_3->clear();
        ui->prenomE_3->clear();
        ui->startDateEdit->clear();
        ui->endDateEdit->clear();
        ui->nbdays->clear();
    } else {
        msgBox.setText("Échec de suppression des congés.");
    }
    msgBox.exec();
}



void MainWindow::on_Uapdatelist_btn_4_clicked()
{
    // Retrieve the CIN of the employee to update
    int CIN = ui->IDEMP_4->text().toInt();
    if (CIN == 0) {
        QMessageBox::warning(this, "Error", "Invalid CIN provided.");
        return;
    }

    // Determine the leave type from radio buttons
    QString LEAVE_TYPE;
    if (ui->radioButton_6->isChecked()) { // Vacation
        LEAVE_TYPE = "Vacation";
    } else if (ui->radioButton_7->isChecked()) { // Sick-Self
        LEAVE_TYPE = "Sick-Self";
    } else if (ui->radioButton_5->isChecked()) { // Maternity Leave
        LEAVE_TYPE = "Maternity Leave";
    } else if (ui->radioButton_8->isChecked()) { // Sick-Family
        LEAVE_TYPE = "Sick-Family";
    } else {
        QMessageBox::warning(this, "Error", "Please select a leave type.");
        return;
    }

    // Get the leave dates from the user
    QDate FIRST_DAY_OF_LEAVE = ui->startDateEdit->date();
    QDate LAST_DAY_OF_LEAVE = ui->endDateEdit->date();

    // Validate the dates
    if (FIRST_DAY_OF_LEAVE.isNull() || LAST_DAY_OF_LEAVE.isNull()) {
        QMessageBox::warning(this, "Error", "Please provide valid leave dates.");
        return;
    }

    if (FIRST_DAY_OF_LEAVE > LAST_DAY_OF_LEAVE) {
        QMessageBox::warning(this, "Error", "The first day of leave cannot be after the last day.");
        return;
    }

    // Calculate the number of leave days
    int NBDAYS = FIRST_DAY_OF_LEAVE.daysTo(LAST_DAY_OF_LEAVE); // Include the first day in the count

    // Directly update leave details in the database
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEE SET LEAVE_TYPE = :LEAVE_TYPE, FIRST_DAY_OF_LEAVE = :FIRST_DAY_OF_LEAVE, "
                  "LAST_DAY_OF_LEAVE = :LAST_DAY_OF_LEAVE, NBDAYS = :NBDAYS WHERE CIN = :CIN");

    query.bindValue(":LEAVE_TYPE", LEAVE_TYPE);
    query.bindValue(":FIRST_DAY_OF_LEAVE", FIRST_DAY_OF_LEAVE);
    query.bindValue(":LAST_DAY_OF_LEAVE", LAST_DAY_OF_LEAVE);
    query.bindValue(":NBDAYS", NBDAYS);
    query.bindValue(":CIN", CIN);

    // Execute the query and handle results
    if (query.exec()) {
        QMessageBox::information(nullptr, QObject::tr("Successful"),
                                 QObject::tr("Leave details updated successfully.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                              QObject::tr("Update failed: %1").arg(query.lastError().text()),
                              QMessageBox::Cancel);
    }
}


















void MainWindow::on_Exportlist_btn_2_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->list_cong->model()->rowCount();
    const int columnCount = ui->list_cong->model()->columnCount();

    QString currentDate = QDate::currentDate().toString("dd/MM/yyyy");

    // Path to the logo
    QString logoPath = "C:/fac/2eme2/QT/Atelier_Connexion/img/logo.png";
    if (!QFile::exists(logoPath)) {
        QMessageBox::warning(this, "Error", "Logo file not found at " + logoPath);
        return;
    }

    // HTML content with the new layout
    out << "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << QString("<title>%1</title>\n").arg("Employee Leave List")
        << "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<div style='display: flex; justify-content: space-between; align-items: center; padding: 10px 20px;'>"
        "<img src='" + logoPath + "' alt='Company Logo' height='100' style='flex-shrink: 0;'/>"
        // Reduced margin-top to bring the date higher
        "<h2 style='text-align: right; margin: -5px 0 0 0; flex-grow: 1;'>Date: " + currentDate + "</h2>\n"
        "</div>\n"
        "<center><H1 style='color:#000c5e; margin-top: 20px;'>Leave List</H1></center>\n";

    // Add table styling and content
    out << "<style>"
           "table { border-collapse: collapse; width: 100%; margin-top: 30px; }"
           "th, td { border: 1px solid #ddd; padding: 8px; text-align: center; }"
           "th { background-color: #f2f2f2; color: #333; }"
           "tr:nth-child(even) { background-color: #f9f9f9; }"
           "tr:hover { background-color: #f1f1f1; }"
           "</style>";

    out << "<table>\n";

    out << "<thead><tr>";
    out << "<th>Numéro</th>";
    for (int column = 0; column < columnCount; column++) {
        if (!ui->list_cong->isColumnHidden(column)) {
            out << QString("<th>%1</th>").arg(ui->list_cong->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    out << "<tbody>\n";
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        out << "<td>" << row + 1 << "</td>";  // Row number
        for (int column = 0; column < columnCount; column++) {
            if (!ui->list_cong->isColumnHidden(column)) {
                QString data = ui->list_cong->model()->data(ui->list_cong->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out << "</tbody></table>\n";

    out << "</body>\n</html>\n";

    QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);

    doc.print(&printer);

    QMessageBox::information(this, "Export Successful", "PDF file has been successfully created.");
}













void MainWindow::on_stat_clicked()
{
    Employe employe;  // Objet de la classe Clients
        employe.stat_bateau();
    }


void MainWindow::on_Exportlist_btn_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->list_emp->model()->rowCount();
    const int columnCount = ui->list_emp->model()->columnCount();

    QString currentDate = QDate::currentDate().toString("dd/MM/yyyy");

    // Path to the logo
    QString logoPath = "C:/fac/2eme2/QT/Atelier_Connexion/img/logo.png";
    if (!QFile::exists(logoPath)) {
        QMessageBox::warning(this, "Error", "Logo file not found at " + logoPath);
        return;
    }

    // HTML content with the new layout
    out << "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << QString("<title>%1</title>\n").arg("Employee Leave List")
        << "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<div style='display: flex; justify-content: space-between; align-items: center; padding: 10px 20px;'>"
        "<img src='" + logoPath + "' alt='Company Logo' height='100' style='flex-shrink: 0;'/>"
        // Reduced margin-top to bring the date higher
        "<h2 style='text-align: right; margin: -5px 0 0 0; flex-grow: 1;'>Date: " + currentDate + "</h2>\n"
        "</div>\n"
        "<center><H1 style='color:#000c5e; margin-top: 20px;'>Employee List</H1></center>\n";

    // Add table styling and content
    out << "<style>"
           "table { border-collapse: collapse; width: 100%; margin-top: 30px; }"
           "th, td { border: 1px solid #ddd; padding: 8px; text-align: center; }"
           "th { background-color: #f2f2f2; color: #333; }"
           "tr:nth-child(even) { background-color: #f9f9f9; }"
           "tr:hover { background-color: #f1f1f1; }"
           "</style>";

    out << "<table>\n";

    out << "<thead><tr>";
    out << "<th>Numéro</th>";
    for (int column = 0; column < columnCount; column++) {
        if (!ui->list_emp->isColumnHidden(column)) {
            out << QString("<th>%1</th>").arg(ui->list_emp->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    out << "<tbody>\n";
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        out << "<td>" << row + 1 << "</td>";  // Row number
        for (int column = 0; column < columnCount; column++) {
            if (!ui->list_emp->isColumnHidden(column)) {
                QString data = ui->list_emp->model()->data(ui->list_emp->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out << "</tbody></table>\n";

    out << "</body>\n</html>\n";

    QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);

    doc.print(&printer);

    QMessageBox::information(this, "Export Successful", "PDF file has been successfully created.");}





void MainWindow::goToPreviousPage() {
    int currentIndex = ui->Home->currentIndex();
    int previousIndex = currentIndex - 1;

    // If the current page is not the first page, navigate to the previous page
    if (previousIndex >= 0) {
        ui->Home->setCurrentIndex(previousIndex);
    }
}



void MainWindow::searchInListCong(const QString &searchText)
{
    QAbstractItemModel *model = e.afficherCONG(); // Assuming e is an instance that provides the employee model

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    if (searchText.isEmpty()) {
        proxyModel->setFilterWildcard(QString()); // Clear filter if the search text is empty
    } else {
        if (isNumeric(searchText)) {
            proxyModel->setFilterFixedString(searchText); // Set filter for ID column
            proxyModel->setFilterKeyColumn(0); // Filter by ID column (0)
        } else {
            proxyModel->setFilterWildcard("*" + searchText + "*"); // Set wildcard filter for Name
            proxyModel->setFilterKeyColumn(1); // Filter by Name column (1)
        }
    }

    ui->list_cong->setModel(proxyModel); // Set the filtered model to the table view
}




void MainWindow::searchInListCong2(const QString &searchText)
{
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
proxyModel->setSourceModel(ui->list_cong2->model());
    proxyModel->setFilterKeyColumn(0);
    proxyModel->setFilterFixedString((searchText));

    ui->list_cong2->setModel(proxyModel);
}


void MainWindow::on_Sort_btn_2_clicked()
{
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(ui->list_cong->model()); // Définir le modèle source


        int nameColumn = 1;
        proxyModel->setSortRole(Qt::DisplayRole);
        proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
        proxyModel->sort(nameColumn, Qt::AscendingOrder);


        ui->list_cong->setModel(proxyModel);
}


void MainWindow::on_refrech_conggg_clicked()
{
    ui->list_cong2->setModel(e.afficherCONG());
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->Home->setCurrentIndex(0);
}


void MainWindow::on_pushButton_12_clicked()
{
    ui->Home->setCurrentIndex(1);
}


void MainWindow::on_pushButton_14_clicked()
{
    ui->Home->setCurrentIndex(1);
}


void MainWindow::on_viewCong_clicked()
{
    ui->Home->setCurrentIndex(4);
}


void MainWindow::on_home_pushButton_6_clicked()
{
    ui->Home->setCurrentIndex(0);
}


void MainWindow::on_employee_pushButton_6_clicked()
{
    ui->Home->setCurrentIndex(2);
}


void MainWindow::on_employee_pushButton_2_clicked()
{
    ui->Home->setCurrentIndex(2);
}










void MainWindow::on_ajouter_client_2_clicked()
{
    // Récupération des informations saisies dans les champs
    int id = ui->id_client_2->text().toInt(); // Convertir la chaîne saisie en un entier car l'attribut id est de type int
    QString nom = ui->nom_client_2->text();
    QString prenom = ui->prenom_client_2->text();
    QString email = ui->email_client_2->text();
    int telephone = ui->telephone_client_2->text().toInt();
    QString adresse = ui->adresse_client_2->text();
     int prix = ui->prix_client_2->text().toInt();
      int totalAchats = ui->totalAchats_client_2->text().toInt();

    // Instancier un objet de la classe Client en utilisant les informations saisies dans l'interface
    Client  client(id, nom, prenom, email, telephone, adresse, prix,totalAchats);

    // Insérer l'objet Client dans la table client et récupérer la valeur de retour de query.exec()
    bool test = client.ajouter();

    // Si requête exécutée => QMessageBox::information
    if (test)
    {
       ui->affichage_2->setModel(client.afficher()) ;

        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Cliquez sur Annuler pour quitter."),
                                 QMessageBox::Cancel);
    }

    else
    {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Cliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
}

void MainWindow::on_modifier_2_clicked()
{
    int id = ui->id_client_2->text().toInt();
    QString nom = ui->nom_client_2->text();
    QString prenom = ui->prenom_client_2->text();
    QString email = ui->email_client_2->text();
    int telephone = ui->telephone_client_2->text().toInt();
    QString adresse = ui->adresse_client_2->text();
    int prix = ui->prix_client_2->text().toInt();
    int totalAchats = ui->totalAchats_client_2->text().toInt();

    // Log input values for debugging
    qDebug() << "Attempting modification with ID:" << id;
    qDebug() << "New values - Nom:" << nom << ", Prenom:" << prenom
             << ", Email:" << email << ", Telephone:" << telephone
             << ", Adresse:" << adresse << ", Prix:" << prix << ", totalAchats:" <<totalAchats;

    // Create a Client object with the updated information
    Client client(id, nom, prenom, email, telephone, adresse,prix,totalAchats);

    // Attempt to modify the client record and log the result
    bool test = client.modifier(id);
    qDebug() << "Modifier function result:" << test;

    // Display message based on the success of the modification
    if (test) {
        // Refresh the table view to reflect changes
        ui->affichage_2->setModel(client.afficher());
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée\nCliquez sur Cancel pour quitter."),
                                 QMessageBox::Cancel);
    }
    /*else {
       QMessageBox::critical(this, QObject::tr("Erreur"),
                           QObject::tr("La modification n'a pas pu être effectuée.\nCliquez sur Cancel pour quitter."),
                           QMessageBox::Cancel);
    }*/
}

void MainWindow::on_supprimer_2_clicked()
{
    // Convertit la chaîne de texte saisie dans le champ id_supp en un entier
    int id = ui->id_client_2->text().toInt();

    // Création d'un objet Client pour supprimer le client d'ID spécifié
    Client client1;
    client1.setId(id);

    // Appel de la méthode supprimer() de l'objet Client
    bool test = client1.supprimer(client1.getId());

    // Affichage d'un message en fonction du résultat de la suppression
    if (test) {
        // Actualiser le modèle uniquement si la suppression a réussi
        ui->affichage_2->setModel(client1.afficher());
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\n"
                                             "Cliquez sur Annuler pour quitter."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée. Assurez-vous que l'ID existe.\n"
                                          "Cliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
}
#include <QVector>
#include <QDate>
#include <QString>
#include <QMessageBox>
void MainWindow::on_pdf_2_clicked()
{
    // Dialog box for the user to choose the save location
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer sous", "", "Fichiers CSV (*.csv)");

    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun emplacement sélectionné pour l'exportation.");
        return;
    }

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        // Write column headers
        out << "\"id\",\"Nom\",\"Prenom\",\"Email\",\"Telephone\"\n";

        // Prepare the query to retrieve all clients
        QSqlQuery query;
        query.prepare("SELECT ID, NOM, PRENOM, EMAIL, TELEPHONE FROM clients");

        // Execute the query and write each result row to the CSV file
        if (query.exec()) {
            while (query.next()) {
                int id = query.value("ID").toInt();
                QString nom = query.value("NOM").toString();
                QString prenom = query.value("PRENOM").toString();
                QString email = query.value("EMAIL").toString();
                int telephone = query.value("TELEPHONE").toInt();

                out << "\"" << id << "\","
                    << "\"" << nom << "\","
                    << "\"" << prenom << "\","
                    << "\"" << email << "\","
                    << "\"" << telephone << "\"\n";
            }
            QMessageBox::information(this, "Exportation réussie", "Les données ont été exportées avec succès en CSV.");
        } else {
            QMessageBox::warning(this, "Erreur", "Échec de la récupération des données client.");
        }

        file.close();
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier pour l'écriture.");
    }
}

void MainWindow::on_statistique_2_clicked()
{

    if (ui->statistique_2->layout() == nullptr) {
        QVBoxLayout *layout = new QVBoxLayout(ui->statistique_2);
        ui->statistique_2->setLayout(layout);
    }

    QLayout *layout = ui->statistique_2->layout();
    if (layout != nullptr) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }

    int thresholdAmount = 1000;
    int countAboveThreshold = 500;
    int countBelowThreshold =200;

    // Use the globally defined struct and purchases vector
 /*   for (const Purchase &purchase : purchases) {
        if (purchase.totalAchat >= thresholdAmount) {
            countAboveThreshold++;
        } else {
            countBelowThreshold++;
        }
    }*/

    int totalClients = countAboveThreshold + countBelowThreshold;
    if (totalClients == 10) {
        QLabel *noDataLabel = new QLabel("Aucune donnée disponible");
        noDataLabel->setAlignment(Qt::AlignCenter);
        noDataLabel->setStyleSheet("font-size: 18px; font-family: 'Arial'; color: #FF6F61;");
        layout->addWidget(noDataLabel);
        return;
    }

    float percentAboveThreshold = (countAboveThreshold * 500.0f) / totalClients;
    float percentBelowThreshold = (countBelowThreshold * 100.0f) / totalClients;
    #include <QtCharts/QBarSet>
    QBarSet *set0 = new QBarSet("prix ≥ 500");
    QBarSet *set1 = new QBarSet("prix = 200");
    *set0 << percentAboveThreshold;
    *set1 << percentBelowThreshold;

    QHorizontalBarSeries *series = new QHorizontalBarSeries();
    series->append(set0);
    series->append(set1);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des clients par montant d'achat (en pourcentage)");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 100);
    axisX->setLabelFormat("%.0f%%");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background-color: #2C3E50; border: 1px solid #DDDDDD;");

    QLabel *statisticLabel = new QLabel("Statistiques des achats");
    statisticLabel->setAlignment(Qt::AlignCenter);
    statisticLabel->setStyleSheet("font-size: 30px; font-family: 'Arial'; color: #FFFFFF; font-weight: bold;");

    layout->addWidget(statisticLabel);
    layout->addWidget(chartView);
}

void MainWindow::on_cardfidelite_2_clicked()
{
    // Obtenir la valeur de "prix" depuis l'interface utilisateur
    int prix = ui->prix_2->text().toInt();

    // Obtenir le nom du client depuis l'interface utilisateur
    QString clientName = ui->nomClient_2->text(); // Récupère le texte de QLineEdit "nomClient"

    if (clientName.isEmpty())
    {
        // Si le champ de nom est vide, afficher une erreur et arrêter
        QMessageBox::warning(this, "Erreur", "Veuillez saisir le nom du client.");
        return;
    }

    if (prix > 500)
    {
        // Générer un identifiant unique pour la carte
        QString cardNumber = QUuid::createUuid().toString(QUuid::WithoutBraces).toUpper();

        // Générer la date et l'heure actuelles
        QDateTime currentDateTime = QDateTime::currentDateTime();

        // Ajouter un an à la date actuelle avec l'heure incluse
        QDateTime validUntilDateTime = currentDateTime.addYears(0);

        // Formater la date et l'heure
        QString validUntil = validUntilDateTime.toString("dd/MM/yyyy hh:mm:ss"); // Ajoute l'heure dans le format

        // Construire le message
        QString message = QString(
            "Félicitations ! Vous avez obtenu une carte de fidélité.\n\n"
            "**Détails de votre carte** :\n"
            "----------------------------------------\n"
            "Numéro de carte : %1\n"
            "Nom du client : %2\n"
            "Date de validité : %3\n"
            "----------------------------------------\n"
            "**Merci pour votre fidélité** !"
        ).arg(cardNumber).arg(clientName).arg(validUntil);

        // Afficher le message
        QMessageBox::information(this, "Fidélité", message);
    }
    else
    {
        // Message si le client n'est pas éligible
        QMessageBox::information(this, "Fidélité", "Client non fidèle. Le montant minimum pour obtenir une carte est de 500.");
    }
}

void MainWindow::on_total_Achats_2_clicked()
{

    // Structure for mock purchase data
    struct Purchase {
        QString id;            // Client name
        QDate purchasesDate;   // Date of the purchase
        int totalAchat;        // Total purchase amount
    };

    // Mock data (replace with actual database or source)
    QVector<Purchase> purchases = {
        {"maram", QDate(2024, 11, 1), 100},
        {"ameni", QDate(2024, 11, 5), 50},
        {"rami", QDate(2024, 11, 7), 200},
        {"maram", QDate(2024, 10, 15), 70},
        {"ameni", QDate(2024, 11, 12), 300},
        {"maram", QDate(2024, 11, 18), 400},
        {"maram", QDate(2024, 11, 21), 1},
        {"rami", QDate(2024, 11, 2), 150},
        {"ameni", QDate(2024, 11, 10), 500},};
// Get the client name dynamically from the input field in the UI
    QString id = ui->clientNameLineEdit_2->text(); // Fetch input from the text field

    if (id.isEmpty())
    {
        // Warn the user if no name is entered
        QMessageBox::warning(this, "Erreur", "Veuillez saisir le nom du client.");
        return;
    }

    // Get the current date
    QDate currentDate = QDate::currentDate();
    int currentMonth = currentDate.month();
    int currentYear = currentDate.year();

    // Filter purchases for the entered client and current month
    int purchaseCount = 0;
    int totalSpent = 0;
    for (const Purchase &purchase : purchases)
    {
        if (purchase.id == id &&
            purchase.purchasesDate.month() == currentMonth &&
            purchase.purchasesDate.year() == currentYear)
        {
            purchaseCount++;
            totalSpent += purchase.totalAchat;
        }
    }

    // Determine the reward level based on the purchase count
    QString rewardMessage;
    if (purchaseCount > 1)  // Platinum level reward
    {
        rewardMessage = "Félicitations ! Vous avez reçu un cadeau de niveau *Platine*.";
    }
    else if (purchaseCount > 1)  // Gold level reward
    {
        rewardMessage = "Félicitations ! Vous avez reçu un cadeau de niveau *Or*.";
    }
    else if (purchaseCount > 0)  // Silver level reward
    {
        rewardMessage = "Félicitations ! Vous avez reçu un cadeau de niveau *Argent*.";
    }
    else
    {
        rewardMessage = "Vous n'avez pas atteint le nombre minimum d'achats pour recevoir un cadeau.";
    }

    // Display the result in a message box
    QString message = QString(
        "----------------------------------------\n"
        "Client : %1\n"
        "Achats ce mois : %2\n"
        "Total des achats : %3\n"
        "%4\n"
        "----------------------------------------\n"
    ).arg(id).arg(purchaseCount).arg(totalSpent).arg(rewardMessage);

    QMessageBox::information(this, "**Notification cadeau Client**", message);
}

void MainWindow::on_customer_pushButton2_clicked()
{
    ui->Home->setCurrentIndex(4);
}

void MainWindow::on_customer_pushButton_8_clicked()
{
    ui->Home->setCurrentIndex(4);
}


void MainWindow::on_customer_pushButton_9_clicked()
{
    ui->Home->setCurrentIndex(4);
}


void MainWindow::on_customer_pushButton_10_clicked()
{
    ui->Home->setCurrentIndex(4);
}


void MainWindow::on_customer_pushButton_11_clicked()
{
    ui->Home->setCurrentIndex(4);
}


void MainWindow::on_rechercher_clicked()
{
    QString GA_searchParam = ui->comboBox_rech_2->currentText(); // Get the selected search parameter
       QString GA_searchText = ui->id_rech->text(); // Get the text to search

       QSqlQueryModel *searchResultModel = new QSqlQueryModel();

       if (GA_searchParam == "nom") {
           searchResultModel->setQuery(QString("SELECT * FROM CLIENTS WHERE nom = '%1'").arg(GA_searchText));
       } else if (GA_searchParam == "id") {
           bool isNumeric;
           int searchID = GA_searchText.toInt(&isNumeric);

           if (isNumeric) {
               searchResultModel->setQuery(QString("SELECT * FROM CLIENTS WHERE id = %1").arg(searchID));
           } else {
               // Handle non-numeric input for ID (optional)
               // Show an error message or take appropriate action
           }
       } else if (GA_searchParam == "telephone") {
           bool isNumeric;
           int searchPoids = GA_searchText.toInt(&isNumeric);

           if (isNumeric) {
               searchResultModel->setQuery(QString("SELECT * FROM CLIENTS WHERE telephone = %1").arg(searchPoids));
           } else {
               // Handle non-numeric input for poids (optional)
               // Show an error message or take appropriate action
           }
       }

       ui->affichage_2->setModel(searchResultModel);
}


void MainWindow::on_refrech_3_clicked()
{

    ui->affichage_2->setModel(c.afficher());
    ui->Home->setCurrentIndex(5);
}


void MainWindow::on_employee_pushButton_8_clicked()
{
    ui->Home->setCurrentIndex(1);
}


void MainWindow::on_employee_pushButton_7_clicked()
{
    ui->Home->setCurrentIndex(1);
}


void MainWindow::on_home_pushButton_7_clicked()
{
    ui->Home->setCurrentIndex(0);
}


void MainWindow::on_home_pushButton_8_clicked()
{
    ui->Home->setCurrentIndex(0);
}


void MainWindow::on_pushButton_17_clicked()
{
    ui->Home->setCurrentIndex(0);
}


void MainWindow::on_pushButton_16_clicked()
{
    ui->Home->setCurrentIndex(4);
}


void MainWindow::on_view_2_clicked()
{
    ui->Home->setCurrentIndex(5);
}


void MainWindow::on_refrech_conggg_3_clicked()
{
    ui->affichage_3->setModel(c.afficher());
}


void MainWindow::on_rechercher_2_clicked()
{
    QString GA_searchParam = ui->comboBox_rech_3->currentText(); // Get the selected search parameter
       QString GA_searchText = ui->seach_cong2_3->text(); // Get the text to search

       QSqlQueryModel *searchResultModel = new QSqlQueryModel();

       if (GA_searchParam == "nom") {
           searchResultModel->setQuery(QString("SELECT * FROM CLIENTS WHERE nom = '%1'").arg(GA_searchText));
       } else if (GA_searchParam == "id") {
           bool isNumeric;
           int searchID = GA_searchText.toInt(&isNumeric);

           if (isNumeric) {
               searchResultModel->setQuery(QString("SELECT * FROM CLIENTS WHERE id = %1").arg(searchID));
           } else {
               // Handle non-numeric input for ID (optional)
               // Show an error message or take appropriate action
           }
       } else if (GA_searchParam == "telephone") {
           bool isNumeric;
           int searchPoids = GA_searchText.toInt(&isNumeric);

           if (isNumeric) {
               searchResultModel->setQuery(QString("SELECT * FROM CLIENTS WHERE telephone = %1").arg(searchPoids));
           } else {
               // Handle non-numeric input for poids (optional)
               // Show an error message or take appropriate action
           }
       }

       ui->affichage_3->setModel(searchResultModel);
}


void MainWindow::on_boutonTri_clicked()
{

    QString critere = ui->comboBox->currentText(); // Récupère le critère sélectionné

    // Appeler la méthode de tri en fonction du critère
    afficherLivraisonsTriées(critere);
}

void MainWindow::on_boutonRechercher_clicked()
{
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

void MainWindow::on_supprimer_clicked()
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

void MainWindow::on_modifier_clicked()
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

void MainWindow::on_boutonExporterCSV_clicked()
{

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

void MainWindow::afficherLivraisonsTriées(const QString& critere) {
    ui->table_livraisons->setRowCount(0);

    QString orderBy;
    if (critere == "ID") {
        orderBy = "ID_LIVRAISON";
    } else if (critere == "Name") {
        orderBy = "NOM_LIVREUR";
    } else if (critere == "prevue date") {
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

void MainWindow::on_sendEmailButton_clicked()
{

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

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
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

void MainWindow::connectToArduino()
{
  /*  foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
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
}*/
}

void MainWindow::sendCommandToArduino(const QByteArray &command)
{
    if (serial->isOpen()) {
        serial->write(command);
        qDebug() << "Sent to Arduino:" << command;
    }
}

void MainWindow::on_pushButton_stats_clicked()
{

        // Initialisation des variables
        int totalLivraisons = 0;
        int effectuees = 0;
        int enRetard = 0;

        // Récupération des données depuis la base de données
        QSqlQuery query("SELECT DATE_PREVUE, DATE_EFFECTUEE FROM LIVRAISONS");
        while (query.next()) {
            QDate datePrevue = query.value("DATE_PREVUE").toDate();
            QDate dateEffectuee = query.value("DATE_EFFECTUEE").toDate();

            if (!dateEffectuee.isNull()) {
                totalLivraisons++;
                if (dateEffectuee <= datePrevue) {
                    effectuees++;
                } else {
                    enRetard++;
                }
            }
        }

        // Gestion du cas où il n'y a aucune donnée
        if (totalLivraisons == 0) {
            QMessageBox::information(this, "Statistiques", "Aucune livraison trouvée.");
            return;
        }

        // Création de la série pour le graphique en secteurs
        QPieSeries *series = new QPieSeries();
        series->append("Livraisons à temps", effectuees);
        series->append("Livraisons en retard", enRetard);

        // Personnalisation des sections du graphique
        QPieSlice *sliceEffectuees = series->slices().at(0);
        sliceEffectuees->setBrush(Qt::green);
        sliceEffectuees->setLabelVisible();

        QPieSlice *sliceRetard = series->slices().at(1);
        sliceRetard->setBrush(Qt::red);
        sliceRetard->setLabelVisible();

        // Création du graphique
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques des livraisons");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // Création de la vue pour afficher le graphique
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Création de la fenêtre des statistiques
        statsWindow = new QWidget();
        statsWindow->setWindowTitle("Statistiques des Livraisons");
        statsWindow->resize(600, 500);

        QVBoxLayout *layout = new QVBoxLayout(statsWindow);

        // Ajout du graphique au layout
        layout->addWidget(chartView);

        // Affichage des valeurs sous le graphique
        QString details = QString(
                              "Total des livraisons : %1\n"
                              "Livraisons effectuées à temps : %2\n"
                              "Livraisons en retard : %3")
                              .arg(totalLivraisons)
                              .arg(effectuees)
                              .arg(enRetard);

        QLabel *detailsLabel = new QLabel(details);
        detailsLabel->setAlignment(Qt::AlignCenter);
        detailsLabel->setStyleSheet("font-size: 14px; color: black;");
        layout->addWidget(detailsLabel);

        // Bouton pour fermer la fenêtre
        QPushButton *closeButton = new QPushButton("Fermer");
        closeButton->setStyleSheet("padding: 10px; font-size: 14px; color: white; background-color: #007BFF;");
        connect(closeButton, &QPushButton::clicked, statsWindow, &QWidget::close);
        layout->addWidget(closeButton);

        statsWindow->setLayout(layout);
        statsWindow->show();

}


void MainWindow::on_delivery_pushButton2_clicked()
{
    ui->Home->setCurrentIndex(6);
}


void MainWindow::on_delivery_pushButton_15_clicked()
{
    ui->Home->setCurrentIndex(6);

}


void MainWindow::on_delivery_pushButton_11_clicked()
{
    ui->Home->setCurrentIndex(6);

}


void MainWindow::on_delivery_pushButton_10_clicked()
{
    ui->Home->setCurrentIndex(6);

}


void MainWindow::on_delivery_pushButton_9_clicked()
{
    ui->Home->setCurrentIndex(6);

}


void MainWindow::on_pushButton_9_clicked()
{
    ui->Home->setCurrentIndex(0);

}


void MainWindow::on_pushButton_10_clicked()
{
    ui->Home->setCurrentIndex(1);

}


void MainWindow::on_pushButton_13_clicked()
{
    ui->Home->setCurrentIndex(5);

}


void MainWindow::on_stock_pushButton2_clicked()
{
    ui->Home->setCurrentIndex(7);

}


void MainWindow::on_statisticsBtn_clicked()
{
    // 1. Fetch data from the database
    QSqlQuery query;
    query.prepare("SELECT NOM_PRODUIT, QUANTITE_PRODUIT FROM stock");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les données.");
        return;
    }

    // 2. Create the pie series
    QPieSeries *series = new QPieSeries();
    while (query.next()) {
        QString productName = query.value(0).toString();
        int quantity = query.value(1).toInt();
        series->append(productName, quantity);
    }

    // 3. Customize each slice with unique colors
    int colorIndex = 0;
    QList<QColor> colors = {
        QColor("#FF5733"), QColor("#33FF57"), QColor("#3357FF"),
        QColor("#FF33A1"), QColor("#FFC733"), QColor("#33FFF2"), QColor("#B833FF")
    };

    for (QPieSlice *slice : series->slices()) {
        slice->setBrush(colors[colorIndex % colors.size()]);
        slice->setLabelColor(Qt::white);
        slice->setLabel(QString("%1: %2").arg(slice->label()).arg(slice->value()));
        colorIndex++;
    }

    // 4. Create the chart and set the series
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des quantités en stock");
    chart->legend()->setAlignment(Qt::AlignRight);

    // 5. Create a chart view and apply an animation on the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 6. Create a dialog to show the chart
    QDialog dialog(this);
    dialog.setWindowTitle("Statistiques");
    dialog.resize(600, 400);

    QVBoxLayout layout(&dialog);
    layout.addWidget(chartView);

    // Animation on chart view (Fade in effect)
    QPropertyAnimation *animation = new QPropertyAnimation(chartView, "windowOpacity");
    animation->setDuration(800);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    dialog.exec();
}

void MainWindow::on_stat_2_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT MARQUE_PRODUIT, SUM(QUANTITE_PRODUIT * PRIX_PRODUIT) AS PROFIT FROM STOCK GROUP BY MARQUE_PRODUIT");

    QPieSeries *series = new QPieSeries();
    if (query.exec()) {
        while (query.next()) {
            QString brand = query.value(0).toString();
            double profit = query.value(1).toDouble();
            series->append(brand, profit);
        }
    }

    // Apply colors to the slices
    int colorIndex = 0;
    QList<QColor> colors = {
        QColor("#FF5733"), QColor("#33FF57"), QColor("#3357FF"),
        QColor("#FF33A1"), QColor("#FFC733"), QColor("#33FFF2"), QColor("#B833FF")
    };
    for (QPieSlice *slice : series->slices()) {
        slice->setLabel(slice->label() + ": " + QString::number(slice->value(), 'f', 2));
        slice->setBrush(colors[colorIndex % colors.size()]);
        colorIndex++;
    }

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Profit par Marque");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Create a dialog to show the chart with animation
    QDialog dialog(this);
    dialog.setWindowTitle("Profit Chart");
    dialog.resize(640, 480);
    QVBoxLayout layout(&dialog);
    layout.addWidget(chartView);

    // Animation for the chart (Fade in effect)
    QPropertyAnimation *chartAnimation = new QPropertyAnimation(chartView, "windowOpacity");
    chartAnimation->setDuration(8000);
    chartAnimation->setStartValue(0.0);
    chartAnimation->setEndValue(1.0);
    chartAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    dialog.exec();
}


void MainWindow::on_rechercherBtn_clicked()
{
    // Récupérer la chaîne entrée dans le QLineEdit
    QString recherche = ui->lineEdit_recherche->text();

    // Rechercher dans le modèle Stock par nom de produit
    QSqlQueryModel *model = s.rechercherProduit(recherche);

    // Afficher les résultats dans le QTableView
    ui->tableView_2->setModel(model);
}


void MainWindow::on_viewCong_2_clicked()
{
    ui->tabWidget->setCurrentIndex(1);

}


void MainWindow::on_rechercherBtn_3_clicked()
{

    QString recherche = ui->lineEdit_recherche_3->text();


    QSqlQueryModel *model = s.rechercherProduit(recherche);


    ui->tableView->setModel(model);
}


void MainWindow::on_sortBtn_clicked()
{
    QString critere = "PRIX_PRODUIT";  // On trie par l'attribut 'PRIX'
    bool croissant = (ui->comboBox_2->currentText() == "ASC");  // Vérifie si l'option est 'Ascending Price'

    // Obtenir le modèle trié
    QSqlQueryModel* model = s.trierStock(critere, croissant);

    // Vérifier si le modèle contient des lignes après le tri
    if (model->rowCount() == 0) {
        qDebug() << "Aucune donnée trouvée après le tri.";
    }

    // Appliquer le modèle trié au QTableView
    ui->tableView->setModel(model);
}


void MainWindow::on_exportButton_6_clicked()
{

    // 1. Choose a location and file name for the PDF
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "*.pdf");
    if (filePath.isEmpty()) {
        return; // User canceled the dialog
    }

    // Add ".pdf" if the user did not specify it
    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath += ".pdf";
    }

    // 2. Create a QPdfWriter instance
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMargins(50, 50, 50, 50)); // Larger margins for better placement

    // 3. Set up QPainter for drawing on the PDF
    QPainter painter(&pdfWriter);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Export Failed", "Failed to initialize PDF writer.");
        return;
    }

    painter.setPen(Qt::black);

    // Optional: Add a title or header
    QFont titleFont("Arial", 8, QFont::Bold);
    painter.setFont(titleFont);

    // Optional: Add a timestamp
    QFont dateFont("Arial", 12);
    painter.setFont(dateFont);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    painter.drawText(100, 200, "Generated on: " + timestamp);

    // 4. Draw table headers and data
    QAbstractItemModel *model = ui->tableView->model();
    if (!model) {
        QMessageBox::warning(this, "Export Failed", "No data available in the table view.");
        painter.end();
        return;
    }

    // Set larger font for table headers and data
    QFont headerFont("Arial", 8, QFont::Bold);
    QFont dataFont("Arial", 8);
    int rowHeight = 200;     // Increase row height
    int colPadding = 200;    // Add extra padding to columns

    // Calculate column widths based on content length
    int xMargin = 100;      // Left margin for the table
    int yMargin = 300;      // Top margin for the table
    int colCount = model->columnCount();
    QVector<int> colWidths(colCount);

    painter.setFont(headerFont);
    for (int col = 0; col < colCount; ++col) {
        int maxWidth = painter.fontMetrics().horizontalAdvance(model->headerData(col, Qt::Horizontal).toString());
        painter.setFont(dataFont);
        for (int row = 0; row < model->rowCount(); ++row) {
            maxWidth = qMax(maxWidth, painter.fontMetrics().horizontalAdvance(model->data(model->index(row, col)).toString()));
        }
        colWidths[col] = maxWidth + colPadding; // Add padding
    }

    // Draw headers
    int xPos = xMargin;
    int yPos = yMargin;

    painter.setFont(headerFont);
    for (int col = 0; col < colCount; ++col) {
        QRect headerRect(xPos, yPos, colWidths[col], rowHeight);
        painter.drawRect(headerRect);
        painter.drawText(headerRect, Qt::AlignCenter, model->headerData(col, Qt::Horizontal).toString());
        xPos += colWidths[col];
    }

    yPos += rowHeight; // Move to the first row of data

    // Draw table data
    painter.setFont(dataFont);
    for (int row = 0; row < model->rowCount(); ++row) {
        xPos = xMargin;
        for (int col = 0; col < colCount; ++col) {
            QRect cellRect(xPos, yPos, colWidths[col], rowHeight);
            painter.drawRect(cellRect);
            painter.drawText(cellRect, Qt::AlignCenter, model->data(model->index(row, col)).toString());
            xPos += colWidths[col];
        }
        yPos += rowHeight; // Move to the next row
    }

    // 5. End the painting and save the PDF
    painter.end();

    // Optional: Confirm successful export
    QMessageBox::information(this, "Export Successful", "PDF file has been successfully created at:\n" + filePath);
}
#include <QInputDialog>

void MainWindow::on_btn_gestion_stocks_clicked()
{
    // Demander l'ID du produit à l'utilisateur
    bool ok;
    int idProduit = QInputDialog::getInt(this, "Entrée de l'ID du produit",
                                         "Veuillez entrer l'ID du produit :",
                                         0, 0, 1000000, 1, &ok);

    // Vérifier si l'utilisateur a validé l'entrée
    if (!ok) {
        return;  // Si l'utilisateur a annulé ou entré une valeur invalide, on arrête l'exécution
    }

    // Récupérer la quantité du produit sélectionné
    int quantite = s.getQuantite(idProduit);

    // Vérifier la quantité et afficher une alerte
    QMessageBox msgBox;

    // Debugging output to check the quantity
    qDebug() << "Produit ID:" << idProduit << "Quantité:" << quantite;

    if (quantite < 0) {
        msgBox.setWindowTitle("Erreur");
        msgBox.setText("Erreur lors de la récupération de la quantité du produit.");
        msgBox.exec();
        return; // Stop further execution if there's an error
    }

    if (quantite <= 300) {
        msgBox.setWindowTitle("Alerte de réapprovisionnement");
        msgBox.setText("La quantité de ce produit est faible. Réapprovisionnement nécessaire.");
        msgBox.setStyleSheet(
            "QMessageBox { background-color: #ffcccc; }"
            "QLabel { color: #000000; font-size: 14px; }"
            "QPushButton { background-color: #ff0000; color: white; border: none; padding: 5px; }"
            );
    } else {
        msgBox.setWindowTitle("Stock suffisant");
        msgBox.setText("Le stock de ce produit est suffisant.");
    }

    // Show the message box
    msgBox.exec();
}

void MainWindow::on_Historic_2_clicked()
{
    ui->tabWidget->setCurrentIndex(2);

}


void MainWindow::on_AjoutStockBtn_clicked()
{

    QString nom = ui->lineEdit_nom->text();
    int id = ui->line->text().toInt();
    double prix = ui->lineEdit_Prix->text().toDouble();
    int qt = ui->lineEdit_Quantite->text().toInt();
    QString marque = ui->lineEdit_Marque->text();
    int idF = ui->comboBox->currentText().toInt();
    int idL = ui->comboBox_2->currentText().toInt();

    Stock s(id, nom, qt, prix, marque, idF, idL);

    bool test = s.ajouter();
    if (test) {
        ui->tableView->setModel(s.afficher());
        QMessageBox::information(nullptr, QObject::tr("Ajout"),
                                 QObject::tr("Ajout effectué avec succès.\n"
                                             "Cliquez sur Annuler pour sortir."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur d'ajout"),
                              QObject::tr("Échec de l'ajout. Vérifiez les données et réessayez."));
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView->model()->data(in).toString();
    idmod = ui->tableView->model()->data(in).toInt();

    ui->line->setText(ui->tableView->model()->data(index.sibling(i,0)).toString());
    ui->lineEdit_nom->setText(ui->tableView->model()->data(index.sibling(i,1)).toString());
    ui->lineEdit_Prix->setText(ui->tableView->model()->data(index.sibling(i,3)).toString());
    ui->lineEdit_Quantite->setText(ui->tableView->model()->data(index.sibling(i,2)).toString());
    ui->lineEdit_Marque->setText(ui->tableView->model()->data(index.sibling(i,4)).toString());
    ui->comboBox->setCurrentText(ui->tableView->model()->data(index.sibling(i,5)).toString());
    ui->comboBox_2->setCurrentText(ui->tableView->model()->data(index.sibling(i,6)).toString());

}


void MainWindow::on_pushButton_27_clicked()
{
    int i;
    QModelIndex index=ui->tableView->currentIndex();
    i=index.row();
    QModelIndex in=index.sibling(i,0);

    int val=ui->tableView->model()->data(in).toInt();
    bool test=s.supprimer(val);
    if (test)
    {
        ui->tableView->setModel(s.afficher());

    }else{

        QMessageBox::critical(nullptr, QObject::tr("Delete"),
                              QObject::tr(" failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    }
}


void MainWindow::on_modifierStockBtn_clicked()
{
    // Vérifiez si une ligne est sélectionnée
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, QObject::tr("Erreur"),
                             QObject::tr("Il faut sélectionner une ligne.\n"
                                         "Click Cancel to exist."),
                             QMessageBox::Cancel);
        return; // Arrêtez l'exécution si aucune ligne n'est sélectionnée
    }

    // Récupérez les données des champs de saisie
    int idmod = ui->line->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    double prix = ui->lineEdit_Prix->text().toDouble();
    int qt = ui->lineEdit_Quantite->text().toInt();
    QString marque = ui->lineEdit_Marque->text();
    int idF = ui->comboBox->currentText().toInt();
    int idL = ui->comboBox_2->currentText().toInt();

    // Créez l'objet Stock
    Stock m(idmod, nom, qt, prix, marque, idF, idL);

    // Tentez de modifier les données
    bool test = m.modifier(idmod);

    if (test) {
        // Si la modification a réussi
        QMessageBox::information(this, QObject::tr("modifier"),
                                 QObject::tr("succesfull.\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
        ui->tableView->setModel(m.afficher()); // Met à jour l'affichage
    } else {
        // Si la modification a échoué
        QMessageBox::critical(this, QObject::tr("modifier"),
                              QObject::tr("failed .\n"
                                          "Click Cancel to exit"),
                              QMessageBox::Cancel);
    }
}

void MainWindow::on_buttonHistorique_clicked()
{
    QString filePath = "stock_historique.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier d'historique.");
        return;
    }

    QTextStream in(&file);
    QString contenuHistorique = in.readAll();
    file.close();

    // Afficher le contenu dans un QLabel (assurez-vous que `historiqueLabel` existe dans l'interface)
    ui->historiqueLabel->setText(contenuHistorique);
    ui->historiqueLabel->setWordWrap(true); // Permet le retour à la ligne automatique

    QMessageBox::information(this, "Succès", "L'historique a été chargé avec succès.");
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->Home->setCurrentIndex(0);

}


void MainWindow::on_pushButton_21_clicked()
{
    ui->Home->setCurrentIndex(1);

}


void MainWindow::on_pushButton_23_clicked()
{
    ui->Home->setCurrentIndex(7);

}


void MainWindow::on_supplier_pushButton2_clicked()
{
    ui->Home->setCurrentIndex(8);

}


void MainWindow::showEvent(QShowEvent *event)
{
    //QDialog::showEvent(event);
    QSqlQueryModel* model = f.afficher();
    ui->tableView_3->setModel(model);
}
void MainWindow::clearFields()
{
    ui->ID->clear();
    ui->NAME->clear();
    ui->ADRESSE->clear();
    ui->EMAIL->clear();
    ui->TELEPHONE->clear();
    ui->CONTACT->clear();
}
void MainWindow::on_add_clicked()
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
        ui->tableView_3->setModel(f.afficher());
        QMessageBox::information(nullptr, QObject::tr("Sucsess !!"),
                              QObject::tr("fournisseur ajouté."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error !!"),
                              QObject::tr("Cannot add fournisseur."), QMessageBox::Cancel);
    }
}


void MainWindow::on_update_clicked()
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
        ui->tableView_3->setModel(f.afficher());
        QMessageBox::information(nullptr, QObject::tr("Sucsess !!"),
                                 QObject::tr("fournisseur modifié."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error !!"),
                              QObject::tr("Cannot edit fournisseur."), QMessageBox::Cancel);
    }

}


void MainWindow::on_deletebt_clicked()
{
    fournisseur f1;
    f1.Supprimer(ui->IDS->text().toInt());
    ui->tableView_3->setModel(f.afficher());
}


void MainWindow::on_pushButton_rech_clicked()
{
    QString val=ui->lineEdit_rech->text();
    QString option=ui->comboBox_rech->currentText();

    if((val!="")&&(option=="Nom"))
    {        ui->tableView_3->setModel(f.afficher_name(val));}
    else if((val!="")&&(option=="Adresse"))
    {
        ui->tableView_3->setModel(f.afficher_adresse(val));
    }
    else if((val!="")&&(option=="Email"))
    {
        ui->tableView_3->setModel(f.afficher_email(val));
    }
}



void MainWindow::on_comboBox_tri_currentIndexChanged(int index)
{
    QString choix=ui->comboBox_tri->currentText();
    ui->tableView_3->setModel(f.afficher_choix(choix));
}


void MainWindow::on_pushButton_pdf_clicked()
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


void MainWindow::on_send_clicked()
{
    QString userInput = ui->input->text(); // Retrieve user input from lineEdit
    if (!userInput.isEmpty()) {
        // Display the user input in the text edit
        ui->output->append("You: " + userInput);

        // Send the user input to ChatGPT
        client->sendRequest(userInput);

        // Clear the input field
        ui->input->clear();
    }
}


void MainWindow::on_pushButton_stat_clicked()
{
    int A= f.statistique1(); // a = 30 ( nb de quantité inf 30 )
    int B= f.statistique2(); // b = 50 ( nb de quantité sup 30 )
    float s1= A*100 ; // s1 = 3000  a = 30
    float s2=B*100;  // s2 = 5000  b = 50
    float nb = A+B; // nb = 80
    float q2 ;
    q2 = s1/nb ;   // q2 = 3000/80 = 37.5 %
    float q3;
    q3=s2/nb;      // q3 = 5000/80 = 62.5 %
    float y  ;
    y = (q2*360)/100 ;  // y = 37.5*360/100 = 135
    float m;
    m= (q3*360)/100;   // m = 62.5*360/100 = 225

    float res1 = 16*y;  // res1  = 2160
    float res2 = 16*m;  // res2 = 3600

    QChartView *chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);

    QPieSeries *series = new QPieSeries();
    series->append("Adresse Tunis", res1);

    series->append("Adresse étranger", res2);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique par rapport l'adresse");

    chartView = new QChartView(chart,ui->label_stat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(850,600);
    chartView->show();
}
//arduino 2
void MainWindow::setupSerialPort() {
    // Replace "COM4" with the correct port for your system
    serialPort->setPortName("COM3");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    // Connect the readyRead signal to the readSerialData slot
    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readSerialData);

    // Try to open the port in ReadWrite mode
    if (!serialPort->open(QIODevice::ReadWrite)) { // Change ReadOnly to ReadWrite
        qDebug() << "Error opening serial port: " << serialPort->errorString();
        QMessageBox::critical(this, "Serial Port Error", "Unable to open serial port: " + serialPort->errorString());
    } else {
        qDebug() << "Serial port opened successfully!";
    }
}

void MainWindow::readSerialData() {
    QByteArray data = serialPort->readAll();
    QString message(data);
    updateDisplay(message);
}

void MainWindow::updateDisplay(const QString &message) {
    // Update the QLabel based on the received message
    if (message.contains("Stock faible")) {
        ui->ard->setText("<b style='color:red; font-size:48px;'>Stock faible</b>"); // Bold, red, and font size 48
        QPixmap alertPixmap("C:/Users/IBRI/Desktop/pour youssef/alerte.png"); // Update with your path
        ui->img->setPixmap(alertPixmap.scaled(ui->img->size(), Qt::KeepAspectRatio));
    } else if (message.contains("Aucun objet détecté.")) {
        ui->ard->setText("<b style='color:green; font-size:48px;'>Stock suffisant</b>"); // Bold, green, and font size 48
        QPixmap tickPixmap("C:/Users/IBRI/Desktop/pour youssef/tick.png"); // Update with your path
        ui->img->setPixmap(tickPixmap.scaled(ui->img->size(), Qt::KeepAspectRatio));
    }
}


