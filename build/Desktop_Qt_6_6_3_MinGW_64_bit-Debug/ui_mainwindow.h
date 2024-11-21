/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tab;
    QWidget *tab_1;
    QLabel *label_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QLabel *label_12;
    QLineEdit *lineEdit_adresse;
    QTableWidget *table_livraisons;
    QDateEdit *dateEdit_dateprevue;
    QLabel *label_19;
    QPushButton *supprimer;
    QLabel *label_15;
    QLabel *label_17;
    QPushButton *pushButton_ajouter;
    QLabel *label_18;
    QDateEdit *dateEdit_dateeffectuee;
    QLineEdit *lineEdit_id;
    QPushButton *modifier;
    QLabel *label_16;
    QLineEdit *lineEdit_id2;
    QPushButton *pushButton_15;
    QLabel *label_13;
    QPushButton *pushButton_33;
    QPushButton *boutonRechercher;
    QPushButton *boutonTri;
    QPushButton *boutonExporterCSV;
    QComboBox *comboBox;
    QLabel *label_21;
    QLabel *label_22;
    QLineEdit *lineEdit_nomLivreur;
    QLineEdit *lineEdit_emailLivreur;
    QLabel *statistiquesLabel;
    QPushButton *pushButton_stats;
    QPushButton *retour;
    QWidget *tab_3;
    QLabel *label_11;
    QLabel *label_14;
    QPushButton *pushButton_31;
    QLabel *label_43;
    QPushButton *pushButton_37;
    QPushButton *pushButton_36;
    QPushButton *pushButton_32;
    QPushButton *pushButton_38;
    QPushButton *pushButton_35;
    QPushButton *pushButton_34;
    QPushButton *pushButton_39;
    QLabel *label_41;
    QCalendarWidget *calendarWidget;
    QPushButton *sendEmailButton;
    QLabel *noteLabel;
    QLabel *label_46;
    QWidget *tab_4;
    QLabel *label_42;
    QLabel *label_44;
    QLabel *label_45;
    QPushButton *pushButton_on;
    QPushButton *pushButton_plus;
    QPushButton *pushButton_off;
    QPushButton *pushButton_moin;
    QLabel *connectionStatusLabel;
    QPushButton *openDoorButton;
    QPushButton *closeDoorButton;
    QTextEdit *distanceTextEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(953, 545);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        tab = new QTabWidget(centralWidget);
        tab->setObjectName("tab");
        tab->setGeometry(QRect(0, 10, 951, 481));
        tab_1 = new QWidget();
        tab_1->setObjectName("tab_1");
        label_8 = new QLabel(tab_1);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(-30, 0, 1101, 501));
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/pour youssef/bg.png")));
        label_8->setScaledContents(true);
        pushButton_9 = new QPushButton(tab_1);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(-10, 100, 150, 40));
        pushButton_9->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  color: #333333; /* Dark text color */\n"
"    border: none;                        /* Remove border */\n"
"    border-radius: 5px;                  /* Rounded corners */\n"
"    padding: 10px 20px;                  /* Padding for button size */\n"
"    font-size: 12px;                     /* Font size */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(56, 76, 130);  /* Lighter blue on hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgb(31, 46, 84);   /* Even darker blue on press */\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pour youssef/abri (1).png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_9->setIcon(icon);
        pushButton_9->setIconSize(QSize(60, 35));
        pushButton_10 = new QPushButton(tab_1);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(-20, 150, 181, 41));
        pushButton_10->setMinimumSize(QSize(0, 0));
        pushButton_10->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  color: #333333; /* Dark text color */\n"
"    border: none;                        /* Remove border */\n"
"    border-radius: 5px;                  /* Rounded corners */\n"
"    padding: 10px 20px;                  /* Padding for button size */\n"
"    font-size: 12px;                     /* Font size */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(56, 76, 130);  /* Lighter blue on hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgb(31, 46, 84);   /* Even darker blue on press */\n"
"}\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/pour youssef/employes.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_10->setIcon(icon1);
        pushButton_10->setIconSize(QSize(60, 35));
        pushButton_11 = new QPushButton(tab_1);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(-10, 200, 161, 41));
        pushButton_11->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  color: #333333; /* Dark text color */\n"
"    border: none;                        /* Remove border */\n"
"    border-radius: 5px;                  /* Rounded corners */\n"
"    padding: 10px 20px;                  /* Padding for button size */\n"
"    font-size: 12px;                     /* Font size */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(56, 76, 130);  /* Lighter blue on hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgb(31, 46, 84);   /* Even darker blue on press */\n"
"}\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/pour youssef/contact.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_11->setIcon(icon2);
        pushButton_11->setIconSize(QSize(60, 35));
        pushButton_12 = new QPushButton(tab_1);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(-20, 280, 171, 51));
        pushButton_12->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  color: #333333; /* Dark text color */\n"
"    border: none;                        /* Remove border */\n"
"    border-radius: 5px;                  /* Rounded corners */\n"
"    padding: 10px 20px;                  /* Padding for button size */\n"
"    font-size: 12px;                     /* Font size */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(56, 76, 130);  /* Lighter blue on hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgb(31, 46, 84);   /* Even darker blue on press */\n"
"}\n"
""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/pour youssef/logistics-delivery.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_12->setIcon(icon3);
        pushButton_12->setIconSize(QSize(60, 40));
        pushButton_13 = new QPushButton(tab_1);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(-20, 250, 171, 31));
        pushButton_13->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(41, 61, 110);  /* Dark blue color */\n"
"    color: white;                        /* White text */\n"
"    border: none;                        /* Remove border */\n"
"    border-radius: 5px;                  /* Rounded corners */\n"
"    padding: 10px 20px;                  /* Padding for button size */\n"
"    font-size: 12px;                     /* Font size */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(56, 76, 130);  /* Lighter blue on hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgb(31, 46, 84);   /* Even darker blue on press */\n"
"}\n"
""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/pour youssef/livraison-rapide (1).png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_13->setIcon(icon4);
        pushButton_13->setIconSize(QSize(60, 35));
        pushButton_14 = new QPushButton(tab_1);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(-50, 330, 231, 51));
        pushButton_14->setAutoFillBackground(false);
        pushButton_14->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  color: #333333; /* Dark text color */\n"
"    border: none;                        /* Remove border */\n"
"    border-radius: 5px;                  /* Rounded corners */\n"
"    padding: 10px 20px;                  /* Padding for button size */\n"
"    font-size: 12px;                     /* Font size */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(56, 76, 130);  /* Lighter blue on hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgb(31, 46, 84);   /* Even darker blue on press */\n"
"}\n"
""));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/pour youssef/courrier.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_14->setIcon(icon5);
        pushButton_14->setIconSize(QSize(60, 40));
        label_12 = new QLabel(tab_1);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(140, 10, 801, 431));
        label_12->setAutoFillBackground(false);
        label_12->setPixmap(QPixmap(QString::fromUtf8(":/pour youssef/bgW.png")));
        label_12->setScaledContents(true);
        label_12->setMargin(0);
        lineEdit_adresse = new QLineEdit(tab_1);
        lineEdit_adresse->setObjectName("lineEdit_adresse");
        lineEdit_adresse->setGeometry(QRect(240, 190, 71, 21));
        table_livraisons = new QTableWidget(tab_1);
        if (table_livraisons->columnCount() < 6)
            table_livraisons->setColumnCount(6);
        QFont font;
        font.setPointSize(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        table_livraisons->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QFont font1;
        font1.setPointSize(7);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        table_livraisons->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font1);
        table_livraisons->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QFont font2;
        font2.setPointSize(6);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font2);
        table_livraisons->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font1);
        table_livraisons->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font1);
        table_livraisons->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        table_livraisons->setObjectName("table_livraisons");
        table_livraisons->setGeometry(QRect(330, 90, 611, 211));
        table_livraisons->setTabletTracking(false);
        table_livraisons->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        table_livraisons->setAutoFillBackground(false);
        table_livraisons->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white; /* Table background */\n"
"    gridline-color: lightgray; /* Grid line color */\n"
"    border: 1px solid gray; /* Table border */\n"
"    font-family: Arial, sans-serif; /* Font family for text */\n"
"  \n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: rgb(41, 61, 110); /* Light blue header background */\n"
"    color: white; /* Header text color */\n"
"    font-weight: bold; /* Bold header text */\n"
"    font-size: 10px; /* Smaller font size for header text */\n"
"    text-align: center; /* Center-align header text */\n"
"    border: 1px solid white; /* White border between header cells */\n"
"    padding: 4px; /* Padding inside the header cells */\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    border: 1px solid lightgray; /* Border for each table cell */\n"
"    \n"
"}"));
        table_livraisons->setColumnCount(6);
        table_livraisons->horizontalHeader()->setCascadingSectionResizes(true);
        table_livraisons->verticalHeader()->setCascadingSectionResizes(true);
        dateEdit_dateprevue = new QDateEdit(tab_1);
        dateEdit_dateprevue->setObjectName("dateEdit_dateprevue");
        dateEdit_dateprevue->setGeometry(QRect(240, 124, 81, 21));
        label_19 = new QLabel(tab_1);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(160, 170, 61, 61));
        label_19->setScaledContents(true);
        supprimer = new QPushButton(tab_1);
        supprimer->setObjectName("supprimer");
        supprimer->setGeometry(QRect(150, 400, 71, 31));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe Print")});
        supprimer->setFont(font3);
        label_15 = new QLabel(tab_1);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(570, 30, 251, 61));
        label_15->setScaledContents(true);
        label_17 = new QLabel(tab_1);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(150, 110, 81, 41));
        label_17->setScaledContents(true);
        pushButton_ajouter = new QPushButton(tab_1);
        pushButton_ajouter->setObjectName("pushButton_ajouter");
        pushButton_ajouter->setGeometry(QRect(240, 310, 61, 31));
        pushButton_ajouter->setFont(font3);
        label_18 = new QLabel(tab_1);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(140, 140, 91, 51));
        label_18->setScaledContents(true);
        dateEdit_dateeffectuee = new QDateEdit(tab_1);
        dateEdit_dateeffectuee->setObjectName("dateEdit_dateeffectuee");
        dateEdit_dateeffectuee->setGeometry(QRect(240, 160, 81, 21));
        lineEdit_id = new QLineEdit(tab_1);
        lineEdit_id->setObjectName("lineEdit_id");
        lineEdit_id->setGeometry(QRect(240, 90, 71, 20));
        modifier = new QPushButton(tab_1);
        modifier->setObjectName("modifier");
        modifier->setGeometry(QRect(330, 310, 61, 31));
        modifier->setFont(font3);
        modifier->setStyleSheet(QString::fromUtf8(""));
        label_16 = new QLabel(tab_1);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(150, 70, 81, 51));
        label_16->setScaledContents(true);
        lineEdit_id2 = new QLineEdit(tab_1);
        lineEdit_id2->setObjectName("lineEdit_id2");
        lineEdit_id2->setGeometry(QRect(240, 400, 61, 24));
        pushButton_15 = new QPushButton(tab_1);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(780, 10, 171, 41));
        pushButton_15->setBaseSize(QSize(0, 0));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Arial")});
        pushButton_15->setFont(font4);
        pushButton_15->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 13px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/pour youssef/picP.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_15->setIcon(icon6);
        pushButton_15->setIconSize(QSize(60, 35));
        label_13 = new QLabel(tab_1);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(20, 10, 71, 71));
        label_13->setStyleSheet(QString::fromUtf8("  color: #000000; /* Text color */\n"
"  font-size: 14px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"  padding: 5px; "));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/pour youssef/logo.png")));
        label_13->setScaledContents(true);
        label_13->setWordWrap(false);
        label_13->setMargin(0);
        pushButton_33 = new QPushButton(tab_1);
        pushButton_33->setObjectName("pushButton_33");
        pushButton_33->setGeometry(QRect(-20, 400, 90, 36));
        pushButton_33->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  color: #333333; /* Dark text color */\n"
"    border: none;                        /* Remove border */\n"
"    border-radius: 5px;                  /* Rounded corners */\n"
"    padding: 10px 20px;                  /* Padding for button size */\n"
"    font-size: 12px;                     /* Font size */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(56, 76, 130);  /* Lighter blue on hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgb(31, 46, 84);   /* Even darker blue on press */\n"
"}\n"
""));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/pour youssef/deconnexion.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_33->setIcon(icon7);
        pushButton_33->setIconSize(QSize(20, 20));
        boutonRechercher = new QPushButton(tab_1);
        boutonRechercher->setObjectName("boutonRechercher");
        boutonRechercher->setGeometry(QRect(150, 310, 71, 31));
        boutonRechercher->setFont(font3);
        boutonTri = new QPushButton(tab_1);
        boutonTri->setObjectName("boutonTri");
        boutonTri->setGeometry(QRect(240, 360, 61, 31));
        boutonTri->setFont(font3);
        boutonExporterCSV = new QPushButton(tab_1);
        boutonExporterCSV->setObjectName("boutonExporterCSV");
        boutonExporterCSV->setGeometry(QRect(150, 360, 71, 31));
        boutonExporterCSV->setFont(font3);
        comboBox = new QComboBox(tab_1);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(320, 360, 101, 31));
        label_21 = new QLabel(tab_1);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(150, 200, 101, 51));
        label_21->setScaledContents(true);
        label_22 = new QLabel(tab_1);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(150, 240, 101, 41));
        label_22->setScaledContents(true);
        lineEdit_nomLivreur = new QLineEdit(tab_1);
        lineEdit_nomLivreur->setObjectName("lineEdit_nomLivreur");
        lineEdit_nomLivreur->setGeometry(QRect(240, 220, 71, 20));
        lineEdit_emailLivreur = new QLineEdit(tab_1);
        lineEdit_emailLivreur->setObjectName("lineEdit_emailLivreur");
        lineEdit_emailLivreur->setGeometry(QRect(240, 250, 71, 21));
        statistiquesLabel = new QLabel(tab_1);
        statistiquesLabel->setObjectName("statistiquesLabel");
        statistiquesLabel->setGeometry(QRect(430, 290, 501, 141));
        pushButton_stats = new QPushButton(tab_1);
        pushButton_stats->setObjectName("pushButton_stats");
        pushButton_stats->setGeometry(QRect(330, 400, 71, 31));
        pushButton_stats->setFont(font3);
        retour = new QPushButton(tab_1);
        retour->setObjectName("retour");
        retour->setGeometry(QRect(150, 20, 71, 31));
        retour->setFont(font3);
        retour->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  color: #333333; /* Dark text color */\n"
"    border: none;                        /* Remove border */\n"
"    border-radius: 5px;                  /* Rounded corners */\n"
"    padding: 10px 20px;                  /* Padding for button size */\n"
"    font-size: 12px;                     /* Font size */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(56, 76, 130);  /* Lighter blue on hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgb(31, 46, 84);   /* Even darker blue on press */\n"
"}\n"
""));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/pour youssef/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        retour->setIcon(icon8);
        retour->setIconSize(QSize(27, 25));
        tab->addTab(tab_1, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        label_11 = new QLabel(tab_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(-10, 0, 1101, 501));
        label_11->setPixmap(QPixmap(QString::fromUtf8(":/pour youssef/bg.png")));
        label_11->setScaledContents(true);
        label_14 = new QLabel(tab_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(140, 10, 801, 431));
        label_14->setAutoFillBackground(false);
        label_14->setPixmap(QPixmap(QString::fromUtf8(":/pour youssef/bgW.png")));
        label_14->setScaledContents(true);
        label_14->setMargin(0);
        pushButton_31 = new QPushButton(tab_3);
        pushButton_31->setObjectName("pushButton_31");
        pushButton_31->setGeometry(QRect(770, 10, 171, 41));
        pushButton_31->setBaseSize(QSize(0, 0));
        pushButton_31->setFont(font4);
        pushButton_31->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 13px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        pushButton_31->setIcon(icon6);
        pushButton_31->setIconSize(QSize(60, 35));
        label_43 = new QLabel(tab_3);
        label_43->setObjectName("label_43");
        label_43->setGeometry(QRect(20, 10, 71, 71));
        label_43->setStyleSheet(QString::fromUtf8("  color: #000000; /* Text color */\n"
"  font-size: 14px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"  padding: 5px; "));
        label_43->setPixmap(QPixmap(QString::fromUtf8(":/pour youssef/logo.png")));
        label_43->setScaledContents(true);
        label_43->setWordWrap(false);
        label_43->setMargin(0);
        pushButton_37 = new QPushButton(tab_3);
        pushButton_37->setObjectName("pushButton_37");
        pushButton_37->setGeometry(QRect(-10, 110, 141, 31));
        pushButton_37->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 11px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        pushButton_37->setIcon(icon);
        pushButton_37->setIconSize(QSize(60, 35));
        pushButton_36 = new QPushButton(tab_3);
        pushButton_36->setObjectName("pushButton_36");
        pushButton_36->setGeometry(QRect(-20, 150, 181, 41));
        pushButton_36->setMinimumSize(QSize(0, 0));
        pushButton_36->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 11px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        pushButton_36->setIcon(icon1);
        pushButton_36->setIconSize(QSize(60, 35));
        pushButton_32 = new QPushButton(tab_3);
        pushButton_32->setObjectName("pushButton_32");
        pushButton_32->setGeometry(QRect(-20, 200, 161, 41));
        pushButton_32->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 11px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        pushButton_32->setIcon(icon2);
        pushButton_32->setIconSize(QSize(60, 35));
        pushButton_38 = new QPushButton(tab_3);
        pushButton_38->setObjectName("pushButton_38");
        pushButton_38->setGeometry(QRect(-20, 250, 181, 41));
        pushButton_38->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 11px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        pushButton_38->setIcon(icon4);
        pushButton_38->setIconSize(QSize(60, 35));
        pushButton_35 = new QPushButton(tab_3);
        pushButton_35->setObjectName("pushButton_35");
        pushButton_35->setGeometry(QRect(-20, 340, 171, 51));
        pushButton_35->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 11px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        pushButton_35->setIcon(icon3);
        pushButton_35->setIconSize(QSize(60, 40));
        pushButton_34 = new QPushButton(tab_3);
        pushButton_34->setObjectName("pushButton_34");
        pushButton_34->setGeometry(QRect(-60, 290, 231, 51));
        pushButton_34->setAutoFillBackground(false);
        pushButton_34->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 11px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        pushButton_34->setIcon(icon5);
        pushButton_34->setIconSize(QSize(60, 40));
        pushButton_39 = new QPushButton(tab_3);
        pushButton_39->setObjectName("pushButton_39");
        pushButton_39->setGeometry(QRect(0, 400, 90, 36));
        pushButton_39->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: transparent; /* Transparent background */\n"
"  color: #333333; /* Dark text color */\n"
"  border: none; /* No border */\n"
"  border-radius: 5px; /* Rounded corners */\n"
"  padding: 10px 20px; /* Padding inside the button */\n"
"  font-size: 14px; /* Font size */\n"
"  font-family: Arial, sans-serif; /* Font family */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"  background-color: rgba(204, 204, 204, 0.2); /* Light grey tint on hover */\n"
"}\n"
""));
        pushButton_39->setIcon(icon7);
        pushButton_39->setIconSize(QSize(20, 20));
        label_41 = new QLabel(tab_3);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(210, 50, 151, 41));
        label_41->setScaledContents(true);
        calendarWidget = new QCalendarWidget(tab_3);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(170, 90, 291, 171));
        sendEmailButton = new QPushButton(tab_3);
        sendEmailButton->setObjectName("sendEmailButton");
        sendEmailButton->setGeometry(QRect(160, 390, 71, 31));
        sendEmailButton->setFont(font3);
        noteLabel = new QLabel(tab_3);
        noteLabel->setObjectName("noteLabel");
        noteLabel->setGeometry(QRect(490, 50, 411, 381));
        label_46 = new QLabel(tab_3);
        label_46->setObjectName("label_46");
        label_46->setGeometry(QRect(490, 60, 411, 41));
        label_46->setScaledContents(true);
        tab->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        label_42 = new QLabel(tab_4);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(90, 70, 121, 61));
        label_42->setScaledContents(true);
        label_44 = new QLabel(tab_4);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(290, 0, 151, 41));
        label_44->setScaledContents(true);
        label_45 = new QLabel(tab_4);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(90, 170, 121, 61));
        label_45->setScaledContents(true);
        pushButton_on = new QPushButton(tab_4);
        pushButton_on->setObjectName("pushButton_on");
        pushButton_on->setGeometry(QRect(260, 80, 91, 41));
        pushButton_on->setFont(font3);
        pushButton_plus = new QPushButton(tab_4);
        pushButton_plus->setObjectName("pushButton_plus");
        pushButton_plus->setGeometry(QRect(260, 180, 91, 41));
        pushButton_plus->setFont(font3);
        pushButton_off = new QPushButton(tab_4);
        pushButton_off->setObjectName("pushButton_off");
        pushButton_off->setGeometry(QRect(380, 80, 91, 41));
        pushButton_off->setFont(font3);
        pushButton_moin = new QPushButton(tab_4);
        pushButton_moin->setObjectName("pushButton_moin");
        pushButton_moin->setGeometry(QRect(380, 180, 91, 41));
        pushButton_moin->setFont(font3);
        connectionStatusLabel = new QLabel(tab_4);
        connectionStatusLabel->setObjectName("connectionStatusLabel");
        connectionStatusLabel->setGeometry(QRect(470, 250, 331, 171));
        connectionStatusLabel->setScaledContents(true);
        openDoorButton = new QPushButton(tab_4);
        openDoorButton->setObjectName("openDoorButton");
        openDoorButton->setGeometry(QRect(620, 80, 91, 41));
        openDoorButton->setFont(font3);
        closeDoorButton = new QPushButton(tab_4);
        closeDoorButton->setObjectName("closeDoorButton");
        closeDoorButton->setGeometry(QRect(620, 150, 91, 41));
        closeDoorButton->setFont(font3);
        distanceTextEdit = new QTextEdit(tab_4);
        distanceTextEdit->setObjectName("distanceTextEdit");
        distanceTextEdit->setGeometry(QRect(10, 250, 411, 191));
        tab->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 953, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        tab->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Clients", nullptr));
#if QT_CONFIG(tooltip)
        tab->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_8->setText(QString());
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "   Acceuil", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "  Gestion Employe ", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "  Gestion Client ", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "Gestion Stock ", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "  Gestion Livraison ", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "   Gestion\n"
" Fournisseur", nullptr));
        label_12->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton {\n"
"  color: #333333; /* Dark text color */\n"
"    border: none;                        /* Remove border */\n"
"    border-radius: 5px;                  /* Rounded corners */\n"
"    padding: 10px 20px;                  /* Padding for button size */\n"
"    font-size: 12px;                     /* Font size */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(56, 76, 130);  /* Lighter blue on hover */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgb(31, 46, 84);   /* Even darker blue on press */\n"
"}\n"
"", nullptr));
        label_12->setText(QString());
        lineEdit_adresse->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = table_livraisons->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID Livraison", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = table_livraisons->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "DATE_PREVUE", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = table_livraisons->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "DATE_EFFECTUEE", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = table_livraisons->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "ADRESSE", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = table_livraisons->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "NOM_LIVREUR", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = table_livraisons->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "EMAIL_LIVREUR", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; font-style:italic; color:#55aa7f;\">Adresse</span></p></body></html>", nullptr));
        supprimer->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700; font-style:italic; color:#ffaa7f;\">affichage Des Livraison:</span></p></body></html>", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; color:#55aa7f;\">Date Epervue</span></p></body></html>", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("MainWindow", "ajouter", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700; font-style:italic; color:#55aa7f;\">Date Effectu\303\251e</span></p></body></html>", nullptr));
        modifier->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700; font-style:italic; color:#55aa7f;\">ID Livraison</span></p></body></html>", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "Hi,Rabie", nullptr));
        label_13->setText(QString());
        pushButton_33->setText(QString());
        boutonRechercher->setText(QCoreApplication::translate("MainWindow", "rechercher", nullptr));
        boutonTri->setText(QCoreApplication::translate("MainWindow", "Tri", nullptr));
        boutonExporterCSV->setText(QCoreApplication::translate("MainWindow", "exporter", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "ID", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Date Pr\303\251vue", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Nom", nullptr));

        label_21->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:8pt; font-weight:700; font-style:italic; color:#55aa7f;\">NOM LIVREUR</span></p></body></html>", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:8pt; font-weight:700; color:#55aa7f;\">EMAIL LIVREUR</span></p></body></html>", nullptr));
        lineEdit_nomLivreur->setText(QString());
        lineEdit_emailLivreur->setText(QString());
        statistiquesLabel->setText(QString());
        pushButton_stats->setText(QCoreApplication::translate("MainWindow", "statistique", nullptr));
        retour->setText(QString());
        tab->setTabText(tab->indexOf(tab_1), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        label_11->setText(QString());
        label_14->setText(QString());
        pushButton_31->setText(QCoreApplication::translate("MainWindow", "Hi,Rabie", nullptr));
        label_43->setText(QString());
        pushButton_37->setText(QCoreApplication::translate("MainWindow", "   Acceuil", nullptr));
        pushButton_36->setText(QCoreApplication::translate("MainWindow", "  Gestion Employe ", nullptr));
        pushButton_32->setText(QCoreApplication::translate("MainWindow", "  Gestion Client ", nullptr));
        pushButton_38->setText(QCoreApplication::translate("MainWindow", "  Gestion Livraison ", nullptr));
        pushButton_35->setText(QCoreApplication::translate("MainWindow", "Gestion Stock ", nullptr));
        pushButton_34->setText(QCoreApplication::translate("MainWindow", "   Gestion\n"
" Fournisseur", nullptr));
        pushButton_39->setText(QString());
        label_41->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700; font-style:italic; color:#ffaa7f;\">CALENDRIER:</span></p><p><br/></p></body></html>", nullptr));
        sendEmailButton->setText(QCoreApplication::translate("MainWindow", "send email", nullptr));
        noteLabel->setText(QString());
        label_46->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700; font-style:italic; color:#ffaa7f;\">List of Deliveries Scheduled for This Date:</span></p></body></html>", nullptr));
        tab->setTabText(tab->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Page", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700; font-style:italic; color:#55aa7f;\">lampe 1:</span></p></body></html>", nullptr));
        label_44->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; color:#ffaa7f;\">ARDUINO:</span></p></body></html>", nullptr));
        label_45->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt; font-weight:700; font-style:italic; color:#55aa7f;\">lampe 2:</span></p></body></html>", nullptr));
        pushButton_on->setText(QCoreApplication::translate("MainWindow", "ON", nullptr));
        pushButton_plus->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        pushButton_off->setText(QCoreApplication::translate("MainWindow", "OFF", nullptr));
        pushButton_moin->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        connectionStatusLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
        openDoorButton->setText(QCoreApplication::translate("MainWindow", "open door ", nullptr));
        closeDoorButton->setText(QCoreApplication::translate("MainWindow", "close door", nullptr));
        tab->setTabText(tab->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Page", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
