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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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






}


MainWindow::~MainWindow()
{
    delete ui;

}



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
        }
        /*else
        {
            QMessageBox::critical(nullptr, QObject::tr("Error"),
                                  QObject::tr("Failed to add employee.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }*/
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
void MainWindow::on_AddList_btn_4_clicked()
{

        int CIN = ui->IDEMP_4->text().toInt();

        // Retrieve existing employee data
        Employe existingEmployee = Employe::GetByCIN(CIN); // Method to fetch existing data


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
        QDate FIRST_DAY_OF_LEAVE = QDate::currentDate(); // New value
        QDate LAST_DAY_OF_LEAVE = FIRST_DAY_OF_LEAVE.addDays(0); // New value
        int NBDAYS = 0; // New value

        // Create the Employe object with existing values for unchanged attributes
        Employe e(CIN, existingEmployee.getNOM_E(), existingEmployee.getPRENOM_E(), existingEmployee.getPOST(), existingEmployee.getEMAIL(),
                   existingEmployee.getTELEPHONE(), existingEmployee.getADRESSE(),
                   LEAVE_TYPE, FIRST_DAY_OF_LEAVE, LAST_DAY_OF_LEAVE, NBDAYS);

        // Call update
        bool test = e.Modifier();
        if (test) {
            QMessageBox::information(nullptr, QObject::tr("Successful"),
                                     QObject::tr("Successful.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                                  QObject::tr("Update failed.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }

}


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
}










void MainWindow::on_Exportlist_btn_2_clicked()
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

    out << "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << QString("<title>%1</title>\n").arg("Employee List")
        << "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<center><H1>Liste Des EMP</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

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
}





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

