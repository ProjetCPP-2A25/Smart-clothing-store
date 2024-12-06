#include "mainwindow.h"
#include "qdir.h"
#include "ui_mainwindow.h"
#include "stock.h"
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QDebug>
#include <QPixmap>
#include <QScreen>
#include <QApplication>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QLabel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QColor>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QPropertyAnimation>
#include <QEvent>
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QPieSeries>
#include <QPieSlice>
#include <QChart>
#include <QChartView>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDialog>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) ,
    ui(new Ui::MainWindow)
{ ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableView->setModel(s.afficher());
    ui->lineEdit_Prix->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_Quantite->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_Prix_modif->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_Quantite_modif->setValidator(new QIntValidator(0,99999999,this));
    connect(ui->rechercherBtn, SIGNAL(clicked()), this, SLOT(on_rechercherBtn_clicked()));
    connect(ui->sortBtn, SIGNAL(clicked()), this, SLOT(on_sortBtn_clicked()));
    connect(ui->exportButton_6, &QPushButton::clicked, this, &MainWindow::on_exportButton_6_clicked);
    connect(ui->btn_gestion_stocks, &QPushButton::clicked, this, &MainWindow::on_btn_gestion_stocks_clicked);
     connect(ui->buttonHistorique, &QPushButton::clicked, this, &MainWindow::afficherHistorique);
    ui->line->setPlaceholderText("ID Produit");
     //connect(ui->pushButton, &QPushButton::pressed, this, &MainWindow::animateStatButtonOnPress);
     //connect(ui->pushButton, &QPushButton::released, this, &MainWindow::animateStatButtonOnRelease);
     connect(ui->stat, &QPushButton::clicked, this, &MainWindow::showProfitChart); // Affiche le graphique au clic






}MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_statisticsBtn_clicked() {
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

void MainWindow::showMostProfitableBrand() {
    double maxProfit = 0.0;
    Stock stock;
    QString brand = stock.mostProfitableBrand(maxProfit);

    if (!brand.isEmpty()) {
        QMessageBox::information(this, "Marque la plus rentable",
                                 "Marque : " + brand +
                                     "\nProfit : $" + QString::number(maxProfit));
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer la marque la plus rentable.");
    }
}



void MainWindow::showProfitChart()
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

void MainWindow::on_allerAjoutBtn_clicked()
{
      ui->stackedWidget->setCurrentIndex(1);
    ui->error_fr->setVisible(false);
    ui->error_lv->setVisible(false);
    ui->error_nom->setVisible(false);
    ui->error_qt->setVisible(false);
    ui->error_marque->setVisible(false);
    ui->error_prix->setVisible(false);
}


void MainWindow::on_AnnulerBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_nom->clear();
    ui->lineEdit_Prix->clear();
    ui->lineEdit_Quantite->clear();
    ui->lineEdit_Marque->clear();

}


void MainWindow::on_AjoutStockBtn_clicked()
{

    QString nom = ui->lineEdit_nom->text();
    int idProduit = ui->line->text().toInt();
    double prix = ui->lineEdit_Prix->text().toDouble();
    int qt = ui->lineEdit_Quantite->text().toInt();
    QString marque = ui->lineEdit_Marque->text();
    int idF = ui->comboBox->currentText().toInt();
    int idL = ui->comboBox_2->currentText().toInt();

    Stock s(idProduit, nom, qt, prix, marque, idF, idL);

    if (validate()) {
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
    } else {
        QMessageBox::warning(nullptr, QObject::tr("Validation échouée"),
                             QObject::tr("Veuillez vérifier les champs avant de soumettre."));
    }
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int i;
    i=index.row();
    QModelIndex in=index.sibling(i,0);
    QString val=ui->tableView->model()->data(in).toString();
    idmod = ui->tableView->model()->data(in).toInt();


            ui->lineEdit_nom_modif->setText(ui->tableView->model()->data(index.sibling(i,1)).toString());
            ui->lineEdit_Prix_modif->setText(ui->tableView->model()->data(index.sibling(i,3)).toString());
            ui->lineEdit_Quantite_modif->setText(ui->tableView->model()->data(index.sibling(i,2)).toString());
            ui->lineEdit_Marque_modif->setText(ui->tableView->model()->data(index.sibling(i,4)).toString());
            ui->comboBox_fr_modif->setCurrentText(ui->tableView->model()->data(index.sibling(i,5)).toString());
            ui->comboBox_lv_modif->setCurrentText(ui->tableView->model()->data(index.sibling(i,6)).toString());



}


void MainWindow::on_pushButton_3_clicked()
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


void MainWindow::on_AnnulerBtn_modif_clicked()
{

 ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_modifierStockBtn_clicked()
{

    QString nom=ui->lineEdit_nom_modif->text();
    double prix=ui->lineEdit_Prix_modif->text().toDouble();
    int qt=ui->lineEdit_Quantite_modif->text().toInt();
    QString marque=ui->lineEdit_Marque_modif->text();
    int idF = ui->comboBox_fr_modif->currentText().toInt() ;
    int idL = ui->comboBox_lv_modif->currentText().toInt() ;
    Stock m(idmod,nom,qt,prix,marque,idF,idL);

    if(validate_modification()){
    bool test=m.modifier(idmod);
    if (test)
    {
        ui->tableView->setModel(s.afficher());

        QMessageBox::information(nullptr, QObject::tr("modifier"),
                                 QObject::tr(" successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("modifier"),
                              QObject::tr(" failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    }
    ui->stackedWidget->setCurrentIndex(0);}

}


void MainWindow::on_pushButton_2_clicked()
{

    ui->error_fr_mod->setVisible(false);
    ui->error_lv_mod->setVisible(false);
    ui->error_nom_mod->setVisible(false);
    ui->error_qt_mod->setVisible(false);
    ui->error_marque_mod->setVisible(false);
    ui->error_prix_mod->setVisible(false);

    if(ui->tableView->currentIndex().isValid()){
        ui->stackedWidget->setCurrentIndex(2);}else{
        QMessageBox::warning(nullptr, QObject::tr("info"),
                              QObject::tr(" il faut selectionner une ligne  .\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_rfchBtn_clicked()
{
   ui->tableView->setModel(s.afficher());
}

bool MainWindow::validate()
{
    ui->error_fr->setVisible(false);
    ui->error_lv->setVisible(false);
    ui->error_nom->setVisible(false);
    ui->error_qt->setVisible(false);
    ui->error_marque->setVisible(false);
    ui->error_prix->setVisible(false);

    bool v = true;
    if (ui->lineEdit_nom->text().isEmpty())
    {
        ui->error_nom->setVisible(true);
        v = false;
    }
    if (ui->lineEdit_Prix->text().isEmpty())
    {
        ui->error_prix->setVisible(true);
        v = false;
    }
    if (ui->lineEdit_Quantite->text().isEmpty())
    {
        ui->error_qt->setVisible(true);
        v = false;
    }
    if (ui->lineEdit_Marque->text().isEmpty())
    {
        ui->error_marque->setVisible(true);
        v = false;
    }
    if (ui->comboBox->currentIndex() == -1)
    {
        ui->error_fr->setVisible(true);
        v = false;
    }
    if (ui->comboBox_2->currentIndex() == -1)
    {
        ui->error_lv->setVisible(true);
        v = false;
    }

    return v;
}

bool MainWindow::validate_modification()
{
    ui->error_fr_mod->setVisible(false);
    ui->error_lv_mod->setVisible(false);
    ui->error_nom_mod->setVisible(false);
    ui->error_qt_mod->setVisible(false);
    ui->error_marque_mod->setVisible(false);
    ui->error_prix_mod->setVisible(false);
    bool v = true;
    if( ui->lineEdit_nom_modif->text().isEmpty()){
        ui->error_nom_mod->setVisible(true);
        v = false;
    }
    if( ui->lineEdit_Prix_modif->text().isEmpty()){
        ui->error_prix_mod->setVisible(true);
        v = false;
    }
    if( ui->lineEdit_Quantite_modif->text().isEmpty()){
        ui->error_qt_mod->setVisible(true);
        v = false;
    }
    if( ui->lineEdit_Marque_modif->text().isEmpty()){
        ui->error_marque_mod->setVisible(true);
        v = false;
    }



    return v ;
}
void MainWindow::on_rechercherBtn_clicked()
{
    // Récupérer la chaîne entrée dans le QLineEdit
    QString recherche = ui->lineEdit_recherche->text();

    // Rechercher dans le modèle Stock par nom de produit
    QSqlQueryModel *model = s.rechercherProduit(recherche);

    // Afficher les résultats dans le QTableView
    ui->tableView->setModel(model);
}
void MainWindow::on_sortBtn_clicked() {
    QString critere = "PRIX_PRODUIT";  // On trie par l'attribut 'PRIX'
    bool croissant = (ui->comboBox->currentText() == "ASC");  // Vérifie si l'option est 'Ascending Price'

    // Obtenir le modèle trié
    QSqlQueryModel* model = s.trierStock(critere, croissant);

    // Vérifier si le modèle contient des lignes après le tri
    if (model->rowCount() == 0) {
        qDebug() << "Aucune donnée trouvée après le tri.";
    }

    // Appliquer le modèle trié au QTableView
    ui->tableView->setModel(model);
}



void MainWindow::on_exportButton_6_clicked() {
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
#include <QInputDialog>  // Assurez-vous d'inclure cette bibliothèque pour utiliser QInputDialog

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


void MainWindow::afficherHistorique() {
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
void MainWindow::on_Historic_clicked() {
    afficherHistorique();
}
