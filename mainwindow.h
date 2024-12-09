#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "livraison.h"
#include<QSqlDatabase>
#include <QMainWindow>
#include <QString>
#include <QDate>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QPushButton>
#include <QStringList>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonArray>
#include <QUrl>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTcpSocket>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QSqlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTableWidgetItem>
#include <QTextCharFormat>
#include <QDate>
#include <QCalendarWidget>
#include <QLabel>
#include <QTableWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMainWindow>
#include <QByteArray>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QSqlQuery>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void rechercherLivraisonsParPeriode();//2eme


private slots:
    void on_pushButton_ajouter_clicked(); // ajout
    void on_supprimer_Clicked() ;    //delete
    void on_modifier_Clicked();  // Slot pour le bouton Modifier
    void afficherLivraisons();//afficher
    void on_rechercher_clicked();
    void exporterEnCSV() ;
////////////////////////////////send
    void on_sendMailButton_clicked();  // Slot for sending email
void sendEmail(const QString &to, const QString &subject, const QString &body) ;
////////////////////////////////send
/////////////////////////////////////////////////////////////////////////////calendrier
// Slot pour la gestion du clic sur une date
void onDateClicked(const QDate &date);
void updateCalendar() ;
void afficherLivraisonsStats();
void fermerStatistiques();


//////////////////////////////////////////////////////////////////////////////calendrier




    /// \arduino
void on_openDoorButton_clicked();   // Slot to open the door
void on_closeDoorButton_clicked();  // Slot to close the door
void readFromArduino();  // Slot to read data from Arduino
void on_autoModeButton_clicked();

private:
    Ui::MainWindow *ui;
    Livraison livraison;


    QNetworkAccessManager *networkManager;
    // Méthode pour initialiser le calendrier
    QCalendarWidget *calendar;
    QLabel *noteLabel;
    void onTrierClicked();
    void afficherLivraisonsTriées(const QString& critere) ;
    QPushButton *closeStatsButton;  // Bouton de fermeture

//////////////////////arduino
 QSerialPort *serial;  // Serial port to communicate with Arduino
    QString arduinoPort;  // Port for Arduino connection
    bool isArduinoConnected;  // Flag to track Arduino connection status
       bool isAutoMode = false; // Add this to your header or class definition

    void connectToArduino();  // Method to connect to Arduino
    void sendCommandToArduino(const QByteArray &command);  // Method to send commands to Arduino

    QWidget *statsWindow; // Fenêtre pour afficher le graphique

};

#endif // MAINWINDOW_H
