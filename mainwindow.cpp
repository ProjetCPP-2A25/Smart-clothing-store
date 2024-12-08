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

#include <QSslSocket>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

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
    //connect(ui->Exportlist_btn, &QPushButton::clicked, this, &MainWindow::on_Exportlist_btn_clicked);
    //connect(ui->Exportlist_btn_2, &QPushButton::clicked, this, &MainWindow::on_Exportlist_btn_2_clicked);
    connect(ui->seach_list, &QLineEdit::textChanged, this, &MainWindow::searchInListEmp);
    connect(ui->seach_list2, &QLineEdit::textChanged, this, &MainWindow::searchInListEmployee2);
    connect(ui->seach_cong, &QLineEdit::textChanged, this, &MainWindow::searchInListCong);
    connect(ui->seach_cong2, &QLineEdit::textChanged, this, &MainWindow::searchInListCong2);
    //connect(ui->stat, &QPushButton::clicked, this, &MainWindow::on_stat_clicked);







    connect(ui->Home, &QTabWidget::currentChanged, this, &MainWindow::on_tabBarClicked);

    ui->Home->setCurrentIndex(0); // Assuming the login page is at index 0


    //connect(ui->downloadLeaveHistory, &QPushButton::clicked, this, &MainWindow::on_downloadLeaveHistory_clicked);




}


MainWindow::~MainWindow()
{
    delete ui;

}




////////////////////////////////////////////////////////////////////////////////////////////////////debut de 1er metier:notfier livreur
/*void MainWindow::on_sendMailButton_clicked() {
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
}*/



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


/*bool MainWindow::sendEmail(const QString &to, const QString &subject, const QString &body) {
    QSslSocket *smtpSocket = new QSslSocket(this);

    // Connect to Gmail's SMTP server
    smtpSocket->connectToHostEncrypted("smtp.gmail.com", 465);
    if (!smtpSocket->waitForConnected(5000)) {
        QMessageBox::warning(this, "Connection Error", "Failed to connect to the SMTP server.");
        delete smtpSocket;
        return false; // Indicate failure
    }

    QTextStream stream(smtpSocket);

    // SMTP Communication Helper
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





    // Authenticate and send the email
    if (!sendCommand("EHLO smtp.gmail.com") ||
        !sendCommand("AUTH LOGIN") ||
        !sendCommand(QByteArray("hellourbanelegance@gmail.com").toBase64()) || // Your Gmail
        !sendCommand(QByteArray("hyrs mdow agho uonv").toBase64())) {   // Your App Password
        QMessageBox::warning(this, "Error", "SMTP authentication failed.");
        delete smtpSocket;
        return false; // Indicate failure
    }

    if (!sendCommand("MAIL FROM:<hellourbanelegance@gmail.com>") ||
        !sendCommand("RCPT TO:<" + to + ">") ||
        !sendCommand("DATA")) {
        QMessageBox::warning(this, "Error", "Failed to prepare email.");
        delete smtpSocket;
        return false; // Indicate failure
    }

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
        return false; // Indicate failure
    }

    // Close the connection
    sendCommand("QUIT");
    smtpSocket->close();
    delete smtpSocket;

    // Confirm success
    QMessageBox::information(this, "Success", "Email sent successfully to " + to + ".");
    return true; // Indicate success
}*/

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











/*void MainWindow::toggleDarkMode() {
    static bool darkModeEnabled = false;

    if (darkModeEnabled) {
        // Switch to Light Mode
        qApp->setStyleSheet("");
        ui->toggleDarkModeButton->setText("Dark Mode");
    } else {
        // Switch to Dark Mode
        QString darkModeStyle = R"(
            QWidget {
                background-color: #121212;
                color: #ffffff;
            }
            QPushButton {
                background-color: #1e1e1e;
                color: #ffffff;
                border: 1px solid #555555;
                border-radius: 5px;
                padding: 5px;
            }
            QPushButton:hover {
                background-color: #333333;
            }
            QLineEdit, QComboBox, QTextEdit {
                background-color: #1e1e1e;
                color: #ffffff;
                border: 1px solid #555555;
                border-radius: 5px;
                padding: 5px;
            }
            QComboBox QAbstractItemView::item {
                background-color: #2e2e2e;
                color: #ffffff;
            }
            QComboBox QAbstractItemView::item:hover {
                background-color: #3e3e3e;
            }
        )";
        qApp->setStyleSheet(darkModeStyle);
        ui->toggleDarkModeButton->setText("Light Mode");
    }

    darkModeEnabled = !darkModeEnabled;

    // Save preference using QSettings
    QSettings settings("YourCompany", "YourApp");
    settings.setValue("darkModeEnabled", darkModeEnabled);
}*/


    /*void MainWindow::on_AddEmp_clicked()
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
        QDate FIRST_DAY_OF_LEAVE = QDate();        // Default (null) date
        QDate LAST_DAY_OF_LEAVE = QDate();         // Default (null) date
        int NBDAYS = 0;                            // Default leave days count

        // Create the employee object with placeholders for unused attributes
        Employe e(CIN, NOM_E, PRENOM_E, POST, EMAIL, TELEPHONE, ADRESSE, LEAVE_TYPE, FIRST_DAY_OF_LEAVE, LAST_DAY_OF_LEAVE, NBDAYS);


        // Call the ajouter method to add the employee
        bool test = e.ajouter();
        if (test)
        {
            QMessageBox::information(nullptr, QObject::tr("Successful"),
                                     QObject::tr("Employee added successfully.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);

            // Clear UI fields after successful addition
            ui->IDEMP->clear();
            ui->nameE->clear();
            ui->prenomE->clear();
            ui->jobECombo->setCurrentIndex(0);
            ui->mailE->clear();
            ui->phone_E->clear();
            ui->adresse_E->clear();
        }*/
        /*else
        {
            QMessageBox::critical(nullptr, QObject::tr("Error"),
                                  QObject::tr("Failed to add employee.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }*/
    //}








/*#include <QTcpSocket>
#include <QTextStream>
#include <QMessageBox>

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

    // Placeholder for leave-related attributes
    QString LEAVE_TYPE = "";
    QDate FIRST_DAY_OF_LEAVE = QDate();
    QDate LAST_DAY_OF_LEAVE = QDate();
    int NBDAYS = 0;

    // Create the employee object
    Employe e(CIN, NOM_E, PRENOM_E, POST, EMAIL, TELEPHONE, ADRESSE, LEAVE_TYPE, FIRST_DAY_OF_LEAVE, LAST_DAY_OF_LEAVE, NBDAYS);

    // Add the employee
    bool test = e.ajouter();
    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("Successful"),
                                 QObject::tr("Employee added successfully.\nClick Cancel to exit."), QMessageBox::Cancel);

        // Send email to the new employee
        if (!sendWelcomeEmail(EMAIL, NOM_E, PRENOM_E, CIN)) {
            QMessageBox::warning(this, "Email Error", "Failed to send welcome email.");
        } else {
            QMessageBox::information(this, "Email Sent", "Welcome email sent successfully!");
        }

        // Clear UI fields
        ui->IDEMP->clear();
        ui->nameE->clear();
        ui->prenomE->clear();
        ui->jobECombo->setCurrentIndex(0);
        ui->mailE->clear();
        ui->phone_E->clear();
        ui->adresse_E->clear();
    }*/
    /*else
    {
        QMessageBox::critical(nullptr, QObject::tr("Error"),
                              QObject::tr("Failed to add employee.\nClick Cancel to exit."), QMessageBox::Cancel);
    }*/
//}




/*bool MainWindow::sendWelcomeEmail(const QString &toEmail, const QString &firstName, const QString &lastName, int cin) {
    QString fromEmail = "hellourbanelegance@gmail.com";
    QString fromPassword = "nfjk ykqw loin uxxh"; // Use your Gmail app-specific password
    QString smtpServer = "smtp.gmail.com";
    int smtpPort = 587;  // SSL port for Gmail SMTP

    QString cinString = QString::number(cin);

    // Construct the email message
    QString message = QString("Dear %1 %2,\n\n"
                              "Welcome to our company!\n\n"
                              "Here are your login details:\n"
                              "Email: %3\n"
                              "Password: %4\n\n"
                              "Please let us know if you have any questions.\n\n"
                              "Best regards,\n"
                              "Your Company")
                      .arg(firstName)
                      .arg(lastName)
                      .arg(toEmail)
                      .arg(cinString);

    // Simulate sending an email
    qDebug() << "Sending email to:" << toEmail;
    qDebug() << "Message content:" << message;

    QTcpSocket socket;
    socket.connectToHost(smtpServer, smtpPort);

    if (!socket.waitForConnected(30000)) {
        QMessageBox::critical(nullptr, "SMTP Error", "Failed to connect to the SMTP server.");
        return false;
    }

    // SMTP handshake
    auto sendCommand = [&](const QString &cmd) {
        socket.write(cmd.toUtf8() + "\r\n");
        if (!socket.waitForBytesWritten(5000) || !socket.waitForReadyRead(5000)) {
            return false;
        }

        QByteArray response = socket.readAll();
        qDebug() << "SMTP Response: " << response;
        return true;
    };

    // Send "HELO" command and check response
    if (!sendCommand("HELO localhost")) {
        qDebug() << "HELO command failed.";
        return false;
    }

    // Authenticate with the SMTP server using your app password
    if (!sendCommand("AUTH LOGIN") ||
        !sendCommand(QByteArray(fromEmail.toUtf8()).toBase64()) ||
        !sendCommand(QByteArray(fromPassword.toUtf8()).toBase64())) {
        return false;
    }

    // Send the "MAIL FROM" command with proper formatting
    if (!sendCommand("MAIL FROM:<" + fromEmail + ">")) {
        return false;
    }

    // Send the "RCPT TO" command with the recipient's email
    if (!sendCommand("RCPT TO:<" + toEmail + ">")) {
        return false;
    }

    // Send the "DATA" command, which indicates the start of the email body
    if (!sendCommand("DATA")) {
        return false;
    }

    // Send the actual email content
    QString emailData = QString("Subject: Welcome to Our Company\r\n") +
                        "To: " + toEmail + "\r\n" +
                        "From: " + fromEmail + "\r\n" +
                        "\r\n" + message + "\r\n.\r\n";  // "\r\n." is used to end the message body
      // "\r\n." is used to end the message body
    if (!sendCommand(emailData)) {
        return false;
    }

    // Finalize the session with the QUIT command
    sendCommand("QUIT");
    socket.close();
    return true;
}*/





























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



/*void MainWindow::on_Updatelist_btn2_clicked()
{

    int CIN = ui->IDEMP->text().toInt();
    QString NOM_E = ui->nameE->text();
    QString PRENOM_E = ui->prenomE->text();
    QString POST = ui->jobE->text();
    QString EMAIL = ui->mailE->text();
    int TELEPHONE = ui->phone_E->text().toInt();
    QString ADRESSE = ui->adresse_E->text();

    QString LEAVE_TYPE="None";


    Employe e(CIN, "", "", "", "", 0, "","");


    if (e.cinexiste(CIN)) {

        bool test = e.Modifier(NOM_E, PRENOM_E, POST, EMAIL, TELEPHONE, ADRESSE,LEAVE_TYPE,);


        if (test) {
            QMessageBox::information(nullptr, QObject::tr("MODIFICATION"),
                QObject::tr("Success: Employee details updated.\nClick Cancel to exit."), QMessageBox::Ok);
            ui->list_emp->setModel(e.afficher());

            ui->IDEMP->clear();
            ui->nameE->clear();
            ui->prenomE->clear();
            ui->jobE->clear();
            ui->mailE->clear();
            ui->phone_E->clear();
            ui->adresse_E->clear();
        } else {
            QMessageBox::critical(nullptr, QObject::tr("MODIFICATION"),
                QObject::tr("Error during update. Please check your inputs.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    } else {

        QMessageBox::critical(nullptr, QObject::tr("MODIFICATION"),
            QObject::tr("Error: CIN does not exist.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}*/


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


/*void MainWindow::searchInListEmp(const QString &searchText)
{
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(ui->list_emp->model());
    //proxyModel->setSourceModel(ui->list_employee->model());
    proxyModel->setFilterKeyColumn(0);
    proxyModel->setFilterKeyColumn(1);
    proxyModel->setFilterFixedString((searchText));

    ui->list_emp->setModel(proxyModel);
}*/


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
    ui->Home->setCurrentIndex(2);
}

void MainWindow::on_employee_pushButton_clicked()
{
    ui->Home->setCurrentIndex(2);
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
    ui->Home->setCurrentIndex(1);
}

void MainWindow::on_home_pushButton_3_clicked()
{
    ui->Home->setCurrentIndex(1);
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

            ui->Home->setCurrentIndex(1); // Navigate to the home page

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

/*void MainWindow::on_Uapdatelist_btn_4_clicked()
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

        // Define leave details
        QDate FIRST_DAY_OF_LEAVE = QDate::currentDate(); // Default to current date
        QDate LAST_DAY_OF_LEAVE = FIRST_DAY_OF_LEAVE.addDays(7); // Default duration: 7 days
        int NBDAYS = 7; // Default number of days (this can be dynamic based on user input)

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
}*/

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












/*void MainWindow::on_Exportlist_btn_2_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->list_cong->model()->rowCount();
    const int columnCount = ui->list_cong->model()->columnCount();

    out << "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << QString("<title>%1</title>\n").arg("Employee List")
        << "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<center><H1>Liste Des Congees</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

    // Headers
    out << "<thead><tr bgcolor=#f0f0f0><th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->list_cong->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->list_cong->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // Data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr><td>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->list_cong->isColumnHidden(column)) {
                QString data = ui->list_cong->model()->data(ui->list_cong->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out << "</table></center>\n"
        "</body>\n"
        "</html>\n";

    QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);

    // No need to set page size manually
    // doc.setPageSize(printer.pageRect().size()); // This line can be removed

    doc.print(&printer);

    QMessageBox::information(this, "Export Successful", "PDF file has been successfully created.");
}*/






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

/*void MainWindow::on_Exportlist_btn_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->list_emp->model()->rowCount();
    const int columnCount = ui->list_emp->model()->columnCount();

    out << "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << QString("<title>%1</title>\n").arg("Employee List")
        << "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<center><H1>Liste Des Employees</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

    // Headers
    out << "<thead><tr bgcolor=#f0f0f0><th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->list_emp->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->list_emp->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // Data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr><td>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->list_emp->isColumnHidden(column)) {
                QString data = ui->list_emp->model()->data(ui->list_emp->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out << "</table></center>\n"
        "</body>\n"
        "</html>\n";

    QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);

    // No need to set page size manually
    // doc.setPageSize(printer.pageRect().size()); // This line can be removed

    doc.print(&printer);

    QMessageBox::information(this, "Export Successful", "PDF file has been successfully created.");
}*/
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
    ui->Home->setCurrentIndex(1);
}


void MainWindow::on_pushButton_12_clicked()
{
    ui->Home->setCurrentIndex(2);
}


void MainWindow::on_pushButton_14_clicked()
{
    ui->Home->setCurrentIndex(3);
}


void MainWindow::on_viewCong_clicked()
{
    ui->Home->setCurrentIndex(4);
}


void MainWindow::on_home_pushButton_6_clicked()
{
    ui->Home->setCurrentIndex(1);
}


void MainWindow::on_employee_pushButton_6_clicked()
{
    ui->Home->setCurrentIndex(2);
}


void MainWindow::on_employee_pushButton_2_clicked()
{
    ui->Home->setCurrentIndex(2);
}









