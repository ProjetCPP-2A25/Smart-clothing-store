#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stock.h"
#include <QTableWidget> // Assurez-vous que c'est bien ce que vous utilisez
#include <QPdfWriter>
#include <QPainter>
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimerEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_allerAjoutBtn_clicked();

    void on_AnnulerBtn_clicked();

    void on_AjoutStockBtn_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_AnnulerBtn_modif_clicked();

    void on_modifierStockBtn_clicked();

    void on_pushButton_2_clicked();

    void on_rfchBtn_clicked();
    bool validate();
    bool validate_modification();
    void on_rechercherBtn_clicked();
     void on_sortBtn_clicked();
    void on_exportButton_6_clicked();
    void on_btn_gestion_stocks_clicked();
    void on_Historic_clicked();
    void afficherHistorique();
    void on_statisticsBtn_clicked();
    void showProfitChart();
    void showMostProfitableBrand();
    void animateStatButtonOnPress();
    void animateStatButtonOnRelease();




private:
    int idmod;
    Stock s;
    Ui::MainWindow *ui;

    void connectToDatabase();
    bool isDatabaseOpen();
    void exporterCaptureTableauEnPdf();
    void addProductToTable(int idProduit, const QString& nomProduit, int quantiteProduit, double prixProduit, const QString& marqueProduit);
};
#endif // MAINWINDOW_H
